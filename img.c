#include "img.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(dir) mkdir(dir, 0755)
#endif

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

/**
 * 画像バッファを白色(255,255,255)でクリアする
 */
void img_clear(void) {
  int i, j;
  // 全ピクセルを白で塗りつぶし
  for (j = 0; j < HEIGHT; ++j) {
    for (i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
    }
  }
}

/**
 * 画像バッファをPPMファイルとして出力する
 * ファイル名は連番で自動生成される（img0001.ppm, img0002.ppm...）
 */
void img_write(void) {
  // 出力ディレクトリを作成
#ifdef _WIN32
  _mkdir("out");
#else
  struct stat st = {0};
  if (stat("out", &st) == -1) {
    mkdir("out", 0755);
  }
#endif

  // ファイル名を生成
  sprintf(fname, "out/img%04d.ppm", ++filecnt);
  FILE* f = fopen(fname, "wb");
  if (f == NULL) {
    fprintf(stderr, "can't open %s\n", fname);
    exit(1);
  }
  // PPMヘッダーを出力
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  // 画像データを出力
  fwrite(buf, sizeof(buf), 1, f);
  fclose(f);
}

/**
 * 指定した座標にピクセルを描画する
 * @param c 色情報
 * @param x X座標
 * @param y Y座標（下が0、上が正の値）
 */
void img_putpixel(struct color c, int x, int y) {
  // 画面範囲外のチェック
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }
  // Y座標を画像座標系に変換（上下反転）
  buf[HEIGHT - y - 1][x][0] = c.r;
  buf[HEIGHT - y - 1][x][1] = c.g;
  buf[HEIGHT - y - 1][x][2] = c.b;
}

/**
 * 塗りつぶした円を描画する
 * @param c 色情報
 * @param x 中心のX座標
 * @param y 中心のY座標
 * @param r 半径
 */
void img_fillcircle(struct color c, double x, double y, double r) {
  // 描画範囲を計算
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int i, j;
  // 範囲内の全ピクセルをチェック
  for (j = jmin; j <= jmax; ++j) {
    for (i = imin; i <= imax; ++i) {
      // 中心からの距離が半径以下なら描画
      if ((x - i) * (x - i) + (y - j) * (y - j) <= r * r) {
        img_putpixel(c, i, j);
      }
    }
  }
}

/**
 * 塗りつぶした円を描画する
 * @param c 色情報
 * @param x 中心のX座標
 * @param y 中心のY座標
 * @param rmax 最大半径
 * @param rmin 最小半径
 * @param n 描画方法指定
 * 0で円、1で上側半円、2で下側半円、3で左上半円、4で左下半円
 */
void img_filldonuts(struct color c, double x, double y, double rmax, double rmin, int n) {
  int imin = (int)(x - rmax - 1), imax = (int)(x + rmax + 1);
  int jmin = (int)(y - rmax - 1), jmax = (int)(y + rmax + 1);
  int i, j;
  for (j = jmin; j <= jmax; ++j) {
    for (i = imin; i <= imax; ++i) {
      // 円
      if (n == 0 && (x - i) * (x - i) + (y - j) * (y - j) <= rmax * rmax && (x - i) * (x - i) + (y - j) * (y - j) >= rmin * rmin) {
        img_putpixel(c, i, j);
      }
      // 上側半円
      if (n == 1 && (x - i) * (x - i) + (y - j) * (y - j) <= rmax * rmax && (x - i) * (x - i) + (y - j) * (y - j) >= rmin * rmin && j >= y) {
        img_putpixel(c, i, j);
      }
      // 下側半円
      if (n == 2 && (x - i) * (x - i) + (y - j) * (y - j) <= rmax * rmax && (x - i) * (x - i) + (y - j) * (y - j) >= rmin * rmin && j <= y) {
        img_putpixel(c, i, j);
      }
      // 左上半円
      if (n == 3 && (x - i) * (x - i) + (y - j) * (y - j) <= rmax * rmax && (x - i) * (x - i) + (y - j) * (y - j) >= rmin * rmin && y >= (x - i) + j) {
        img_putpixel(c, i, j);
      }
      // 左下半円
      if (n == 4 && (x - i) * (x - i) + (y - j) * (y - j) <= rmax * rmax && (x - i) * (x - i) + (y - j) * (y - j) >= rmin * rmin && y <= -(x - i) + j) {
        img_putpixel(c, i, j);
      }
    }
  }
}

/**
 * 整数比較関数（qsort用）
 * @param a 比較する要素1
 * @param b 比較する要素2
 * @return a-bの値（昇順ソート用）
 */
int cmp_int(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

/**
 * スキャンライン法を使用して多角形を塗りつぶす
 * @param c 色情報
 * @param ax X座標の配列
 * @param ay Y座標の配列
 * @param n 頂点数
 */
void fill_scanline(struct color c, int* ax, int* ay, int n) {
  int i, j, y;
  int ymin = ay[0];
  int ymax = ay[0];

  // Y座標の最小値と最大値を求める
  for (i = 1; i < n; i++) {
    if (ay[i] < ymin) ymin = ay[i];
    if (ay[i] > ymax) ymax = ay[i];
  }

  // 交点のX座標を格納する配列を動的確保
  int* nodeX = malloc(n * sizeof(int));
  if (nodeX == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  int nodes;

  // 各スキャンラインについて処理
  for (y = ymin; y < ymax; y++) {
    nodes = 0;
    j = n - 1;

    // 多角形の各辺とスキャンラインの交点を求める
    for (i = 0; i < n; i++) {
      if ((ay[i] < y && ay[j] >= y) || (ay[j] < y && ay[i] >= y)) {
        // 線形補間で交点のX座標を計算
        nodeX[nodes++] = (int)(ax[i] + (double)(y - ay[i]) / (ay[j] - ay[i]) * (ax[j] - ax[i]));
      }
      j = i;
    }

    // 交点をX座標でソート
    qsort(nodeX, nodes, sizeof(int), cmp_int);

    // 交点のペアごとに水平線を描画
    for (i = 0; i < nodes; i += 2) {
      if (i + 1 >= nodes) break;
      int x_start = nodeX[i];
      int x_end = nodeX[i + 1];

      for (int x = x_start; x <= x_end; x++) {
        img_putpixel(c, x, y);
      }
    }
  }

  // 動的に確保したメモリを解放
  free(nodeX);
}

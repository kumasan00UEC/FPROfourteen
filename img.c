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

void img_clear(void) {
  int i, j;
  for (j = 0; j < HEIGHT; ++j) {
    for (i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
    }
  }
}

void img_write(void) {
  // outディレクトリが存在しない場合は作成
#ifdef _WIN32
  _mkdir("out");
#else
  struct stat st = {0};
  if (stat("out", &st) == -1) {
    mkdir("out", 0755);
  }
#endif

  sprintf(fname, "out/img%04d.ppm", ++filecnt);
  FILE* f = fopen(fname, "wb");
  if (f == NULL) {
    fprintf(stderr, "can't open %s\n", fname);
    exit(1);
  }
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  fwrite(buf, sizeof(buf), 1, f);
  fclose(f);
}

void img_putpixel(struct color c, int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }
  buf[HEIGHT - y - 1][x][0] = c.r;
  buf[HEIGHT - y - 1][x][1] = c.g;
  buf[HEIGHT - y - 1][x][2] = c.b;
}

void img_fillcircle(struct color c, double x, double y, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int i, j;
  for (j = jmin; j <= jmax; ++j) {
    for (i = imin; i <= imax; ++i) {
      if ((x - i) * (x - i) + (y - j) * (y - j) <= r * r) {
        img_putpixel(c, i, j);
      }
    }
  }
}

/* 比較関数 (qsort用) */
int cmp_int(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

/* スキャンラインアルゴリズムによる塗りつぶし */
/* 頂点配列 ax, ay とその頂点数 n を受け取ります（四角形なら n=4） */
void fill_scanline(struct color c, int* ax, int* ay, int n) {
  int i, j, y;
  int ymin = ay[0];
  int ymax = ay[0];

  // 1. 全体のYの範囲（スキャン範囲）を求める
  for (i = 1; i < n; i++) {
    if (ay[i] < ymin) ymin = ay[i];
    if (ay[i] > ymax) ymax = ay[i];
  }

  // 交点X座標を格納するバッファ (四角形なら最大でも1行に2〜4点あれば十分)
  // 複雑な多角形に対応するため少し大きめに確保するか、動的確保します
  int nodeX[20];
  int nodes;

  // 2. Y座標を上から下（または下から上）へスキャン
  for (y = ymin; y < ymax; y++) {
    nodes = 0;
    j = n - 1;  // 最後の頂点（iの直前の頂点として使用）

    // 3. 全ての辺に対して、現在のスキャンライン y と交差するか判定
    for (i = 0; i < n; i++) {
      // 辺 (ax[i], ay[i]) - (ax[j], ay[j]) が現在のYをまたいでいるか？
      // 頂点の二重カウントを防ぐため、一方は < で、もう一方は >= で判定する
      if ((ay[i] < y && ay[j] >= y) || (ay[j] < y && ay[i] >= y)) {
        // 線形補間で交差するX座標を計算
        // x = x1 + (y - y1) / (y2 - y1) * (x2 - x1)
        nodeX[nodes++] = (int)(ax[i] + (double)(y - ay[i]) / (ay[j] - ay[i]) * (ax[j] - ax[i]));
      }
      j = i;  // 次のループのために現在の頂点を保存
    }

    // 4. 求めたX座標を昇順（左から右）にソート
    qsort(nodeX, nodes, sizeof(int), cmp_int);

    // 5. ペアごとにその間を塗りつぶす (偶数番目から奇数番目へ)
    // 凸多角形の場合、nodesは通常2つになります
    for (i = 0; i < nodes; i += 2) {
      if (i + 1 >= nodes) break;  // 安全策

      int x_start = nodeX[i];
      int x_end = nodeX[i + 1];

      // 横線を引く
      for (int x = x_start; x <= x_end; x++) {
        img_putpixel(c, x, y);
      }
    }
  }
}

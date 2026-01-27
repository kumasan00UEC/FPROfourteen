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

static unsigned char image_buffer[HEIGHT][WIDTH][3];
static int file_counter = 0;
static char output_filename[100];

/**
 * 画像バッファを白色(255,255,255)でクリアする
 */
void img_clear_canvas(void) {
  int x_pos, y_pos;
  // 全ピクセルを白で塗りつぶし
  for (y_pos = 0; y_pos < HEIGHT; ++y_pos) {
    for (x_pos = 0; x_pos < WIDTH; ++x_pos) {
      image_buffer[y_pos][x_pos][0] = image_buffer[y_pos][x_pos][1] = image_buffer[y_pos][x_pos][2] = 255;
    }
  }
}

/**
 * 画像バッファをPPMファイルとして出力する
 * ファイル名は連番で自動生成される（img0001.ppm, img0002.ppm...）
 */
void img_save_to_file(void) {
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
  sprintf(output_filename, "out/img%04d.ppm", ++file_counter);
  FILE* output_file = fopen(output_filename, "wb");
  if (output_file == NULL) {
    fprintf(stderr, "can't open %s\n", output_filename);
    exit(1);
  }
  // PPMヘッダーを出力
  fprintf(output_file, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  // 画像データを出力
  fwrite(image_buffer, sizeof(image_buffer), 1, output_file);
  fclose(output_file);
}

/**
 * 指定した座標にピクセルを描画する
 * @param color 色情報
 * @param x X座標
 * @param y Y座標（下が0、上が正の値）
 */
void img_draw_pixel(struct Color color, int x, int y) {
  // 画面範囲外のチェック
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }
  // Y座標を画像座標系に変換（上下反転）
  image_buffer[HEIGHT - y - 1][x][0] = color.r;
  image_buffer[HEIGHT - y - 1][x][1] = color.g;
  image_buffer[HEIGHT - y - 1][x][2] = color.b;
}

/**
 * 塗りつぶした円を描画する
 * @param color 色情報
 * @param center_x 中心のX座標
 * @param center_y 中心のY座標
 * @param radius 半径
 */
void img_draw_filled_circle(struct Color color, double center_x, double center_y, double radius) {
  // 描画範囲を計算
  int min_x = (int)(center_x - radius - 1), max_x = (int)(center_x + radius + 1);
  int min_y = (int)(center_y - radius - 1), max_y = (int)(center_y + radius + 1);
  int x_pos, y_pos;
  // 範囲内の全ピクセルをチェック
  for (y_pos = min_y; y_pos <= max_y; ++y_pos) {
    for (x_pos = min_x; x_pos <= max_x; ++x_pos) {
      // 中心からの距離が半径以下なら描画
      if ((center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <= radius * radius) {
        img_draw_pixel(color, x_pos, y_pos);
      }
    }
  }
}

/**
 * リング型（ドーナツ型）の形を描画する
 * @param color 色情報
 * @param center_x 中心のX座標
 * @param center_y 中心のY座標
 * @param outer_radius 最大半径
 * @param inner_radius 最小半径
 * @param draw_mode 描画方法指定
 * 0で円、0で上側半円、2で下側半円、3で左上半円、4で左下半円
 */
void img_draw_ring(struct Color color, double center_x, double center_y, double outer_radius, double inner_radius,
                   int draw_mode) {
  if (inner_radius > outer_radius) {
    fprintf(stderr, "Error: inner_radius is larger than outer_radius\n");
    return;
  }
  int min_x = (int)(center_x - outer_radius - 1);
  int max_x = (int)(center_x + outer_radius + 1);
  int min_y = (int)(center_y - outer_radius - 1);
  int max_y = (int)(center_y + outer_radius + 1);
  int x_pos, y_pos;
  for (y_pos = min_y; y_pos <= max_y; ++y_pos) {
    for (x_pos = min_x; x_pos <= max_x; ++x_pos) {
      // 円
      if (draw_mode == 0 &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <=
              outer_radius * outer_radius &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) >=
              inner_radius * inner_radius) {
        img_draw_pixel(color, x_pos, y_pos);
      }
      // 上側半円
      if (draw_mode == 1 &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <=
              outer_radius * outer_radius &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) >=
              inner_radius * inner_radius &&
          y_pos >= center_y) {
        img_draw_pixel(color, x_pos, y_pos);
      }
      // 下側半円
      if (draw_mode == 2 &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <=
              outer_radius * outer_radius &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) >=
              inner_radius * inner_radius &&
          y_pos <= center_y) {
        img_draw_pixel(color, x_pos, y_pos);
      }
      // 左上半円
      if (draw_mode == 3 &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <=
              outer_radius * outer_radius &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) >=
              inner_radius * inner_radius &&
          center_y <= (center_x - x_pos) + y_pos) {
        img_draw_pixel(color, x_pos, y_pos);
      }
      // 左下半円
      if (draw_mode == 4 &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) <=
              outer_radius * outer_radius &&
          (center_x - x_pos) * (center_x - x_pos) + (center_y - y_pos) * (center_y - y_pos) >=
              inner_radius * inner_radius &&
          center_y >= -(center_x - x_pos) + y_pos) {
        img_draw_pixel(color, x_pos, y_pos);
      }
    }
  }
}

/**
 * 整数比較関数（qsort用）
 * @param first_element 比較する要素1
 * @param second_element 比較する要素2
 * @return first-secondの値（昇順ソート用）
 */
int compare_integers(const void* first_element, const void* second_element) {
  return (*(int*)first_element - *(int*)second_element);
}

/**
 * スキャンライン法を使用して多角形を塗りつぶす
 * @param color 色情報
 * @param vertices_x X座標の配列
 * @param vertices_y Y座標の配列
 * @param vertex_count 頂点数
 */
void img_fill_polygon(struct Color color, int* vertices_x, int* vertices_y, int vertex_count) {
  int current_vertex, previous_vertex, scan_y;
  int min_y = vertices_y[0];
  int max_y = vertices_y[0];

  // Y座標の最小値と最大値を求める
  for (current_vertex = 1; current_vertex < vertex_count; current_vertex++) {
    if (vertices_y[current_vertex] < min_y) min_y = vertices_y[current_vertex];
    if (vertices_y[current_vertex] > max_y) max_y = vertices_y[current_vertex];
  }

  // 交点のX座標を格納する配列を動的確保
  int* intersection_x = malloc(vertex_count * sizeof(int));
  if (intersection_x == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  int intersection_count;

  // 各スキャンラインについて処理
  for (scan_y = min_y; scan_y < max_y; scan_y++) {
    intersection_count = 0;
    previous_vertex = vertex_count - 1;

    // 多角形の各辺とスキャンラインの交点を求める
    for (current_vertex = 0; current_vertex < vertex_count; current_vertex++) {
      if ((vertices_y[current_vertex] < scan_y && vertices_y[previous_vertex] >= scan_y) ||
          (vertices_y[previous_vertex] < scan_y && vertices_y[current_vertex] >= scan_y)) {
        // 線形補間で交点のX座標を計算
        intersection_x[intersection_count++] =
            (int)(vertices_x[current_vertex] + (double)(scan_y - vertices_y[current_vertex]) /
                                                   (vertices_y[previous_vertex] - vertices_y[current_vertex]) *
                                                   (vertices_x[previous_vertex] - vertices_x[current_vertex]));
      }
      previous_vertex = current_vertex;
    }

    // 交点をX座標でソート
    qsort(intersection_x, intersection_count, sizeof(int), compare_integers);

    // 交点のペアごとに水平線を描画
    for (current_vertex = 0; current_vertex < intersection_count; current_vertex += 2) {
      if (current_vertex + 1 >= intersection_count) break;
      int start_x = intersection_x[current_vertex];
      int end_x = intersection_x[current_vertex + 1];

      for (int pixel_x = start_x; pixel_x <= end_x; pixel_x++) {
        img_draw_pixel(color, pixel_x, scan_y);
      }
    }
  }

  // 動的に確保したメモリを解放
  free(intersection_x);
}

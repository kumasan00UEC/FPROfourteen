// animate1 --- create animation using img lib.
#include <math.h>

#include "img.h"

int main(void) {
  struct Color white = {255, 255, 255};
  struct Color red = {233, 51, 68};
  struct Color lightred = {245, 229, 236};

  int i;
  for (i = 0; i < 20; ++i) {
    // large Q
    img_clear_canvas();
    img_draw_ring(lightred, XCENTER, YCENTER, 90 - i, 60 - i, 0);
    int ax[4] = {XCENTER + 20 - ceil(i / 1.4), XCENTER + 40 - ceil(i / 1.4), XCENTER + 60 - ceil(i / 1.4),
                 XCENTER + 40 - ceil(i / 1.4)};
    int ay[4] = {YCENTER - 40 + ceil(i / 1.4), YCENTER - 40 + ceil(i / 1.4), YCENTER - 90 + ceil(i / 1.4),
                 YCENTER - 90 + ceil(i / 1.4)};
    img_fill_polygon(lightred, ax, ay, 4);
    // Q
    img_draw_ring(red, 25 + i, YCENTER, 20, 15, 0);
    int Qx[4] = {25 + i, 30 + i, 45 + i, 40 + i};
    int Qy[4] = {YCENTER - 5, YCENTER - 5, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, Qx, Qy, 4);
    // u
    img_draw_ring(red, 66 + ceil(i / 1.5), YCENTER - 10, 10, 5, 2);
    int ux1[4] = {56 + ceil(i / 1.5), 60 + ceil(i / 1.5), 60 + ceil(i / 1.5), 56 + ceil(i / 1.5)};
    int uy1[4] = {YCENTER, YCENTER, YCENTER - 10, YCENTER - 10};
    int ux2[4] = {72 + ceil(i / 1.5), 76 + ceil(i / 1.5), 76 + ceil(i / 1.5), 72 + ceil(i / 1.5)};
    int uy2[4] = {YCENTER, YCENTER, YCENTER - 10, YCENTER - 10};
    img_fill_polygon(red, ux1, uy1, 4);
    img_fill_polygon(red, ux2, uy2, 4);
    // i
    img_draw_filled_circle(red, 90 + ceil(i / 2), YCENTER + 10, 3);
    int ix[4] = {88 + ceil(i / 2), 92 + ceil(i / 2), 92 + ceil(i / 2), 88 + ceil(i / 2)};
    int iy[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, ix, iy, 4);
    // z
    int zx1[4] = {105 + ceil(i / 4), 120 + ceil(i / 4), 120 + ceil(i / 4), 105 + ceil(i / 4)};
    int zy1[4] = {YCENTER, YCENTER, YCENTER - 5, YCENTER - 5};
    int zx2[4] = {118 + ceil(i / 4), 123 + ceil(i / 4), 108 + ceil(i / 4), 103 + ceil(i / 4)};
    int zy2[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    int zx3[4] = {105 + ceil(i / 4), 120 + ceil(i / 4), 120 + ceil(i / 4), 105 + ceil(i / 4)};
    int zy3[4] = {YCENTER - 15, YCENTER - 15, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, zx1, zy1, 4);
    img_fill_polygon(red, zx2, zy2, 4);
    img_fill_polygon(red, zx3, zy3, 4);
    // k1
    int k1x[11] = {XCENTER - 5,  XCENTER,      XCENTER, XCENTER + 20, XCENTER + 26, XCENTER + 5,
                   XCENTER + 24, XCENTER + 18, XCENTER, XCENTER,      XCENTER - 5};
    int k1y[11] = {YCENTER + 20, YCENTER + 20, YCENTER,     YCENTER + 20, YCENTER + 20, YCENTER - 2,
                   YCENTER - 20, YCENTER - 20, YCENTER - 3, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, k1x, k1y, 11);
    // n
    img_draw_ring(red, XCENTER + 43 - ceil(i / 4), YCENTER - 10, 10, 5, 1);
    int nx1[4] = {XCENTER + 33 - ceil(i / 4), XCENTER + 37 - ceil(i / 4), XCENTER + 37 - ceil(i / 4),
                  XCENTER + 33 - ceil(i / 4)};
    int ny1[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    int nx2[4] = {XCENTER + 49 - ceil(i / 4), XCENTER + 53 - ceil(i / 4), XCENTER + 53 - ceil(i / 4),
                  XCENTER + 49 - ceil(i / 4)};
    int ny2[4] = {YCENTER - 10, YCENTER - 10, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, nx1, ny1, 4);
    img_fill_polygon(red, nx2, ny2, 4);
    // o
    img_draw_ring(red, XCENTER + 71 - ceil(i / 2), YCENTER - 10, 10, 5, 0);
    // c
    img_draw_ring(red, XCENTER + 98 - ceil(i / 1.5), YCENTER - 10, 10, 5, 3);
    img_draw_ring(red, XCENTER + 98 - ceil(i / 1.5), YCENTER - 10, 10, 5, 4);
    // k2
    int k2x[11] = {XCENTER + 117 - i, XCENTER + 122 - i, XCENTER + 122 - i, XCENTER + 127 - i,
                   XCENTER + 134 - i, XCENTER + 126 - i, XCENTER + 134 - i, XCENTER + 129 - i,
                   XCENTER + 122 - i, XCENTER + 122 - i, XCENTER + 117 - i};
    int k2y[11] = {YCENTER + 20, YCENTER + 20, YCENTER - 5,  YCENTER,      YCENTER,     YCENTER - 8,
                   YCENTER - 20, YCENTER - 20, YCENTER - 10, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, k2x, k2y, 11);
    img_save_to_file();
  }
  for (i = 0; i < 20; ++i) {
    // large Q
    img_clear_canvas();
    img_draw_ring(lightred, XCENTER, YCENTER, 70 + i, 40 + i, 0);
    int ax[4] = {XCENTER + 5 + ceil(i / 1.4), XCENTER + 25 + ceil(i / 1.4), XCENTER + 45 + ceil(i / 1.4),
                 XCENTER + 25 + ceil(i / 1.4)};
    int ay[4] = {YCENTER - 25 - ceil(i / 1.4), YCENTER - 25 - ceil(i / 1.4), YCENTER - 75 - ceil(i / 1.4),
                 YCENTER - 75 - ceil(i / 1.4)};
    img_fill_polygon(lightred, ax, ay, 4);
    // Q
    img_draw_ring(red, 45 - i, YCENTER, 20, 15, 0);
    int Qx[4] = {45 - i, 50 - i, 65 - i, 60 - i};
    int Qy[4] = {YCENTER - 5, YCENTER - 5, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, Qx, Qy, 4);
    // u
    img_draw_ring(red, 80 - ceil(i / 1.5), YCENTER - 10, 10, 5, 2);
    int ux1[4] = {70 - ceil(i / 1.5), 74 - ceil(i / 1.5), 74 - ceil(i / 1.5), 70 - ceil(i / 1.5)};
    int uy1[4] = {YCENTER, YCENTER, YCENTER - 10, YCENTER - 10};
    int ux2[4] = {86 - ceil(i / 1.5), 90 - ceil(i / 1.5), 90 - ceil(i / 1.5), 86 - ceil(i / 1.5)};
    int uy2[4] = {YCENTER, YCENTER, YCENTER - 10, YCENTER - 10};
    img_fill_polygon(red, ux1, uy1, 4);
    img_fill_polygon(red, ux2, uy2, 4);
    // i
    img_draw_filled_circle(red, 100 - ceil(i / 2), YCENTER + 10, 3);
    int ix[4] = {98 - ceil(i / 2), 102 - ceil(i / 2), 102 - ceil(i / 2), 98 - ceil(i / 2)};
    int iy[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, ix, iy, 4);
    // z
    int zx1[4] = {110 - ceil(i / 4), 125 - ceil(i / 4), 125 - ceil(i / 4), 110 - ceil(i / 4)};
    int zy1[4] = {YCENTER, YCENTER, YCENTER - 5, YCENTER - 5};
    int zx2[4] = {123 - ceil(i / 4), 128 - ceil(i / 4), 113 - ceil(i / 4), 108 - ceil(i / 4)};
    int zy2[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    int zx3[4] = {110 - ceil(i / 4), 125 - ceil(i / 4), 125 - ceil(i / 4), 110 - ceil(i / 4)};
    int zy3[4] = {YCENTER - 15, YCENTER - 15, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, zx1, zy1, 4);
    img_fill_polygon(red, zx2, zy2, 4);
    img_fill_polygon(red, zx3, zy3, 4);
    // k
    int kx[11] = {XCENTER - 5,  XCENTER,      XCENTER, XCENTER + 20, XCENTER + 26, XCENTER + 5,
                  XCENTER + 24, XCENTER + 18, XCENTER, XCENTER,      XCENTER - 5};
    int ky[11] = {YCENTER + 20, YCENTER + 20, YCENTER,     YCENTER + 20, YCENTER + 20, YCENTER - 2,
                  YCENTER - 20, YCENTER - 20, YCENTER - 3, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, kx, ky, 11);
    // n
    img_draw_ring(red, XCENTER + 38 + ceil(i / 4), YCENTER - 10, 10, 5, 1);
    int nx1[4] = {XCENTER + 28 + ceil(i / 4), XCENTER + 32 + ceil(i / 4), XCENTER + 32 + ceil(i / 4),
                  XCENTER + 28 + ceil(i / 4)};
    int ny1[4] = {YCENTER, YCENTER, YCENTER - 20, YCENTER - 20};
    int nx2[4] = {XCENTER + 44 + ceil(i / 4), XCENTER + 48 + ceil(i / 4), XCENTER + 48 + ceil(i / 4),
                  XCENTER + 44 + ceil(i / 4)};
    int ny2[4] = {YCENTER - 10, YCENTER - 10, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, nx1, ny1, 4);
    img_fill_polygon(red, nx2, ny2, 4);
    // o
    img_draw_ring(red, XCENTER + 61 + ceil(i / 2), YCENTER - 10, 10, 5, 0);
    // c
    img_draw_ring(red, XCENTER + 84 + ceil(i / 1.5), YCENTER - 10, 10, 5, 3);
    img_draw_ring(red, XCENTER + 84 + ceil(i / 1.5), YCENTER - 10, 10, 5, 4);
    // k2
    int k2x[11] = {XCENTER + 97 + i,  XCENTER + 102 + i, XCENTER + 102 + i, XCENTER + 107 + i,
                   XCENTER + 114 + i, XCENTER + 106 + i, XCENTER + 114 + i, XCENTER + 109 + i,
                   XCENTER + 102 + i, XCENTER + 102 + i, XCENTER + 97 + i};
    int k2y[11] = {YCENTER + 20, YCENTER + 20, YCENTER - 5,  YCENTER,      YCENTER,     YCENTER - 8,
                   YCENTER - 20, YCENTER - 20, YCENTER - 10, YCENTER - 20, YCENTER - 20};
    img_fill_polygon(red, k2x, k2y, 11);
    img_save_to_file();
  }
  return 0;
}

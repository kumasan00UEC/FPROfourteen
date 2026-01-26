// animate1 --- create animation using img lib.
#include <math.h>
#include "img.h"

int main(void) {
  struct color white = {255, 255, 255};
  struct color red = {233, 51, 68};
  struct color lightred = {245, 229, 236};

  int i;
  for (i = 0; i < 20; ++i) {
    img_clear();
    img_fillcircle(lightred, WIDTH / 2, HEIGHT / 2, 90 - i);
    img_fillcircle(white, WIDTH / 2, HEIGHT / 2, 60 - i);
    int ax[4] = {WIDTH / 2 + 20 - i, WIDTH / 2 + 40 - i, WIDTH / 2 + 60 - i, WIDTH / 2 + 40 - i};
    int ay[4] = {HEIGHT / 2 - 40 + i, HEIGHT / 2 - 40 + i, HEIGHT / 2 - 90 + i, HEIGHT / 2 - 90 + i};
    fill_scanline(lightred, ax, ay, 4);
    // Q
    img_fillcircle(red, 25 + i, HEIGHT / 2, 20);
    img_fillcircle(white, 25 + i, HEIGHT / 2, 15);
    int Qx[4] = {25 + i, 30 + i, 45 + i, 40 + i};
    int Qy[4] = {HEIGHT / 2 - 5, HEIGHT / 2 - 5, HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, Qx, Qy, 4);
    // u
    img_fillcircle(red, 66 + ceil(i / 1.5), HEIGHT / 2 - 10, 10);
    img_fillcircle(lightred, 66 + ceil(i / 1.5), HEIGHT / 2 - 10, 5);
    int ux1[4] = {56 + ceil(i / 1.5), 60 + ceil(i / 1.5), 60 + ceil(i / 1.5), 56 + ceil(i / 1.5)};
    int uy1[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    int ux2[4] = {61 + ceil(i / 1.5), 71 + ceil(i / 1.5), 71 + ceil(i / 1.5), 61 + ceil(i / 1.5)};
    int uy2[4] = {HEIGHT / 2 + 2, HEIGHT / 2 + 2, HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    int ux3[4] = {72 + ceil(i / 1.5), 76 + ceil(i / 1.5), 76 + ceil(i / 1.5), 72 + ceil(i / 1.5)};
    int uy3[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    fill_scanline(red, ux1, uy1, 4);
    fill_scanline(lightred, ux2, uy2, 4);
    fill_scanline(red, ux3, uy3, 4);
    // i
    img_fillcircle(red, 90 + ceil(i / 2), HEIGHT / 2 + 10, 3);
    int ix[4] = {88 + ceil(i / 2), 92 + ceil(i / 2), 92 + ceil(i / 2), 88 + ceil(i / 2)};
    int iy[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, ix, iy, 4);
    // z
    int zx1[4] = {105 + ceil(i / 4), 120 + ceil(i / 4), 120 + ceil(i / 4), 105 + ceil(i / 4)};
    int zy1[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 5, HEIGHT / 2 - 5};
    int zx2[4] = {118 + ceil(i / 4), 123 + ceil(i / 4), 108 + ceil(i / 4), 103 + ceil(i / 4)};
    int zy2[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    int zx3[4] = {105 + ceil(i / 4), 120 + ceil(i / 4), 120 + ceil(i / 4), 105 + ceil(i / 4)};
    int zy3[4] = {HEIGHT / 2 - 15, HEIGHT / 2  - 15, HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, zx1, zy1, 4);
    fill_scanline(red, zx2, zy2, 4);
    fill_scanline(red, zx3, zy3, 4);
    img_write();
  }
  for (i = 0; i < 20; ++i) {
    img_clear();
    img_fillcircle(lightred, WIDTH / 2, HEIGHT / 2, 70 + i);
    img_fillcircle(white, WIDTH / 2, HEIGHT / 2, 40 + i);
    int ax[4] = {WIDTH / 2 + i, WIDTH / 2 + 20 + i, WIDTH / 2 + 40 + i, WIDTH / 2 + 20 + i};
    int ay[4] = {HEIGHT / 2 - 20 - i, HEIGHT / 2 - 20 - i, HEIGHT / 2 - 70 - i, HEIGHT / 2 - 70 - i};
    fill_scanline(lightred, ax, ay, 4);
    // Q
    img_fillcircle(red, 45 - i, HEIGHT / 2, 20);
    img_fillcircle(white, 45 - i, HEIGHT / 2, 15);
    int Qx[4] = {45 - i, 50 - i, 65 - i, 60 - i};
    int Qy[4] = {HEIGHT / 2 - 5, HEIGHT / 2 - 5, HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, Qx, Qy, 4);
    // u
    img_fillcircle(red, 80 - ceil(i / 1.5), HEIGHT / 2 - 10, 10);
    img_fillcircle(lightred, 80 - ceil(i / 1.5), HEIGHT / 2 - 10, 5);
    int ux1[4] = {70 - ceil(i / 1.5), 74 - ceil(i / 1.5), 74 - ceil(i / 1.5), 70 - ceil(i / 1.5)};
    int uy1[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    int ux2[4] = {75 - ceil(i / 1.5), 85 - ceil(i / 1.5), 85 - ceil(i / 1.5), 75 - ceil(i / 1.5)};
    int uy2[4] = {HEIGHT / 2 + 2, HEIGHT / 2 + 2, HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    int ux3[4] = {86 - ceil(i / 1.5), 90 - ceil(i / 1.5), 90 - ceil(i / 1.5), 86 - ceil(i / 1.5)};
    int uy3[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 10, HEIGHT / 2 - 10};
    fill_scanline(red, ux1, uy1, 4);
    fill_scanline(lightred, ux2, uy2, 4);
    fill_scanline(red, ux3, uy3, 4);
    // i
    img_fillcircle(red, 100 - ceil(i / 2), HEIGHT / 2 + 10, 3);
    int ix[4] = {98 - ceil(i / 2), 102 - ceil(i / 2), 102 - ceil(i / 2), 98 - ceil(i / 2)};
    int iy[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, ix, iy, 4);
    // z
    int zx1[4] = {110 - ceil(i / 4), 125 - ceil(i / 4), 125 - ceil(i / 4), 110 - ceil(i / 4)};
    int zy1[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 5, HEIGHT / 2 - 5};
    int zx2[4] = {123 - ceil(i / 4), 128 - ceil(i / 4), 113 - ceil(i / 4), 108 - ceil(i / 4)};
    int zy2[4] = {HEIGHT / 2 , HEIGHT / 2 , HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    int zx3[4] = {110 - ceil(i / 4), 125 - ceil(i / 4), 125 - ceil(i / 4), 110 - ceil(i / 4)};
    int zy3[4] = {HEIGHT / 2 - 15, HEIGHT / 2  - 15, HEIGHT / 2 - 20, HEIGHT / 2 - 20};
    fill_scanline(red, zx1, zy1, 4);
    fill_scanline(red, zx2, zy2, 4);
    fill_scanline(red, zx3, zy3, 4);
    img_write();
  }
  return 0;
}

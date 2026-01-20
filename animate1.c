// animate1 --- create animation using img lib.
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
    img_write();
  }
  for (i = 0; i < 20; ++i) {
    img_clear();
    img_fillcircle(lightred, WIDTH / 2, HEIGHT / 2, 70 + i);
    img_fillcircle(white, WIDTH / 2, HEIGHT / 2, 40 + i);
    int ax[4] = {WIDTH / 2 + i, WIDTH / 2 + 20 + i, WIDTH / 2 + 40 + i, WIDTH / 2 + 20 + i};
    int ay[4] = {HEIGHT / 2 - 20 - i, HEIGHT / 2 - 20 - i, HEIGHT / 2 - 70 - i, HEIGHT / 2 - 70 - i};
    fill_scanline(lightred, ax, ay, 4);
    img_write();
  }
  return 0;
}

// animate1 --- create animation using img lib.
#include "img.h"

int main(void) {
  struct color c1 = {30, 255, 0};
  struct color c2 = {255, 0, 0};
  int i;
  for (i = 0; i < 20; ++i) {
    img_clear();
    img_fillcircle(c1, 20 + i * 8, 100, 20);
    img_write();
  }
  for (i = 0; i < 20; ++i) {
    img_clear();
    img_fillcircle(c2, 180, 100 + i * 5, 20 - i);
    img_write();
  }
  return 0;
}

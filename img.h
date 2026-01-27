#define WIDTH 300
#define XCENTER WIDTH / 2
#define HEIGHT 200
#define YCENTER HEIGHT / 2
struct color {
  unsigned char r, g, b;
};
void img_clear(void);
void img_write(void);
void img_putpixel(struct color c, int x, int y);
void img_fillcircle(struct color c, double x, double y, double r);
void fill_scanline(struct color c, int* ax, int* ay, int n);
void img_filldonuts(struct color c, double x, double y, double rmax, double rmin, int n);

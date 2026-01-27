#define WIDTH 300
#define XCENTER WIDTH / 2
#define HEIGHT 200
#define YCENTER HEIGHT / 2

struct Color {
  unsigned char r, g, b;
};

void img_clear_canvas(void);
void img_save_to_file(void);
void img_draw_pixel(struct Color pixel_color, int x_coord, int y_coord);
void img_draw_filled_circle(struct Color pixel_color, double center_x, double center_y, double radius);
void img_fill_polygon(struct Color pixel_color, int* vertices_x, int* vertices_y, int vertex_count);
void img_draw_ring(struct Color pixel_color, double center_x, double center_y, double outer_radius, double inner_radius,
                   int draw_mode);

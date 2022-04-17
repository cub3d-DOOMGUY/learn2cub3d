#include "engine.h"
#include "mlx_linux/mlx.h"

const extern int worldMap[24][24];

// void verLine(t_info* info, int x, int y1, int y2, int color) {
//   for (int y = y1; y <= y2; y++) {
//     mlx_pixel_put(info->mlx, info->win, x, y, color);
//   }
// }

void draw(t_info* info) {
  for (int y = 0; y < HEIGHT; y++)
    for (int x = 0; x < WIDTH; x++)
      info->img.data[y * WIDTH + x] =
          info->buf[y][x];  // NOTE: for some reason its WIDTH?

  mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

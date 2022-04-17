#include "engine.h"
#include "mlx_linux/mlx.h"

const extern int worldMap[24][24];

void verLine(t_info* info, int x, int y1, int y2, int color) {
  for (int y = y1; y <= y2; y++) {
    mlx_pixel_put(info->mlx, info->win, x, y, color);
  }
}

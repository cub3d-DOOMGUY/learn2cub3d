#include <math.h>
#include "color.h"
#include "engine.h"

const extern int worldMap[24][24];

bool is_raycast_refresh(t_keyinfo keyinfo) {
  return (keyinfo.is_up_pressed || keyinfo.is_down_pressed ||
          keyinfo.is_left_pressed || keyinfo.is_right_pressed);
}

t_colors get_color(int map_y, int map_x) {
  const t_colors colors[] = {
      COLOR__YELLOW, COLOR__RED, COLOR__GREEN, COLOR__BLUE, COLOR__WHITE,
  };
  const int index = worldMap[map_y][map_x];
  if (index > 4)
    return colors[0];
  return colors[index];
}

void raycast(t_engine* e) {
  clear_grid(e->buf);

  for (int x = 0; x < WIDTH; x++) {
    double cameraX = 2 * x / (double)WIDTH - 1;
    double rayDirX = e->dir.x + e->plane.x * cameraX;
    double rayDirY = e->dir.y + e->plane.y * cameraX;

    int mapX = (int)e->pos.x;
    int mapY = (int)e->pos.y;

    // length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    // length of ray from one x or y-side to next x or y-side
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    double perpWallDist;

    // what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    bool is_hit = false;  // was there a wall hit?
    int side;             // was a NS or a EW wall hit?

    if (rayDirX < 0) {
      stepX = -1;
      sideDistX = (e->pos.x - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - e->pos.x) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (e->pos.y - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - e->pos.y) * deltaDistY;
    }

    while (is_hit == false) {
      // jump to next map square, OR in x-direction, OR in y-direction
      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }
      // Check if ray has hit a wall
      if (worldMap[mapX][mapY] > 0)
        is_hit = true;
    }
    if (side == 0)
      perpWallDist = (mapX - e->pos.x + (1 - stepX) / 2) / rayDirX;
    else
      perpWallDist = (mapY - e->pos.y + (1 - stepY) / 2) / rayDirY;

    // Calculate HEIGHT of line to draw on screen
    int lineHeight = (int)(HEIGHT / perpWallDist);

    // calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
      drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
      drawEnd = HEIGHT - 1;

    int color = get_color(mapY, mapX);

    if (side == 1)
      color = color / 2;

    for (int y = drawStart; y < drawEnd; y++)
      e->buf[y][x] = color;
    // verLine(info, x, drawStart, drawEnd, color);
  }
}

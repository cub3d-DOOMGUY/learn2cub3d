#include <math.h>
#include "engine.h"

const extern int worldMap[24][24];

bool is_raycast_refresh(t_keyinfo keyinfo) {
  return (keyinfo.is_up_pressed || keyinfo.is_down_pressed ||
          keyinfo.is_left_pressed || keyinfo.is_right_pressed);
}

void raycast(t_engine* engine) {
  clear_grid(engine->buf);

  for (int x = 0; x < WIDTH; x++) {
    double cameraX = 2 * x / (double)WIDTH - 1;
    double rayDirX = engine->dirX + engine->planeX * cameraX;
    double rayDirY = engine->dirY + engine->planeY * cameraX;

    int mapX = (int)engine->posX;
    int mapY = (int)engine->posY;

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
      sideDistX = (engine->posX - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - engine->posX) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (engine->posY - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - engine->posY) * deltaDistY;
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
      perpWallDist = (mapX - engine->posX + (1 - stepX) / 2) / rayDirX;
    else
      perpWallDist = (mapY - engine->posY + (1 - stepY) / 2) / rayDirY;

    // Calculate HEIGHT of line to draw on screen
    int lineHeight = (int)(HEIGHT / perpWallDist);

    // calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
      drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
      drawEnd = HEIGHT - 1;

    int color;
    if (worldMap[mapY][mapX] == 1)
      color = 0xFF1111;
    else if (worldMap[mapY][mapX] == 2)
      color = 0x11FF11;
    else if (worldMap[mapY][mapX] == 3)
      color = 0x1111FF;
    else if (worldMap[mapY][mapX] == 4)
      color = 0xAAAAAA;
    else
      color = 0xFFFF11;

    if (side == 1)
      color = color / 2;

    for (int y = drawStart; y < drawEnd; y++)
      engine->buf[y][x] = color;
    // verLine(info, x, drawStart, drawEnd, color);
  }
}

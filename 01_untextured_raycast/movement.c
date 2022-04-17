#include <math.h>
#include <stdio.h>
#include "engine.h"
const extern int worldMap[24][24];

void handle_movement(t_engine* e) {
  t_keyinfo keyinfo = e->keyinfo;
  // printf("key status: %d %d %d %d\n", keyinfo.is_up_pressed,
  //        keyinfo.is_down_pressed, keyinfo.is_left_pressed,
  //        keyinfo.is_right_pressed);
  // TODO: make here better
  if (keyinfo.is_up_pressed) {
    t_vec new_pos = {e->posX + e->dirX * e->moveSpeed,
                     e->posY + e->dirY * e->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)e->posY])
      e->posX += e->dirX * e->moveSpeed;
    if (!worldMap[(int)e->posX][(int)new_pos.y])
      e->posY += e->dirY * e->moveSpeed;
  }
  // move backwards if no wall behind you
  if (keyinfo.is_down_pressed) {
    t_vec new_pos = {e->posX - e->dirX * e->moveSpeed,
                     e->posY - e->dirY * e->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)e->posY])
      e->posX -= e->dirX * e->moveSpeed;
    if (!worldMap[(int)e->posX][(int)new_pos.y])
      e->posY -= e->dirY * e->moveSpeed;
  }
  // rotate to the right
  if (keyinfo.is_right_pressed) {
    // both camera direction and camera plane must be rotated
    double oldDirX = e->dirX;
    e->dirX = e->dirX * cos(-e->rotSpeed) - e->dirY * sin(-e->rotSpeed);
    e->dirY = oldDirX * sin(-e->rotSpeed) + e->dirY * cos(-e->rotSpeed);

    double oldPlaneX = e->planeX;
    e->planeX = e->planeX * cos(-e->rotSpeed) - e->planeY * sin(-e->rotSpeed);
    e->planeY = oldPlaneX * sin(-e->rotSpeed) + e->planeY * cos(-e->rotSpeed);
  }
  // rotate to the left
  if (keyinfo.is_left_pressed) {
    // t_vec camera_vec = {e->dirX, e->dirY};
    // vec__rotate(&camera_vec, e->rotSpeed);
    // t_vec plane_vec = {e->planeX, e->planeY};
    // vec__rotate(&plane_vec, e->rotSpeed);
    double oldDirX = e->dirX;
    e->dirX = e->dirX * cos(e->rotSpeed) - e->dirY * sin(e->rotSpeed);
    e->dirY = oldDirX * sin(e->rotSpeed) + e->dirY * cos(e->rotSpeed);

    double oldPlaneX = e->planeX;
    e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
    e->planeY = oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
  }
}

// TODO: make all x and y into t_vec
void vec__rotate(t_vec* vec, double angle) {
  const double org_x = vec->x;
  const double org_y = vec->y;

  vec->x = org_x * cos(angle) - org_y * sin(angle);
  vec->y = org_x * sin(angle) + org_y * cos(angle);
}

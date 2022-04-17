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
    t_vec new_pos = {e->pos.x + e->dir.x * e->moveSpeed,
                     e->pos.y + e->dir.y * e->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)e->pos.y])
      e->pos.x += e->dir.x * e->moveSpeed;
    if (!worldMap[(int)e->pos.x][(int)new_pos.y])
      e->pos.y += e->dir.y * e->moveSpeed;
  }
  // move backwards if no wall behind you
  if (keyinfo.is_down_pressed) {
    t_vec new_pos = {e->pos.x - e->dir.x * e->moveSpeed,
                     e->pos.y - e->dir.y * e->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)e->pos.y])
      e->pos.x -= e->dir.x * e->moveSpeed;
    if (!worldMap[(int)e->pos.x][(int)new_pos.y])
      e->pos.y -= e->dir.y * e->moveSpeed;
  }
  // rotate to the right
  if (keyinfo.is_right_pressed) {
    // both camera direction and camera plane must be rotated
    double oldDirX = e->dir.x;
    e->dir.x = e->dir.x * cos(-e->rotSpeed) - e->dir.y * sin(-e->rotSpeed);
    e->dir.y = oldDirX * sin(-e->rotSpeed) + e->dir.y * cos(-e->rotSpeed);

    double oldPlaneX = e->plane.x;
    e->plane.x = e->plane.x * cos(-e->rotSpeed) - e->plane.y * sin(-e->rotSpeed);
    e->plane.y = oldPlaneX * sin(-e->rotSpeed) + e->plane.y * cos(-e->rotSpeed);
  }
  // rotate to the left
  if (keyinfo.is_left_pressed) {
    // t_vec camera_vec = {e->dir.x, e->dir.y};
    // vec__rotate(&camera_vec, e->rotSpeed);
    // t_vec plane_vec = {e->plane.x, e->plane.y};
    // vec__rotate(&plane_vec, e->rotSpeed);
    double oldDirX = e->dir.x;
    e->dir.x = e->dir.x * cos(e->rotSpeed) - e->dir.y * sin(e->rotSpeed);
    e->dir.y = oldDirX * sin(e->rotSpeed) + e->dir.y * cos(e->rotSpeed);

    double oldPlaneX = e->plane.x;
    e->plane.x = e->plane.x * cos(e->rotSpeed) - e->plane.y * sin(e->rotSpeed);
    e->plane.y = oldPlaneX * sin(e->rotSpeed) + e->plane.y * cos(e->rotSpeed);
  }
}

// TODO: make all x and y into t_vec
void vec__rotate(t_vec* vec, double angle) {
  const double org_x = vec->x;
  const double org_y = vec->y;

  vec->x = org_x * cos(angle) - org_y * sin(angle);
  vec->y = org_x * sin(angle) + org_y * cos(angle);
}

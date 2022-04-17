#include <math.h>
#include "engine.h"

const extern int worldMap[24][24];

void handle_move(t_info* info) {
  t_keyinfo keyinfo = info->keyinfo;

  // TODO: make here better
  if (keyinfo.is_up_pressed) {
    t_vec new_pos = {info->posX + info->dirX * info->moveSpeed,
                     info->posY + info->dirY * info->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)info->posY])
      info->posX += info->dirX * info->moveSpeed;
    if (!worldMap[(int)info->posX][(int)new_pos.y])
      info->posY += info->dirY * info->moveSpeed;
  }
  // move backwards if no wall behind you
  if (keyinfo.is_down_pressed) {
    t_vec new_pos = {info->posX - info->dirX * info->moveSpeed,
                     info->posY - info->dirY * info->moveSpeed};
    if (!worldMap[(int)new_pos.x][(int)info->posY])
      info->posX -= info->dirX * info->moveSpeed;
    if (!worldMap[(int)info->posX][(int)new_pos.y])
      info->posY -= info->dirY * info->moveSpeed;
  }
  // rotate to the right
  if (keyinfo.is_right_pressed) {
    // both camera direction and camera plane must be rotated
    double oldDirX = info->dirX;
    info->dirX =
        info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
    info->dirY =
        oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
    double oldPlaneX = info->planeX;
    info->planeX = info->planeX * cos(-info->rotSpeed) -
                   info->planeY * sin(-info->rotSpeed);
    info->planeY =
        oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
  }
  // rotate to the left
  if (keyinfo.is_left_pressed) {
    // both camera direction and camera plane must be rotated
    double oldDirX = info->dirX;
    info->dirX =
        info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
    info->dirY =
        oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
    double oldPlaneX = info->planeX;
    info->planeX =
        info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
    info->planeY =
        oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
  }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarf <youkim@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2022/04/17 13:23:53 by scarf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "key_linux.h"
#include "mlx_linux/mlx.h"
#include "x11_enums.h"

const extern int worldMap[24][24];

int main_loop(t_info* info) {
  handle_move(info);
  calc(info);
  // mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

  return (0);
}

int key_release(int key, t_info* info) {
  info->keyinfo = (t_keyinfo){false, false, false, false};
  return 0;
}

void handle_move(t_info* info) {
  t_keyinfo keyinfo = info->keyinfo;

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
int key_press(int key, t_info* info) {
  if (key == K_W)
    info->keyinfo.is_up_pressed = true;
  if (key == K_S)
    info->keyinfo.is_down_pressed = true;
  if (key == K_A)
    info->keyinfo.is_left_pressed = true;
  if (key == K_D)
    info->keyinfo.is_right_pressed = true;
  if (key == K_ESC)
    exit(0);

  return (0);
}

int main(void) {
  t_info info;
  info.mlx = mlx_init();

  info.posX = 12;
  info.posY = 5;
  info.dirX = -1;
  info.dirY = 0;
  info.planeX = 0;
  info.planeY = 0.66;
  info.moveSpeed = 0.05;
  info.rotSpeed = 0.05;
  info.keyinfo = (t_keyinfo){false, false, false, false};

  info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "mlx");

  mlx_loop_hook(info.mlx, &main_loop, &info);
  mlx_hook(info.win, X11EVENTS__KeyPress, X11MASKS__KeyPressMask, &key_press,
           &info);
  mlx_hook(info.win, X11EVENTS__KeyRelease, X11MASKS__KeyReleaseMask,
           &key_release, &info);
  //   mlx_do_key_autorepeaton(info.mlx);
  mlx_loop(info.mlx);
}

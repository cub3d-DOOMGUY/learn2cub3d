/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarf <youkim@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2022/04/17 12:10:02 by scarf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "key_linux.h"
#include "mlx_linux/mlx.h"

const extern int worldMap[24][24];

void verLine(t_info* info, int x, int y1, int y2, int color) {
  int y;

  y = y1;
  while (y <= y2) {
    mlx_pixel_put(info->mlx, info->win, x, y, color);
    y++;
  }
}

int main_loop(t_info* info) {
  calc(info);
  // mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

  return (0);
}

int key_press(int key, t_info* info) {
  if (key == K_W) {
    if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)]
                 [(int)(info->posY)])
      info->posX += info->dirX * info->moveSpeed;
    if (!worldMap[(int)(info->posX)]
                 [(int)(info->posY + info->dirY * info->moveSpeed)])
      info->posY += info->dirY * info->moveSpeed;
  }
  // move backwards if no wall behind you
  if (key == K_S) {
    if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)]
                 [(int)(info->posY)])
      info->posX -= info->dirX * info->moveSpeed;
    if (!worldMap[(int)(info->posX)]
                 [(int)(info->posY - info->dirY * info->moveSpeed)])
      info->posY -= info->dirY * info->moveSpeed;
  }
  // rotate to the right
  if (key == K_D) {
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
  if (key == K_A) {
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

  info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "mlx");

  mlx_loop_hook(info.mlx, &main_loop, &info);
  mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);

  mlx_loop(info.mlx);
}

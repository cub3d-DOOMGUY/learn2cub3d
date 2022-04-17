/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarf <youkim@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2022/04/17 14:40:15 by scarf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

const extern int worldMap[24][24];

bool is_refresh(t_keyinfo keyinfo) {
  return (keyinfo.is_up_pressed || keyinfo.is_down_pressed ||
          keyinfo.is_left_pressed || keyinfo.is_right_pressed);
}

int main_loop(t_info* info) {
  if (is_refresh(info->keyinfo))
    raycast(info);
  draw(info);
  handle_movement(info);

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
  info.moveSpeed = 0.02;
  info.rotSpeed = 0.008;
  info.keyinfo = (t_keyinfo){false, false, false, false};

  info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "mlx");

  info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
  info.img.data = (int*)mlx_get_data_addr(info.img.img, &info.img.bpp,
                                          &info.img.size_l, &info.img.endian);

  raycast(&info);
  mlx_loop_hook(info.mlx, &main_loop, &info);
  mlx_hook(info.win, X11EVENTS__KeyPress, X11MASKS__KeyPressMask, &key_press,
           &info);
  mlx_hook(info.win, X11EVENTS__KeyRelease, X11MASKS__KeyReleaseMask,
           &key_release, &info);
  mlx_loop(info.mlx);
}

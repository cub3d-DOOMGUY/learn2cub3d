/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarf <youkim@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2022/04/17 14:13:04 by scarf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

const extern int worldMap[24][24];

int main_loop(t_info* info) {
  clear_grid(info->buf);
  calc(info);
  draw(info);
  handle_move(info);
  // mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

  return (0);
}

int key_release(t_keycode key, t_info* info) {
  (void)key;
  info->keyinfo = (t_keyinfo){false, false, false, false};
  return 0;
}


int key_press(t_keycode key, t_info* info) {
  if (key == KEY_W)
    info->keyinfo.is_up_pressed = true;
  if (key == KEY_S)
    info->keyinfo.is_down_pressed = true;
  if (key == KEY_A)
    info->keyinfo.is_left_pressed = true;
  if (key == KEY_D)
    info->keyinfo.is_right_pressed = true;
  if (key == KEY_ESC)
    exit(0);

  return (0);
}

void clear_grid(int grid[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      grid[i][j] = 0;
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
  info.moveSpeed = 0.03;
  info.rotSpeed = 0.02;
  info.keyinfo = (t_keyinfo){false, false, false, false};

  // use clear_grid on info.buf

  // for (int i = 0; i < HEIGHT; i++)
  //   for (int j = 0; j < WIDTH; j++)
  //     info.buf[i][j] = 0;

  info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "mlx");

  info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
  info.img.data = (int*)mlx_get_data_addr(info.img.img, &info.img.bpp,
                                          &info.img.size_l, &info.img.endian);

  mlx_loop_hook(info.mlx, &main_loop, &info);
  mlx_hook(info.win, X11EVENTS__KeyPress, X11MASKS__KeyPressMask, &key_press,
           &info);
  mlx_hook(info.win, X11EVENTS__KeyRelease, X11MASKS__KeyReleaseMask,
           &key_release, &info);
  mlx_loop(info.mlx);
}

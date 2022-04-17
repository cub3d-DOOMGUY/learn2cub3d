#ifndef __ENGINE_H__
#define __ENGINE_H__

#define mapWidth 24
#define mapHeight 24
#define WIDTH 640
#define HEIGHT 480

#include <stdbool.h>
#include "key_linux.h"
#include "mlx_linux/mlx.h"
#include "x11_enums.h"
typedef struct s_vec {
  double x;
  double y;
} t_vec;

typedef struct s_keyinfo {
  bool is_up_pressed;
  bool is_down_pressed;
  bool is_left_pressed;
  bool is_right_pressed;
} t_keyinfo;

typedef struct s_info {
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  void* mlx;
  void* win;
  void* buffer;
  double moveSpeed;
  double rotSpeed;
  t_keyinfo keyinfo;
} t_info;

// clang-format off
//@func
/*
** < draw.c > */

void	verLine(t_info* info, int x, int y1, int y2, int color);
/*
** < main.c > */

int		main_loop(t_info* info);
int		key_release(t_keycode key, t_info* info);
int		key_press(t_keycode key, t_info* info);
/*
** < movement.c > */

void	handle_move(t_info* info);
/*
** < util.c > */

void	calc(t_info* info);
#endif  // __ENGINE_H__

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdbool.h>
#include "key_linux.h"
#include "mlx_linux/mlx.h"
#include "x11_enums.h"

typedef enum e_config {
  mapWidth = 24,
  mapHeight = 24,
  WIDTH = 640,
  HEIGHT = 480,
} t_config;

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

typedef struct s_img {
  void* img;
  int* data;

  int size_l;
  int bpp;
  int endian;
  int img_width;
  int img_height;
} t_img;

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
  t_img img;
  int buf[HEIGHT][WIDTH];
  t_keyinfo keyinfo;
} t_info;

// clang-format off
//@func
/*
** < draw.c > */

void	draw(t_info* info);
void	clear_grid(int grid[HEIGHT][WIDTH]);
/*
** < keyinput.c > */

int		key_release(t_keycode key, t_info* info);
int		key_press(t_keycode key, t_info* info);
/*
** < main.c > */

bool	is_refresh(t_keyinfo keyinfo);
int		main_loop(t_info* info);
/*
** < movement.c > */

void	handle_movement(t_info* info);
/*
** < raycast.c > */

void	raycast(t_info* info);
#endif  // __ENGINE_H__

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdbool.h>
#include "engine_types.h"
#include "key_linux.h"
#include "mlx_linux/mlx.h"
#include "x11_enums.h"

typedef enum e_config {
  mapWidth = 24,
  mapHeight = 24,
  WIDTH = 640,
  HEIGHT = 480,
} t_config;

typedef struct s_engine {
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
} t_engine;

// clang-format off
//@func
/*
** < draw.c > */

void	draw(t_engine* info);
void	clear_grid(int grid[HEIGHT][WIDTH]);
/*
** < keyinput.c > */

int		key_release(t_keycode key, t_engine* info);
int		key_press(t_keycode key, t_engine* info);
/*
** < main.c > */

int		main_loop(t_engine* engine);
/*
** < movement.c > */

void	handle_movement(t_engine* e);
void	vec__rotate(t_vec* vec, double angle);
/*
** < raycast.c > */

bool	is_raycast_refresh(t_keyinfo keyinfo);
void	raycast(t_engine* engine);
#endif  // __ENGINE_H__

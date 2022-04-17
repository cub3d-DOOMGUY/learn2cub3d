#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdbool.h>
#include "key_linux.h"
#include "mlx_linux/mlx.h"
#include "types__engine.h"
#include "x11_enums.h"

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
** < movement.c > */

void	handle_movement(t_engine* e);
void	vec__rotate(t_vec* vec, double angle);
#endif  // __ENGINE_H__

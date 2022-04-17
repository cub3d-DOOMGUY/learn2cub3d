#ifndef __ENGINE_H__
#define __ENGINE_H__

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17
#define mapWidth 24
#define mapHeight 24
#define WIDTH 640
#define HEIGHT 480

typedef struct s_info {
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  void* mlx;
  void* win;
  double moveSpeed;
  double rotSpeed;
} t_info;

// clang-format off
//@func
/*
** < main.c > */

void	verLine(t_info* 	info, int x, int y1, int y2, int color);
int		main_loop(t_info* info);
int		key_press(int key, t_info* info);
/*
** < util.c > */

void	calc(t_info* info);
#endif  // __ENGINE_H__

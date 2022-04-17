#ifndef __MLX_TYPES_H__
#define __MLX_TYPES_H__

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

typedef enum e_direction { UP, DOWN, LEFT, RIGHT } t_direction;
typedef enum e_sign { PLUS = 1, MINUS = -1 } t_sign;
#endif  // __MLX_TYPES_H__

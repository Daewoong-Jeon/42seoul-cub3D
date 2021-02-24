/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:02 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 16:35:24 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define GREY_COLOR 0x00808080
# define WHITE_COLOR 0x00FFFFFF
# define BLUE_COLOR 0x000000FF
# define RED_COLOR 0x00FF0000
# define BLACK_COLOR 0x00000000
# define SKY_COLOR 0x0087CEEB
# define GREEN_COLOR 0x00008000

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53

# define PI 3.14159265359

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.0436332313
# define IMAGE_WIDTH 64
# define IMAGE_HEIGHT 64

# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

typedef struct	s_cal
{
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perpwalldist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texnum;
	double		wall_x;
	int			tex_x;
	double		step;
	double		texpos;
	double		sprite_x;
	double		sprite_y;
	double		invdet;
	double		transform_x;
	double		transform_y;
	int			spritescreen_x;
	int			vmovescreen;
	int			spriteheight;
	int			drawstart_y;
	int			drawend_y;
	int			spritewidth;
	int			drawstart_x;
	int			drawend_x;
	int			tex_y;
}				t_cal;

typedef struct	s_pair
{
	double	first;
	int		second;
}				t_pair;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_struct
{
	void		*mlx;
	void		*win;
	double		user_x;
	double		user_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			**texture_arr;
	int			map_size_x;
	int			map_size_y;
	int			window_size_x;
	int			window_size_y;
	char		**map;
	int			**buf;
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			image_width;
	int			image_height;
	double		*zbuffer;
	int			parse_tmp;
	int			floor_color;
	int			ceil_color;
	int			num_sprite;
	int			error;
	int			last_line;
	t_sprite	*sprite;
	int			w_key;
	int			a_key;
	int			s_key;
	int			d_key;
	int			left_arrow;
	int			right_arrow;
	char		ad_key;
	char		ws_key;
	char		arrow_key;
	int			bmp_flag;
	int			pos_tmp;
	char		**map_tmp1;
	char		**map_tmp2;
	int			line_len;
	int			tem;
}				t_struct;

void			dont_move_sub(t_struct *tmp, double *tmp_x, double *tmp_y);
void			wsad_move(t_struct *tmp);
void			key_release_rl(int key, t_struct *tmp);
void			key_press_rl(int key, t_struct *tmp);
int				parse_color_sub(t_struct *tmp, char *line, int ret_result);
void			ft_tool2_keysave_set(int *key_adws, char *key_save_adws,
		int i, char j);
int				dont_move(t_struct *tmp);
void			rotate_vector(t_struct *tmp, double angle);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			middle_line_sub(t_struct *tmp, char *line, char *map_tmp);
void			double_pointer_free(char **mem, int size);
void			ft_putstr(char *str);
void			parse_map_sub(t_struct *tmp, int fd, int *i, char *line);
char			**ft_strdup_2(char **arr, int size);
int				white_space(char line);
void			sort_order(t_pair *orders, int amount);
void			sortsprites(int *order, double *dist, int amount);
void			load_image(t_struct *tmp, int *texture, char *path);
int				malloc_buf(t_struct *tmp);
int				check_arg(t_struct *tmp, int argc, char **argv);
int				**init_intarr(t_struct *tmp, int x, int y);
void			init_sprite(t_struct *tmp);
void			struct_init(t_struct *tmp);
int				save_bmp(t_struct *tmp);
void			input_wall_texture_init_sub(t_struct *tmp, t_cal *st_cal);
void			input_wall_texture_init(t_struct *tmp, t_cal *st_cal);
void			input_wall_texture(t_struct *tmp, t_cal *st_cal, int x);
void			cal_dist_sub(t_struct *tmp, t_cal *st_cal);
void			cal_dist_init(t_struct *tmp, t_cal *st_cal);
void			cal(t_struct *tmp);
void			load_image(t_struct *tmp, int *texture, char *path);
int				white_space(char line);
void			first_last_line(char *line, t_struct *tmp, char *map_tmp);
void			middle_line(char *line, t_struct *tmp, char *map_tmp);
int				hexa_to_int(char *input);
char			*to_hexa(int input);
int				parse_cub(int fd, t_struct *tmp);
int				key_press(int key, t_struct *tmp);
int				key_release(int key, t_struct *tmp);
int				user_move(t_struct *tmp);
void			rotate_vector(t_struct *tmp, double angle);
int				dont_move(t_struct *tmp);
char			**ft_split(char const *str, char charset);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);

#endif

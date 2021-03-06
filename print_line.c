/*
** print_line.c for fdf in /home/chapui_s/travaux/fdf/fdf
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Fri Dec  6 20:58:37 2013 chapui_s
** Last update Sun Dec  8 22:34:27 2013 chapui_s
*/

#include <stddef.h>
#include "fdf.h"

t_line		get_coord(int x1, int y1, int x2, int y2)
{
  t_line	coord;

  coord.x1 = x1;
  coord.x2 = x2;
  coord.y1 = y1;
  coord.y2 = y2;
  return (coord);
}

void		my_pixel_put_to_image(int x, int y, unsigned int color,
				      t_infos_mlx *infos_mlx)
{
  void		*mlx_ptr;
  size_t	pixel_ptr;

  mlx_ptr = infos_mlx->mlx_ptr;
  if (y <= HEIGHT && y >= 0 && x >= 0 && x <= WIDTH)
  {
    pixel_ptr = ((WIDTH * y) + x) * (infos_mlx->bpp / 8);
    if (color == 0)
      color = mlx_get_color_value(mlx_ptr, 0x9000FF);
    else
      color = mlx_get_color_value(mlx_ptr, 0x000000);
    if (infos_mlx->endian == 0)
    {
      (infos_mlx->data + pixel_ptr)[2] = color >> 16;
      (infos_mlx->data + pixel_ptr)[1] = (color & 0x00FF00) >> 8;
      (infos_mlx->data + pixel_ptr)[0] = color & 0x0000FF;
    }
    else
    {
      (infos_mlx->data + pixel_ptr)[0] = color >> 16;
      (infos_mlx->data + pixel_ptr)[1] = (color & 0x00FF00) >> 8;
      (infos_mlx->data + pixel_ptr)[2] = color & 0x0000FF;
    }
  }
}

void	print_line(t_line c, t_infos_mlx *infos_mlx, unsigned int color)
{
  int	tmp;

  if (transform_coord(&c, infos_mlx) == -1)
    return ;
  if ((c.x1 <= c.x2) && ((c.x2 - c.x1) >= val_abs(c.y2 - c.y1)))
  {
    tmp = c.x1;
    while (tmp <= c.x2)
    {
      my_pixel_put_to_image(tmp, c.y1 + ((c.y2 - c.y1) * (tmp - c.x1))
			    / (c.x2 - c.x1), color, infos_mlx);
      tmp = tmp + 1;
    }
    return ;
  }
  (c.y1 > c.y2) ? (swap_int(&(c.x1), &(c.x2))) : (0);
  (c.y1 > c.y2) ? (swap_int(&(c.y1), &(c.y2))) : (0);
  tmp = c.y1;
  while (tmp < c.y2)
  {
    my_pixel_put_to_image(c.x1 + ((c.x2 - c.x1) * (tmp - c.y1))
			  / (c.y2 - c.y1), tmp, color, infos_mlx);
    tmp = tmp + 1;
  }
}

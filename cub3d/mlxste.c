/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxste.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:04:23 by srapuano          #+#    #+#             */
/*   Updated: 2024/05/14 16:50:03 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_handler(t_data *data)
{
	data->window = mlx_new_window(data->mlx, data->res_w,
			data->res_h, "CUB3D");
	mlx_mouse_move(data->mlx, data->window,
		(data->res_w / 2) - 1, (data->res_h / 2) - 1);
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_get_pos(data->mlx, data->window, &data->def_x, &data->def_y);
	mlx_hook(data->window, 2, 1L << 0, keys_control_movements, data);
	mlx_hook(data->window, 3, 1L << 1, keys_control_released, data);
	mlx_hook(data->window, 17, 0, close_game, (void *)data);
	mlx_loop_hook(data->mlx, nullifiereee, (void *)data);
	mlx_loop(data->mlx);
}

int	close_game(void *data)
{
	t_data	*tmp;

	tmp = (t_data *)data;
	freerer(tmp);
	exit (0);
}

int	nullifiereee(void *data)
{
	t_data	*tmp;

	tmp = (t_data *)data;
	check_movement(tmp);
	mlx_mouse_get_pos(tmp->mlx, tmp->window, &tmp->mouse_x, &tmp->mouse_y);
	turn_mouse(data);
	raycasting(tmp);
	print_ani(tmp, 0, 0, 0);
	add_minimap(data, 0, 0);
	mlx_put_image_to_window(tmp->mlx, tmp->window, tmp->image.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxste.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:04:23 by srapuano          #+#    #+#             */
/*   Updated: 2024/04/27 09:36:37 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_handler(t_data *data)
{
	data->window = mlx_new_window(data->mlx, data->res_w,
			data->res_h, "CUB3D");
	mlx_key_hook(data->window, keys_control, data);
	mlx_hook(data->window, 17, 0, close_game, (void *)data);
	//raycasting(data);
	//mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	mlx_loop_hook(data->mlx, nullifiereee, (void *)data);
	mlx_loop(data->mlx);
}

int	close_game(void *data)
{
	freerer((t_data *)data);
	exit (0);
}

int	nullifiereee(void *data)
{
	t_data	*tmp;

	tmp = (t_data *)data;
	raycasting(tmp);
	mlx_put_image_to_window(tmp->mlx, tmp->window, tmp->image.img, 0, 0);
	return (0);
}

void	print_map(t_data *data)
{
	char *img;

//questa roba va fatta quando andiamo a controllare tutte le texure e le salviamo
	//data->text.ceiling = mlx_new_image(data->mlx,
	//		(data->res_w / 2), (data->res_h / 2));
	//data->text.floor = mlx_new_image(data->mlx,
	//		(data->res_w / 2), (data->res_h / 2));
	//img = mlx_get_data_addr(data->text.ceiling, &data->text.bits_per_pixel,
	//		&data->text.size_line, &data->text.endian);
	//*(unsigned int *)img = data->ceiling_color;
	//img = mlx_get_data_addr(data->text.floor, &data->text.bits_per_pixel,
	//		&data->text.size_line, &data->text.endian);
	//*(unsigned int *)img = data->floor_color;
	//mlx_put_image_to_window(data->mlx, data->window, data->text.ceiling, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->window, data->text.floor, 639, 359);
	// tutta questa roba serve a modificare il colore di un solo pixel in particolare,
	//bisogna quindi anche per il ceiling e per il floor calcolare pixel per pixel,
	//la soluzione più semplice è riempire di pixel il tutto, e pio andare a modificare
	// quelli dei muri.
	return ;
}
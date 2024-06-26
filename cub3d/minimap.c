/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratesco <fratesco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:02:01 by fratesco          #+#    #+#             */
/*   Updated: 2024/05/01 15:02:36 by fratesco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_minimap(t_data *data, double i, double j)
{
	i = 0;
	while (data->map[(int)floor(i)])
	{
		j = 0;
		while (data->map[(int)floor(i)][(int)floor(j)])
		{
			if ((int)floor(i) == ((int)floor(data->player->x))
				&& ((int)floor(j) == ((int)floor(data->player->y))))
				add_pixel_repeat(data, (int)(j * 10), (int)(i * 9.9), 0x00ff00);
			else if (data->map[(int)floor(i)][(int)floor(j)] == '1'
					|| data->map[(int)floor(i)][(int)floor(j)] == ' ')
				add_pixel_repeat(data, (int)(j * 10), (int)(i * 9.9), 0x969696);
			else if (data->map[(int)floor(i)][(int)floor(j)] == '0'
					|| data->map[(int)floor(i)][(int)floor(j)]
					== data->player->direction)
				add_pixel_repeat(data, (int)(j * 10), (int)(i * 9.9), 0xffffff);
			else if (data->map[(int)floor(i)][(int)floor(j)] == '2')
				add_pixel_repeat(data, (int)(j * 10), (int)(i * 9.9), 0xff0000);
			else if (data->map[(int)floor(i)][(int)floor(j)] == '3')
				add_pixel_repeat(data, (int)(j * 10), (int)(i * 9.9), 0x0000ff);
			j += 0.1;
		}
		i += 0.1;
	}
}

void	add_pixel_repeat(t_data *data, int x, int y, int color)
{
	int	ratio_x;
	int	ratio_y;

	ratio_x = ((int)data->res_w / 720);
	while (ratio_x >= 0)
	{
		ratio_y = ((int)data->res_h / 1280);
		while (ratio_y >= 0)
		{
			my_mlx_pixel_put(data, x + ratio_x, y + ratio_y, color);
			ratio_y--;
		}
		ratio_x--;
	}
}

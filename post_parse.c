/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:07:48 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/12 19:11:50 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	repare_value(t_data *data)
{
	if (data->t_to_die < data->t_to_eat)
	{
		data->t_to_eat = data->t_to_die + 1;
	}
	if (data->t_to_die < data->t_to_sleep)
	{
		data->t_to_sleep = data->t_to_die + 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:44:24 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/13 16:19:54 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_atoi(const char *str)
{
	char	sign;
	int		result;

	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	is_a_number(int argc, char **argv)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	while (argc--)
	{
		while (argv[j][k])
		{
			if (!ft_isdigit(argv[j][k]))
				return (0);
			k++;
		}
		j++;
		k = 0;
	}
	return (1);
}

static int	is_parsing_ok(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || !is_a_number(argc - 1, argv))
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}

int	parse_value(int argc, char **argv, t_data *data)
{
	if (!is_parsing_ok(argc, argv))
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		data->nbr_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_must_eat = -1;
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	data->stop = 0;
	if (data->nbr_of_philo < 1 || data->nbr_of_philo > 200 \
			|| data->t_to_die < 60 || data->t_to_eat < 60 \
			|| data->t_to_sleep < 60 || data->nbr_must_eat == 0)
	{
		printf("Error\n");
		return (0);
	}
	if (data->nbr_must_eat == -1)
		return (0);
	repare_value(data);
	return (1);
}

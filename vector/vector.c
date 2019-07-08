/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:15:21 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/04 17:15:23 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void		push_back(t_vector **victor, int data)
{
	int *temp;
	int	i;

	i = -1;
	if (!(*victor)->array)
	{
		++i;
		(*victor)->array = (int*)malloc(sizeof(int));
		if (!(*victor)->array)
			exit(1);
		(*victor)->array[i] = data;
	}
	else
	{
		temp = (int*)malloc(sizeof(int) * ((*victor)->lenght + 1));
		if (!temp)
			exit(1);
		while (++i < (*victor)->lenght)
			temp[i] = (*victor)->array[i];
		temp[i] = data;
		free((*victor)->array);
		(*victor)->array = temp;
		(*victor)->curr_arr++;
	}
	(*victor)->lenght++;
	(*victor)->curr_left = (*victor)->array[i];
}

static void		pop(t_vector **victor, int number_del)
{
	int *temp;
	int	i;

	i = -1;
	if (!(*victor) || number_del <= 0)
		return ;
	if ((*victor)->lenght - 1 == 0)
	{
		free(victor);
		(*victor) = init_vector();
		return ;
	}
	temp = (int*)malloc(sizeof(int) * ((*victor)->lenght - 1));
	if (!temp)
		exit(1);
	if (number_del > (*victor)->lenght)
		number_del = (*victor)->lenght - 1;
	while (++i < number_del)
		temp[i] = (*victor)->array[i];
	while (++i < (*victor)->lenght)
		temp[i - 1] = (*victor)->array[i];
	free((*victor)->array);
	(*victor)->array = temp;
	(*victor)->lenght--;
	(*victor)->curr_left = (*victor)->array[number_del - 1];
	(*victor)->curr_arr--;
}

t_vector	 *copy(struct s_vector *victor)
{
	t_vector 	*victor_ret;
	int			i;

	victor_ret = (t_vector*)malloc(sizeof(t_vector));
	if (!victor_ret)
		exit(1);
	victor_ret->push_back = &push_back;
	victor_ret->pop = &pop;
	victor_ret->copy = &copy;
	if (victor->lenght)
	{
		victor_ret->array = (int*)malloc(sizeof(int) * victor->lenght);
		if (!victor_ret->array)
			exit(1);
		i = -1;
		while (++i < victor->lenght)
			victor_ret->array[i] = victor->array[i];
	}
	else
		victor_ret->array = victor->array;
	victor_ret->curr_arr = victor->curr_arr;
	victor_ret->lenght = victor->lenght;
	victor_ret->curr_left = victor->curr_left;
	return (victor_ret);
}


t_vector	 *init_vector(void)
{
	t_vector *victor;

	victor = (t_vector*)malloc(sizeof(t_vector));
	if (!victor)
		exit(1);
	victor->push_back = &push_back;
	victor->pop = &pop;
	victor->copy = &copy;

	victor->array = NULL;
	victor->curr_arr = 0;
	victor->lenght = 0;
	victor->curr_left = 0;

	return (victor);
}

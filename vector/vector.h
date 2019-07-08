/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:15:47 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/04 17:15:48 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "stdlib.h"

typedef struct 			s_vector
{
	int             	*array;
	int             	lenght;
	int             	curr_arr;
	int             	curr_left;
	void            	(*push_back)(struct s_vector**, int);
	void            	(*pop)(struct s_vector**, int);
	struct s_vector*	(*copy)(struct s_vector*);

}               		t_vector;

t_vector 				*init_vector(void);



#endif

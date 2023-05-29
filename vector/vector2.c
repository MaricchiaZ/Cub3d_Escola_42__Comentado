/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:10:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/17 09:50:07 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	calculate_matrix(float matrix[4][4], t_vector old, t_vector *new)
{
	new->x = old.x * matrix[0][0] + old.y * matrix[0][1] + old.y * matrix[0][2];
	new->y = old.x * matrix[1][0] + old.y * matrix[1][1] + old.y * matrix[1][2];
	new->z = old.x * matrix[2][0] + old.y * matrix[2][1] + old.y * matrix[2][2];
}

void	vector_magnitude(t_vector *v)
{
	v->magnitude = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

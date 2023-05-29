/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:57:17 by gissao-m          #+#    #+#             */
/*   Updated: 2023/04/26 18:37:57 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_sum(t_vector *v1, t_vector *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
}

void	vector_subtraction(t_vector *v1, t_vector *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
}

void	vector_multiplication(t_vector *v1, t_vector *v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
}

void	vector_division(t_vector *v1, t_vector *v2)
{
	v1->x /= v2->x;
	v1->y /= v2->y;
}

void	vector_scale(t_vector *v1, float scale)
{
	v1->x *= scale;
	v1->y *= scale;
}

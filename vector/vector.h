/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:55:18 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/17 08:57:19 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	float			x;
	float			y;
	float			z;
	float			magnitude;
	struct s_vector	*next;
}	t_vector;

void	vector_sum(t_vector *v1, t_vector *v2);
void	vector_subtraction(t_vector *v1, t_vector *v2);
void	vector_multiplication(t_vector *v1, t_vector *v2);
void	vector_division(t_vector *v1, t_vector *v2);
void	vector_scale(t_vector *v1, float scale);
void	calculate_matrix(float matrix[4][4], t_vector old, t_vector *new);
void	vector_magnitude(t_vector *v);

#endif

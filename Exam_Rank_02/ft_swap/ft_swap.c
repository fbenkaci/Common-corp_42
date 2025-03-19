/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:14 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/14 09:25:15 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	printf("%d, %d", *a, *b);
}

// int	main(void)
// {
// 	int *aa;
// 	int *bb;
//     int a = 6;
//     int b = 7;
//     aa = &a;
//     bb = &b;
// 	ft_swap(aa, bb);
// }
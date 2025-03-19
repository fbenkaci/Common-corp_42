/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:08:51 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 12:34:13 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct push_swap
{
	int		nb_elemt;
	char	**dest;
	int		*nb;
	char	int_min[11];
	char	int_max[11];
}			t_data;

int			check_if_numbers(char **av);
int			check_doublon(char **av, int ac);
int			check_doublon_string(char **av, t_data *data);
char		*remove_extra_spaces(char *str);
int			convert_to_int(t_data *data);
int			is_valid_int(char *str);
int			check_if_digit(char **av, int i, int j);
int			check_sign(char **av, int i, int j);
int			check_duplicate_nb(t_data *data);
void		ft_free(t_data *data);

#endif
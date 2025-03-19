/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:01:03 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/21 09:03:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST.H
# define FT_LIST .H

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

#endif
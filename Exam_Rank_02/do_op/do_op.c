/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:02:02 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/15 14:22:49 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int result;
    int a;
    int b;
    
    result = 0;
    a = 0;
    b = 0;
    if (ac == 4)
    {
        a = atoi(av[1]);
        b = atoi(av[3]);
        if (av[2][0] == '+')
          result = a + b;   
        else if (av[2][0] == '-')
          result = a - b;   
        else if (av[2][0] == '*')
          result = a * b;   
        else if (av[2][0] == '/')
          result = a / b;   
        else if (av[2][0] == '%')
            result = a % b; 
        printf("%d", result);
    }
    printf("\n");
    
    return (0);
}
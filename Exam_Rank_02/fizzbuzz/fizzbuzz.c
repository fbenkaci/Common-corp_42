/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:12:29 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/01/14 08:46:40 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void    ft_putnbr(int nb)
{
    char nbb;

    if (nb < 10)
    {
        nbb = nb + 48;
        write(1, &nbb, 1);
    }
    else
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
}

void	fizzbuzz(void)
{
	int	n;
    
	n = 1;
	while (n <= 100)
	{
		if (n % 3 == 0 && n % 5 == 0)
			write(1, "fizzbuzz\n", 9);
		else if (n % 3 == 0)
			write(1, "fizz\n", 5);
		else if (n % 5 == 0)
			write(1, "buzz\n", 5);
        else
        {
            ft_putnbr(n);
            write(1, "\n", 1);
        }
        n++;       
	}
}

int	main(void)
{
    fizzbuzz();
}
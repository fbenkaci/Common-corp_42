/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:24:18 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 15:14:51 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    Zombie *Zombie;
    
    randomChump("Foo");
    Zombie = newZombie("Bar");
    Zombie->announce();
    delete Zombie;
    
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:44:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 16:18:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void Zombie::setname(std::string name)
{
    this->_name = name;
}

Zombie	*zombieHorde(int N, std::string name)
{
    Zombie* hordeOfZombie = new Zombie[N];
    Zombie* firstZombie = hordeOfZombie;
    
    for (int i = 0; i < N; i++)
    {
        hordeOfZombie[i].setname(name);
        hordeOfZombie[i].announce();
    }
    
    return (firstZombie);
}


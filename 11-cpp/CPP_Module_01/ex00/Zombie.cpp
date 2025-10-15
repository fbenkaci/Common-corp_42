/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:48:16 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 17:45:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(): _name("Unnamed")
{
}

Zombie::Zombie(std::string name)
{
    this->_name = name;
}

void Zombie::announce(void)
{
    std::cout << this->_name << ": BraiiiiiiinnnzzzZ..."<< std::endl;
}

Zombie::~Zombie()
{
    std::cout << this->_name << " was killed" << std::endl;
}

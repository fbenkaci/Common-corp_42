/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:48:27 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 17:30:04 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() : _name("unnamed") 
{
    
}

Zombie::Zombie(std::string name)
{
    this->_name = name;
}

void Zombie::announce()
{
    std::cout << this->_name << std::endl;
}


Zombie::~Zombie()
{
    std::cout << this->_name << "Destroy" << std::endl; 
}
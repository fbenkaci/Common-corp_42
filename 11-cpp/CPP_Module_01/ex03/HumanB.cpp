/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:44:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/09 14:47:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB()
{
    this->_weapon = NULL;
}

HumanB::HumanB(std::string name)
{
    this->_name = name;
}

void HumanB::attack()
{
    std::cout<< this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon* weapon)
{
    this->_weapon = weapon;
}

HumanB::~HumanB()
{
}
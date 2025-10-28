/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:12:37 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/09 13:04:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon()
{

    
}

Weapon::Weapon(std::string Weapon)
{
    this->_type = Weapon;
}

const std::string& Weapon::getType() const
{
    const std::string& refType = (this->_type);
    
    return (refType);
}

void Weapon::setType(std::string typeOfWeapon)
{
    this->_type = typeOfWeapon;
}

Weapon::~Weapon()
{}
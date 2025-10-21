/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:13:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/21 16:02:24 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int nb)
{
    std::cout << "Int constructor called" << std::endl;
    this->_value = nb << 8;
    // std::cout << this->_value << std::endl; 
}

Fixed::Fixed(const float nb)
{
    std::cout << "Float constructor called" << std::endl;
    this->_value = roundf(nb * (1 << this->_nbBits));
    // std::cout << this->_value << std::endl; 
}

float Fixed::toFloat(void) const
{
    float floatValue;

    floatValue = roundf(this->_value / (1 << this->_nbBits));
    
    return (floatValue);
}

int Fixed::toInt(void) const
{
    int intValue;
    
    intValue = this->_value >> 8;
    // std::cout << intValue << std::endl;
    return (intValue);
}


Fixed& Fixed::operator=(Fixed const & other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->_value = other.getRawBits();
    return (*this);
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->_value);
}

Fixed::Fixed(const Fixed &src)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}
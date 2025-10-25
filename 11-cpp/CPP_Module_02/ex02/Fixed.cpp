/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:35:19 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/25 18:16:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <math.h>

Fixed::Fixed()
{
    this->_value = 0; 
}

Fixed::Fixed(const int nb)
{
    this->_value = nb << this->_nbBits;
}

Fixed::Fixed(const float nb)
{
    this->_value = roundf(nb * (1 << this->_nbBits));
}

float Fixed::toFloat(void) const
{
    return ((float)this->_value / (1 << this->_nbBits)); // Je cast en float pour avoir les nombres apres la virgule
}

int Fixed::toInt(void) const
{
    return (this->_value >> this->_nbBits);
}

Fixed::Fixed(const Fixed &src)
{
    *this = src;
}

Fixed& Fixed::operator=(Fixed const & other)
{
    if (this != &other)
        this->_value = other._value;
    return (*this);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}

Fixed Fixed::operator+(Fixed const& other) const 
{
    Fixed result;

    result._value = this->_value + other._value;
     
    return (result);
}

Fixed Fixed::operator-(Fixed const& other) const 
{
    Fixed result;

    result._value = this->_value - other._value;
     
    return (result);
}

Fixed Fixed::operator*(Fixed const& other) const 
{
    Fixed result;

    result._value = (this->_value * other._value) >> this->_nbBits;
     
    return (result);
}

Fixed Fixed::operator/(Fixed const& other) const 
{
    Fixed result;

    result._value = (this->_value << this->_nbBits) / other._value;
     
    return (result);
}

bool Fixed::operator>(Fixed const & other) const
{
    return (this->_value > other._value);
}

bool Fixed::operator<(Fixed const & other) const
{
    return (this->_value < other._value);
}

bool Fixed::operator>=(Fixed const & other) const
{
    return (this->_value >= other._value);
}

bool Fixed::operator<=(Fixed const & other) const
{
    return (this->_value <= other._value);
}

bool Fixed::operator==(Fixed const & other) const
{
    return (this->_value == other._value);
}

bool Fixed::operator!=(Fixed const & other) const
{
    return (this->_value != other._value);
}

Fixed& Fixed::operator++()
{
    this->_value += 1;
    
    return (*this);
}

Fixed Fixed::operator++(int)
{
    Fixed cpyCurrentObj(*this);
    
    this->_value += 1;
    
    return (cpyCurrentObj);
}

Fixed& Fixed::operator--()
{
    this->_value -= 1;
    
    return (*this);
}

Fixed Fixed::operator--(int)
{
    Fixed cpyCurrentObj(*this);
    
    this->_value -= 1;
    
    return (cpyCurrentObj);
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    if (a < b)
        return (a);
    return (b);
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    if (a < b)
        return (a);
    return (b);
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    if (a > b)
        return (a);
    return (b);
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    if (a > b)
        return (a);
    return (b);
}


Fixed::~Fixed()
{
}
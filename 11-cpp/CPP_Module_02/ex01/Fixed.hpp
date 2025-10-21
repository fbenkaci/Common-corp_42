/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:12:56 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/21 15:49:52 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <math.h>

class Fixed
{
    public:
    Fixed();
    Fixed(const Fixed &src); // His goal is to duplicates another object

    Fixed(const int nb);
    Fixed(const float nb);
    float toFloat(void) const;
    int toInt(void) const;

    ~Fixed();
    int getRawBits(void) const;
    void setRawBits(int const raw);
    Fixed & operator=(Fixed const & other); // Copies content into an already existing object
    
    private:
    
    int _value;
    int static const _nbBits = 8; 
    
};

#endif
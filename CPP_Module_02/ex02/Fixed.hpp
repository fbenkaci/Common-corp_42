/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:01:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/25 18:00:18 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
    public:
    Fixed();
    Fixed(const Fixed &src); // His goal is to duplicates another object

    Fixed(const int nb);
    Fixed(const float nb);
    float toFloat(void) const;
    int toInt(void) const;

    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);

    ~Fixed();

    Fixed & operator=(Fixed const & other); // Copies content into an already existing object
    
    // Opérateur de comparaison
    bool operator>(Fixed const & other) const;
    bool operator<(Fixed const & other) const;
    bool operator>=(Fixed const & other) const;
    bool operator<=(Fixed const & other) const; 
    bool operator==(Fixed const & other) const; 
    bool operator!=(Fixed const & other) const; 
    
    // Opérateur arithmetiques 
    Fixed operator+(Fixed const& other) const; 
    Fixed operator-(Fixed const& other) const; 
    Fixed operator*(Fixed const& other) const; 
    Fixed operator/(Fixed const & other) const ; 
    
    // Opérateur d'incrementation 
    Fixed operator++(int); // Post-incrementation 
    Fixed& operator++(); // Pre-incrementation 
    Fixed &operator--(); 
    Fixed operator--(int); 
    
    private:
    
    int _value;
    int static const _nbBits = 8; 
    
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
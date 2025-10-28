/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:03:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/15 12:03:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <string>
#include <string.h>

class Harl
{
    public :
    
    Harl();
    ~Harl();
    void complain(std::string level);

    private :
    
    void debug(void);
    void info(void);
    void warning(void);
    void error(void);
};

#endif
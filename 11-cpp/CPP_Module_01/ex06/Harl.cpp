/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:03:03 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/15 12:07:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}

void Harl::debug(void)
{
	std::cout << "I love having extra chicken for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "I cannot believe adding extra chicken costs more money. You didn’t put enough chicken in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}
void	Harl::warning(void)
{
    std::cout << "I think I deserve to have some extra chicken for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}
void	Harl::error(void)
{
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
    void (Harl::*functions[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    for (size_t i = 0; i < 4; i++)
    {
       if (!strcmp(levels[i].c_str(), level.c_str()))
            (this->*functions[i])();
    }
}

Harl::~Harl()
{
}
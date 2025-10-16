/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:03:03 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/16 15:31:50 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}


void switchFunction(size_t i)
{
    switch (i)
    {
        case 0:
            std::cout <<  "[DEBUG]" << std::endl << "I love having extra chicken for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
        case 1:
            std::cout << "[ INFO ]"<< std::endl << "I cannot believe adding extra chicken costs more money. You didn’t put enough chicken in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
        case 2:
            std::cout << "[ WARNING ]" << std::endl << "I think I deserve to have some extra chicken for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
        case 3:
            std::cout << "[ ERROR ]" << std:: endl << "This is unacceptable! I want to speak to the manager now." << std::endl;
        default:
            break;
    }
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
    // void (Harl::*functions[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    for (size_t i = 0; i < 4; i++)
    {
       if (!strcmp(levels[i].c_str(), level.c_str()))
            switchFunction(i);
        // Send i to the function that contain switch.
        // Add all messages in the switch
        // When the indice is enter don't break. just break at the last
    }
}



Harl::~Harl()
{
}
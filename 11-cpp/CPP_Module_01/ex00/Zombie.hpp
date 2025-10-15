/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:28:34 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 15:11:42 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>

class Zombie
{
    public:
    
    Zombie();
    Zombie(std::string name);
    ~Zombie();
    void announce( void );
    
    private:
    std::string _name;
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif
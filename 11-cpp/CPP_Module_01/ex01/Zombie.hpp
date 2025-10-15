/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:37:13 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 16:15:56 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie
{
    public:
    Zombie();
    Zombie(std::string name);
    ~Zombie();
    void setname(std::string name);
    void announce();
    
    private:
    std::string _name;

};

Zombie	*zombieHorde(int N, std::string name);


#endif
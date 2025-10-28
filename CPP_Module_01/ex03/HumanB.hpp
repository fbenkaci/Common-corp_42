/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:05:55 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/09 14:46:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_B_HPP
# define HUMAN_B_HPP

# include <string>
# include <iostream>
# include "Weapon.hpp"

class HumanB
{
  public:
	HumanB();
	HumanB(std::string name);
	~HumanB();

	void attack();
    void setWeapon(Weapon* weapon);

  private:
	std::string _name;
	Weapon *_weapon;
};

#endif
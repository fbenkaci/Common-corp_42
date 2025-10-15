/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:50:38 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/09 14:28:58 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A_HPP
# define HUMAN_A_HPP

# include <string>
# include <iostream>
# include "Weapon.hpp"

class HumanA
{
  public:
	HumanA(std::string name, Weapon& Weapon);
	~HumanA();

	void attack();

  private:
	std::string _name;
	Weapon& _weapon;
};

#endif
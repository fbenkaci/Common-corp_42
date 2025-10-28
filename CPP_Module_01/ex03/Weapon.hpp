/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:42:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/09 13:03:48 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon
{
  public:
	
    Weapon();
	Weapon(std::string Weapon);
	~Weapon();

	std::string const &getType() const;
	void setType(std::string typeOfWeapon);

  private:
	std::string _type;
};

#endif
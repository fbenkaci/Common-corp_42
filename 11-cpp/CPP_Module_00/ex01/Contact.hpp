/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:03:54 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/08 14:39:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT
# define CONTACT

# include "Contact.hpp"
#include <iostream>

class Contact
{
  public:
	
	Contact(void);
	~Contact(void); 
	void getcontact(int i) const; // Affiche le contact
	void displayOneContact() const;
	int setcontact(void); // Modifier le contact

  private:
	std::string _first_name;
	std::string _last_name;
	std::string _nickname;
	std::string _phone_number;
	std::string _darkest_secret;
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:08:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/11 15:34:10 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

#include <iostream>
#include <string>
#include "Contact.hpp"
 
class PhoneBook
{
  public:

  PhoneBook(void);
  ~PhoneBook(void);
  void addContact(PhoneBook& phonebook, Contact contact); // This method add a new contact in the tab
  int displayContact() const; // This method print all contact or just the header if there is no contact
  int getContactCount() const; // This method is used to get the number of contacts
  
  private:
  
  Contact _contact[8];
  int _nbContact;
};

#endif
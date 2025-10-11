/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:17:31 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/11 13:07:57 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <string>

PhoneBook::PhoneBook(void)
{
	// std::cout << "Constructor called" << std::endl;
	_nbContact = 0;
	return ;
}

PhoneBook::~PhoneBook(void)
{
	// std::cout << "Destructor called" << std::endl;
	return ;
}

int PhoneBook::getContactCount() const
{
	return (_nbContact);
}

void PhoneBook::addContact(PhoneBook &phonebook, Contact contact)
{
	if (_nbContact < 8)
	{
		phonebook._contact[_nbContact] = contact;
		_nbContact++;
	}
	else
	{
		phonebook._contact[_nbContact % 8] = contact;
		_nbContact++;
	}
}

void Contact::displayOneContact() const
{
	std::cout << "First name     -> " << _first_name << std::endl;
	std::cout << "last name      -> " << _last_name << std::endl;
	std::cout << "Nickname       -> " << _nickname << std::endl;
	std::cout << "Phone number   -> " << _phone_number << std::endl;
	std::cout << "Darkest secret -> " << _darkest_secret << std::endl;
}

int PhoneBook::displayContact() const
{
	int count;
	char tab[8];
	int idx;
	std::string falseIndex;
	int i;

	std::cout << std::setw(10) << "Index"
				<< "|" << std::setw(10) << "first name"
				<< "|" << std::setw(10) << "last name"
				<< "|" << std::setw(10) << "nickname"
				<< "|" << std::endl;
	if (_nbContact == 0)
	{
		std::cout << "You have no contact in your phonebook" << std::endl;
		return (true);
	}
	count = (_nbContact < 8) ? _nbContact : 8;
	for (i = 0; i < count; i++)
		_contact[i].getcontact(i);
	std::cout << "Please Enter the index of the contact you want : ";
	std::cin >> tab[0];

	if (tab[0] == '\0' || !isdigit(tab[0]))
		return (false);
	else
		idx = tab[0] - '0';

	if (idx < 0 || idx >= count)
	{
		for (int j = 0; j < 1; j++)
		{
			if (idx < 0 || idx >= count)
			{
				std::cout << "Please enter index present in your phonebook" << std::endl;
				std::cin >> tab[0];
				if (tab[0] == '\0' || !isdigit(tab[0]))
					return (false);
				else
					idx = tab[0] - '0';
			}
			if (j == 1)
				return (false);
		}
	}
	_contact[idx].displayOneContact();
	std::cin.ignore();
	return (true);
}
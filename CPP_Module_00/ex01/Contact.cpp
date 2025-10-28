/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:19:47 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/11 15:52:06 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <string>

Contact::Contact(void)
{
}

bool	isAllDigits(const std::string &_phone_number)
{
	for (size_t i = 0; i < _phone_number.length(); i++)
		if (!std::isdigit(static_cast<unsigned char>(_phone_number[i])))
			return (false);
	return (true);
}

void Contact::getcontact(int i) const
{
	std::cout << std::setw(10) << i << "|";
	if (_first_name.length() > 10)
		std::cout << std::setw(10) << _first_name.substr(0, 9) + "."
					<< "|";
	else
		std::cout << std::setw(10) << _first_name << "|";
	if (_last_name.length() > 10)
		std::cout << std::setw(10) << _last_name.substr(0, 9) + "."
					<< "|";
	else
		std::cout << std::setw(10) << _last_name << "|";
	if (_nickname.length() > 10)
		std::cout << std::setw(10) << _nickname.substr(0, 9) + "."
					<< "|" << std::endl;
	else
		std::cout << std::setw(10) << _nickname << "|" << std::endl;
}

bool find_space(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] && str[i + 1] && str[i] == ' ' && str[i + 1] == ' ')
			return (false);
		if (str[i] == '\t')
			return (false);
		if (!isalnum(str[i]) && str[i] != ' ')
			return (false);
	}

	return (true);
}

int Contact::setcontact(void)
{
	std::cout << "Enter your first name" << std::endl;
	getline(std::cin, _first_name);
	if (!find_space(_first_name))
		return (false);
	std::cout << "Enter your last name" << std::endl;
	getline(std::cin, _last_name);
	if (!find_space(_last_name))
		return (false);
	std::cout << "Enter your last nickname" << std::endl;
	getline(std::cin, _nickname);
	if (!find_space(_nickname))
		return (false);
	std::cout << "Enter your phone number (Only digits)" << std::endl;
	getline(std::cin, _phone_number);
	for (size_t i = 0; i < 2; i++)
	{
		if (isAllDigits(_phone_number))
			break ;
		std::string message = (i == 1) ? "Its your last chance. Please enter ONLY digit for phone number." : "Please enter only digit for phone number.";
		std::cout << message << std::endl;
		getline(std::cin, _phone_number);
		if (isAllDigits(_phone_number))
			break ;
		if (i == 1)
			return (std::cout << "Invalid phone number." << std::endl, 0);
	}
	std::cout << "Enter your darkest secret" << std::endl;
	getline(std::cin, _darkest_secret);
	if (!find_space(_darkest_secret))
		return (false);
	return (1);
}

Contact::~Contact(void)
{
}

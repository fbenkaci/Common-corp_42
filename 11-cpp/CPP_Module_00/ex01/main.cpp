/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:18:43 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/05 14:42:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <string>
#include <iomanip>

void	isvalid_command(std::string command, PhoneBook& phonebook)
{
    Contact contact;
    
    while (1)
    {
        std::cout << "> ";
        getline(std::cin, command);
        if (std::cin.eof())
        {
            std::cout << std::endl;
            break;
        }
        if (command.compare("ADD") == 0)
        {
            if (!contact.setcontact())
            {
                std::cout << "Adding contact failed." << std::endl;
                break;
            }
            phonebook.addContact(phonebook, contact);
            std::cout << "Contact was SUCCESSFULLY added" << std::endl;
        }
        else if (command.compare("SEARCH") == 0)
        {
            if (!phonebook.displayContact())
                return;
        }
        else if (command.compare("EXIT") == 0)
        {
            std::cout << "Command EXIT was enter." << std::endl;
            return;
        }
        else
            if (command != "\0")
                std::cout << "'"<< command <<"'" << " is not a valid command. Please enter : ADD, SEARCH or EXIT" << std::endl;
    }
    return;
}

int	main(void)
{
	PhoneBook	phonebook;

	std::string command;
    std::cout << "                                  ////////////// WELCOME IN YOUR PhoneBook!!! //////////////" << std::endl << std::endl;
    std::cout << "============ PHONEBOOK INTERFACE ===========" << std::endl;
    std::cout << "1-ADD: add contact" << std::endl;
    std::cout << "2-SEARCH: displays the requested contact" << std::endl;
    std::cout << "3-EXIT: program quits and contacts are lost " << std::endl;
    std::cout << "============================================" << std::endl;
	isvalid_command(command, phonebook);
	return (0);
}

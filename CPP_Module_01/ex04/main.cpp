/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 11:36:58 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/14 12:41:28 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream> 
#include <string> 
#include <sstream>
#include <algorithm> 

int main(int ac, char **av)
{
    if (ac == 4)
    {
        std::ifstream inFileStream(av[1]);
        std::string cpyfilename = av[1];
        std::string line;
        size_t len_strSearch;
        std::string newStr;
        
        std::string searchWord = av[2];
        std::string replaceWord = av[3];
        
        cpyfilename += ".replace";
        len_strSearch = searchWord.length();
        
        std::ofstream outfile(cpyfilename.c_str()); //c_str() converts std::string cpyfilename into const char*, In C++98, std::ofstream cannot take a std::string directly. It only accepts const char*
        while (std::getline(inFileStream, line))
        {
            size_t currentIndex = 0; 

            size_t pos = line.find(searchWord, currentIndex);
            while (pos != std::string::npos)
            {
                newStr += line.substr(currentIndex, pos - currentIndex);
                newStr += replaceWord;
                currentIndex = pos + len_strSearch;
                pos = line.find(searchWord, currentIndex);

            }
            newStr += line.substr(currentIndex);
            
            outfile << newStr << std::endl;
        }
        
        inFileStream.close();
        outfile.close();
    }
    return (0);
}

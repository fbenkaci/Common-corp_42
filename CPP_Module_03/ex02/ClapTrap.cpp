#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : _name("Unnamed"),  _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name),  _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap Parameter constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    *this = src;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->_hitPoints <= 0 || this->_energyPoints <= 0)
        std::cout << this->_name << " cannot attack, hit points <= 0 or energy points <= 0" << std::endl;
    else
    {
        std::cout << "ClapTrap " << this->_name << " attacks " << target << " , causing " << this->_attackDamage << " points of damage!" << std::endl;
        this->_energyPoints--;
    }
}

void ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << this->_name << " take damage, lose " << amount << " points of hitPoints" << std::endl;
    if (amount >= (unsigned int)this->_hitPoints)
        this->_hitPoints = 0;
    else
        this->_hitPoints -= amount;

}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hitPoints <= 0 || this->_energyPoints <= 0)
        std::cout << this->_name << " cannot be repaired, hit points <= 0 or energy points <= 0" << std::endl;
    else
    {
        std::cout << this->_name << " be repaired, regain " << amount << " points of hitPoints" << std::endl;
        this->_hitPoints += amount;
        this->_energyPoints--;
    }
}

ClapTrap& ClapTrap::operator=(ClapTrap const & other)
{
    std::cout << "ClapTrap Assignment operator called" << std::endl;
    
    if (this != &other)
    {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap Destructor called" << std::endl;
}
#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap() : ClapTrap() 
{
    std::cout << "ScavTrap constructor called" << std::endl;
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) 
{
    std::cout << "ScavTrap parameter constructor called" << std::endl;
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
{
    std::cout << "ScavTrap Copy constructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (this->_hitPoints <= 0 || this->_energyPoints <= 0)
        std::cout << this->_name << " cannot attack, hit points <= 0 or energy points <= 0" << std::endl;
    else
    {
        std::cout << "ScavTrap " << this->_name << " attacks " << target << " , causing " << this->_attackDamage << " points of damage!" << std::endl;
        this->_energyPoints--;
    }
}

ScavTrap& ScavTrap::operator=(ScavTrap const & other)
{
    std::cout << "ScavTrap assignment operator called" << std::endl;
    
    if (this != &other)
    {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return (*this);
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap is now in Gate keeper mode" << std::endl; 
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor called" << std::endl;
}
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

class ScavTrap : public ClapTrap  
{
    public:
    ScavTrap();
    ScavTrap(std::string name);
    ScavTrap(const ScavTrap &src);
    ScavTrap & operator=(ScavTrap const& other);
    ~ScavTrap();
    
    void attack(const std::string& target);
    void guardGate();
};

#endif 
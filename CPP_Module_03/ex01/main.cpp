#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Construction ===" << std::endl;
    ScavTrap scav("Scavvy");
    
    std::cout << "\n=== ScavTrap Attack ===" << std::endl;
    scav.attack("Enemy");
    
    std::cout << "\n=== Guard Gate ===" << std::endl;
    scav.guardGate();
    
    std::cout << "\n=== Damage & Repair ===" << std::endl;
    scav.takeDamage(50);
    scav.beRepaired(20);
    
    std::cout << "\n=== Copy ===" << std::endl;
    ScavTrap copy(scav);
    copy.guardGate();
    
    std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
    return 0;
}
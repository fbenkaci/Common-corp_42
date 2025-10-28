#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Construction ===" << std::endl;
    FragTrap frag("Fraggy");
    
    std::cout << "\n=== FragTrap Attack ===" << std::endl;
    frag.attack("Enemy");
    
    std::cout << "\n=== High Five ===" << std::endl;
    frag.highFivesGuys();
    
    std::cout << "\n=== Damage & Repair ===" << std::endl;
    frag.takeDamage(40);
    frag.beRepaired(20);
    
    std::cout << "\n=== Copy ===" << std::endl;
    FragTrap copy(frag);
    copy.highFivesGuys();
    
    std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
    return 0;
}
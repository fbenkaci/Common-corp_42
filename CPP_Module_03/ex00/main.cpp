#include "ClapTrap.hpp"
#include <iostream>

int main(void)
{
    std::cout << "=== Test 1: Basic Constructor and Attack ===" << std::endl;
    ClapTrap clap1("Clappy");
    clap1.attack("target1");
    clap1.attack("target2");
    clap1.attack("target2");
    
    std::cout << "\n=== Test 2: Taking Damage ===" << std::endl;
    ClapTrap clap2("Faycal");
    clap2.takeDamage(3);
    clap2.takeDamage(5);
    clap2.takeDamage(10); // Should set HP to 0
    clap2.attack("enemy"); // Should fail (no HP)
    
    std::cout << "\n=== Test 3: Repairing ===" << std::endl;
    ClapTrap clap3("Healer");
    clap3.takeDamage(5);
    clap3.beRepaired(3);
    clap3.beRepaired(2);
    clap3.attack("target");
    
    std::cout << "\n=== Test 4: Energy Exhaustion ===" << std::endl;
    ClapTrap clap4("Tired");
    for (int i = 0; i < 11; i++)
        clap4.attack("dummy");
    clap4.beRepaired(5); // Should fail (no energy)
    
    std::cout << "\n=== Test 5: Copy Constructor ===" << std::endl;
    ClapTrap clap5("Original");
    ClapTrap clap6(clap5);
    clap6.attack("copy_target");
    
    std::cout << "\n=== Test 6: Assignment Operator ===" << std::endl;
    ClapTrap clap7("First");
    ClapTrap clap8("Second");
    clap8 = clap7;
    clap8.attack("assigned_target");
    
    std::cout << "\n=== Test 7: Dead ClapTrap Attempts ===" << std::endl;
    ClapTrap clap9("Dead");
    clap9.takeDamage(15);
    clap9.attack("ghost");
    clap9.beRepaired(10);
    
    std::cout << "\n=== Test 8: Default Constructor ===" << std::endl;
    ClapTrap clap10;
    clap10.attack("default_target");
    
    std::cout << "\n=== Destructors will be called now ===" << std::endl;
    return (0);
}
#include "test-done.hpp"

#include <iostream>

void show_test_done(const std::string &name)
{
    std::cout << "│   ├── " << name << ": ✓" << std::endl;
}

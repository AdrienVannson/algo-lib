#include "test-done.hpp"
#include <iostream>

void showTestDone(const std::string &name)
{
    std::cout << "### " << name << ": OK" << std::endl;
}

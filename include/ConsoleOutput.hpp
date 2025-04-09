#pragma once
#include "Output.hpp"
#include <iostream>


class ConsoleOutput : public IOutput 
{
public:
    void write(const std::string& data) override {
        std::cout << data << std::endl;
    }
};
#pragma once
#include <string>


class IOutput
{
public:
    virtual ~IOutput() = default;
    virtual void write(const std::string& data) = 0;
};
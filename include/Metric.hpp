#pragma once
#include <string>


class IMetric
{
public:
    virtual ~IMetric() = default;
    virtual std::string collect() = 0;
};
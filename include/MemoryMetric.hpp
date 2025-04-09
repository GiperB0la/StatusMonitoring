#pragma once
#include "Metric.hpp"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <fstream>
#endif


class MemoryMetric : public IMetric
{
public:
    MemoryMetric(const nlohmann::json& config);

public:
    std::string collect() override;

private:
    std::vector<std::string> specs;
};
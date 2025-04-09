#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Metric.hpp"
#include "Output.hpp"
#include "CPUMetric.hpp"
#include "MemoryMetric.hpp"
#include "ConsoleOutput.hpp"
#include "LogOutput.hpp"


class Config
{
public:
	bool load(const std::string& configPath);
	std::vector<std::unique_ptr<IMetric>> createMetrics() const;
	std::vector<std::unique_ptr<IOutput>> createOutputs() const;
	int getPeriod() const;
	bool correctConfig() const;

private:
	nlohmann::json json;
	int period = 1;
	bool isCorrectConfig = false;
};
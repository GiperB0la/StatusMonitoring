#pragma once
#include <iostream>
#include <thread>
#include "Metric.hpp"
#include "Output.hpp"
#include "Config.hpp"


class StatusMonitoring
{
public:
	StatusMonitoring(const std::string& path);

public:
	void start();

private:
	Config config;
	std::vector<std::unique_ptr<IMetric>> metrics;
	std::vector<std::unique_ptr<IOutput>> outputs;
	int period;
};
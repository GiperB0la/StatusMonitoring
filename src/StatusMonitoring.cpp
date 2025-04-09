#include "../include/StatusMonitoring.hpp"


StatusMonitoring::StatusMonitoring(const std::string& path)
{
    config.load(path);
    metrics = config.createMetrics();
    outputs = config.createOutputs();
    period = config.getPeriod();
}

void StatusMonitoring::start()
{
    while (true) {
        std::vector<std::string> results;
        for (auto& metric : metrics) {
            results.push_back(metric->collect());
        }

        for (auto& output : outputs) {
            for (const auto& line : results) {
                output->write(line);
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(period));
    }
}
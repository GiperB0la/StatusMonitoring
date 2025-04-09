#include "../include/Config.hpp"


bool Config::load(const std::string& configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open()) {
        isCorrectConfig = false;
        std::cerr << "[-] The configuration file contains errors." << std::endl;
        return isCorrectConfig;
    }
    file >> json;
    period = std::stoi(json["settings"]["period"].get<std::string>());
    isCorrectConfig = true;
    return isCorrectConfig;
}

std::vector<std::unique_ptr<IMetric>> Config::createMetrics() const 
{
    std::vector<std::unique_ptr<IMetric>> metrics;
    if (isCorrectConfig) {
        for (const auto& m : json["metrics"]) {
            std::string type = m["type"];
            if (type == "cpu") {
                metrics.push_back(std::make_unique<CPUMetric>(m));
            }
            else if (type == "memory") {
                metrics.push_back(std::make_unique<MemoryMetric>(m));
            }
        }
    }
    return metrics;
}

std::vector<std::unique_ptr<IOutput>> Config::createOutputs() const
{
    std::vector<std::unique_ptr<IOutput>> outputs;
    if (isCorrectConfig) {
        for (const auto& o : json["outputs"]) {
            std::string type = o["type"];
            if (type == "console") {
                outputs.push_back(std::make_unique<ConsoleOutput>());
            }
            else if (type == "log") {
                std::string path = o["path"];
                outputs.push_back(std::make_unique<LogOutput>(path));
            }
        }
    }
    return outputs;
}

int Config::getPeriod() const
{
    return period;
}

bool Config::correctConfig() const
{
    return isCorrectConfig;
}
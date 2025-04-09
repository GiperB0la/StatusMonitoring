#pragma once
#include "Metric.hpp"
#include <vector>
#include <nlohmann/json.hpp>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <fstream>
#endif


class CPUMetric : public IMetric
{
public:
    CPUMetric(const nlohmann::json& config);

public:
    std::string collect() override;

private:
    std::vector<int> core_ids_;

#ifdef _WIN32
    FILETIME prev_idle_time_{};
    FILETIME prev_kernel_time_{};
    FILETIME prev_user_time_{};
#else
    unsigned long long prev_user_ = 0;
    unsigned long long prev_nice_ = 0;
    unsigned long long prev_system_ = 0;
    unsigned long long prev_idle_ = 0;
    unsigned long long prev_iowait_ = 0;
    unsigned long long prev_irq_ = 0;
    unsigned long long prev_softirq_ = 0;
#endif

    bool initialized_ = false;
};
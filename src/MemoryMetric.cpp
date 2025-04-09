#include "../include/MemoryMetric.hpp"


MemoryMetric::MemoryMetric(const nlohmann::json& config)
{
    if (config.contains("spec")) {
        specs = config["spec"].get<std::vector<std::string>>();
    }
}

std::string MemoryMetric::collect()
{
    std::ostringstream oss;
    oss << "memory:";

#ifdef _WIN32
    MEMORYSTATUSEX mem_status;
    mem_status.dwLength = sizeof(mem_status);
    if (!GlobalMemoryStatusEx(&mem_status)) {
        return "memory: error";
    }

    for (const auto& spec : specs) {
        if (spec == "used") {
            DWORDLONG used = mem_status.ullTotalPhys - mem_status.ullAvailPhys;
            oss << " used=" << used / (1024 * 1024) << "MB";
        }
        else if (spec == "free") {
            oss << " free=" << mem_status.ullAvailPhys / (1024 * 1024) << "MB";
        }
    }

#else
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo) {
        return "memory: error";
    }

    std::string line;
    unsigned long memTotal = 0, memAvailable = 0;

    while (std::getline(meminfo, line)) {
        if (line.find("MemTotal:") == 0) {
            sscanf(line.c_str(), "MemTotal: %lu kB", &memTotal);
        }
        else if (line.find("MemAvailable:") == 0) {
            sscanf(line.c_str(), "MemAvailable: %lu kB", &memAvailable);
        }
        if (memTotal && memAvailable) break;
    }

    for (const auto& spec : specs) {
        if (spec == "used") {
            unsigned long used = memTotal - memAvailable;
            oss << " used=" << used / 1024 << "MB";
        }
        else if (spec == "free") {
            oss << " free=" << memAvailable / 1024 << "MB";
        }
    }

#endif
    return oss.str();
}
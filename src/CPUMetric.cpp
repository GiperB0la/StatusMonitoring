#include "../include/CPUMetric.hpp"


CPUMetric::CPUMetric(const nlohmann::json& config)
{
    if (config.contains("ids")) {
        core_ids_ = config["ids"].get<std::vector<int>>();
    }
}

std::string CPUMetric::collect()
{
#ifdef _WIN32
    FILETIME idle_time, kernel_time, user_time;
    if (!GetSystemTimes(&idle_time, &kernel_time, &user_time)) {
        return "cpu: error";
    }

    ULONGLONG idle = *((ULONGLONG*)&idle_time);
    ULONGLONG kernel = *((ULONGLONG*)&kernel_time);
    ULONGLONG user = *((ULONGLONG*)&user_time);

    if (!initialized_) {
        prev_idle_time_ = idle_time;
        prev_kernel_time_ = kernel_time;
        prev_user_time_ = user_time;
        initialized_ = true;
        return "cpu: initializing...";
    }

    ULONGLONG prev_idle = *((ULONGLONG*)&prev_idle_time_);
    ULONGLONG prev_kernel = *((ULONGLONG*)&prev_kernel_time_);
    ULONGLONG prev_user = *((ULONGLONG*)&prev_user_time_);

    ULONGLONG sys_total = (kernel + user) - (prev_kernel + prev_user);
    ULONGLONG sys_idle = idle - prev_idle;

    int cpu_usage = sys_total ? (int)((sys_total - sys_idle) * 100 / sys_total) : 0;

    prev_idle_time_ = idle_time;
    prev_kernel_time_ = kernel_time;
    prev_user_time_ = user_time;

#else
    std::ifstream stat("/proc/stat");
    if (!stat) {
        return "cpu: error";
    }

    std::string line;
    std::getline(stat, line);
    unsigned long long user = 0, nice = 0, system = 0, idle = 0;
    unsigned long long iowait = 0, irq = 0, softirq = 0;

    sscanf(line.c_str(), "cpu  %llu %llu %llu %llu %llu %llu %llu",
        &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    unsigned long long prev_total = prev_user_ + prev_nice_ + prev_system_ +
        prev_idle_ + prev_iowait_ + prev_irq_ + prev_softirq_;
    unsigned long long total = user + nice + system + idle + iowait + irq + softirq;

    unsigned long long prev_idle = prev_idle_ + prev_iowait_;
    unsigned long long curr_idle = idle + iowait;

    if (!initialized_) {
        prev_user_ = user;
        prev_nice_ = nice;
        prev_system_ = system;
        prev_idle_ = idle;
        prev_iowait_ = iowait;
        prev_irq_ = irq;
        prev_softirq_ = softirq;
        initialized_ = true;
        return "cpu: initializing...";
    }

    unsigned long long delta_total = total - prev_total;
    unsigned long long delta_idle = curr_idle - prev_idle;

    int cpu_usage = delta_total ? (int)((delta_total - delta_idle) * 100 / delta_total) : 0;

    prev_user_ = user;
    prev_nice_ = nice;
    prev_system_ = system;
    prev_idle_ = idle;
    prev_iowait_ = iowait;
    prev_irq_ = irq;
    prev_softirq_ = softirq;
#endif

    std::ostringstream oss;
    oss << "cpu: " << cpu_usage << "%";
    return oss.str();
}
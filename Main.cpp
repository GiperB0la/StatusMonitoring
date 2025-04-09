#include <iostream>
#include <thread>
#include "include/StatusMonitoring.hpp"


int main(int argc, char* argv[])
{
    std::string configPath = "config.json";
    if (argc > 1) {
        configPath = argv[1];
    }
    else {
        std::cout << "[INFO] Using default config path: config.json\n";
    }

    StatusMonitoring statusMonitoring(configPath);
    statusMonitoring.start();

    return 0;
}
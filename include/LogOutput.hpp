#pragma once
#include "Output.hpp"
#include <fstream>
#include <string>


class LogOutput : public IOutput 
{
public:
    explicit LogOutput(const std::string& path) : log_file(path, std::ios::app) {}
    void write(const std::string& data) override {
        if (log_file.is_open()) {
            log_file << data << std::endl;
        }
    }

private:
    std::ofstream log_file;
};
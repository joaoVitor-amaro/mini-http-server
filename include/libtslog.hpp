#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <iostream>

class TsLogger {
private:
    std::ofstream logfile;
    std::mutex mtx;
    static std::unique_ptr<TsLogger> instance;
    static std::mutex inst_mtx;

    TsLogger(const std::string &filename);
public:
    static TsLogger& getInstance(const std::string &filename = "../logs/server.log");

    void log(const std::string &msg);
    ~TsLogger();
};

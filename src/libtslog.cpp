#include "libtslog.hpp"
#include <ctime>

std::unique_ptr<TsLogger> TsLogger::instance = nullptr;
std::mutex TsLogger::inst_mtx;

TsLogger::TsLogger(const std::string &filename) {
    logfile.open(filename, std::ios::app);
    if (!logfile.is_open()) {
        throw std::runtime_error("Erro ao abrir arquivo de log");
    }
}

TsLogger::~TsLogger() {
    if (logfile.is_open()) logfile.close();
}

TsLogger& TsLogger::getInstance(const std::string &filename) {
    std::lock_guard<std::mutex> lock(inst_mtx);
    if (!instance) {
        instance.reset(new TsLogger(filename));
    }
    return *instance;
}

void TsLogger::log(const std::string &msg) {
    std::lock_guard<std::mutex> lock(mtx);

    // Timestamp
    std::time_t t = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    logfile << "[" << buf << "] " << msg << std::endl;
    logfile.flush();

    // Também printa no console
    std::cout << "[" << buf << "] " << msg << std::endl;
}

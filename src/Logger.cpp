/**
 * Logging service for the application
 */

#include "Logger.h"
#include <iostream>
#include <chrono>

using namespace std;

/**
 * Constructor for the logger
 * @param loc - location from which logger is called
 */
Logger::Logger(string loc) {
    location = loc;
}

/**
 * Displays logs in the following format:
 * (18:06:38) -- [GameWindow]: Game Started
 * (18:06:39) -- [GameWindow]: Game Ended. Exiting.
 * @param msg - The message to be logged
 */
void Logger::log(string msg) {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%T", std::localtime(&now));
    cout << "(" << s.substr(0,8) << ") -- " << "[" << location << "]: " << msg << endl;
}

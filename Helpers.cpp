//
// Created by shadow on 2/28/21.
//

#include "Helpers.h"
#include <chrono>
#include <utility>
#include <random>

using namespace std;
using namespace std::chrono;

string create_uuid() {
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 }; // delimiters

    string res;
    for (bool i : dash) {
        if (i) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

long int create_alarm_time(unsigned short int h, unsigned short int m, unsigned short int s) {
    auto now = system_clock::now();
    time_t time_now = system_clock::to_time_t(now);
    tm* date = localtime(&as_const(time_now));
    date->tm_hour = h;
    date->tm_min = m;
    date->tm_sec = s;

    return duration_cast<milliseconds>(system_clock::from_time_t(mktime(date)).time_since_epoch()).count();
}

string timestamp_to_h_readable(const time_t raw) {
    struct tm* dt;
    char buffer [50];
    dt = localtime(&raw);
    strftime(buffer, sizeof(buffer), "%c", dt);
    return string(buffer);
}
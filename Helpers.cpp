//
// Created by shadow on 2/28/21.
//

#include "Helpers.h"
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

string create_uuid() {
    uuid_t uuid;
    char unparsed[100];
    uuid_generate_random(uuid);
    uuid_unparse(uuid, unparsed); // need to unparse because uuid is generated with weird encoding
    return string(unparsed);
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
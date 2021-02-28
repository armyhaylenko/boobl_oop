//
// Created by shadow on 2/28/21.
//

#ifndef MYKHLAB6_HELPERS_H
#define MYKHLAB6_HELPERS_H

#include <uuid/uuid.h>
#include <string>
#include <chrono>

std::string create_uuid();
long int create_alarm_time(unsigned short int h, unsigned short int m, unsigned short int s);
std::string timestamp_to_h_readable(time_t raw);

#endif //MYKHLAB6_HELPERS_H

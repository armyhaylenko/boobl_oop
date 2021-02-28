//
// Created by shadow on 2/28/21.
//

#ifndef MYKHLAB6_WATCH_H
#define MYKHLAB6_WATCH_H

#include "Timer.h"
#include <iostream>

/*
 * should ideally be called Alarm...
 * works only for today!!!!
 */

class Watch
{
private:
    bool _stopped = false;
    unsigned long int _start_time;
    long int _alarm_time;
    std::string _readable_alarm_time;
    std::string _label;
    std::function<void()> _final_message = [this](){std::cout << "The watch " << _label << ": alarm!!!\n";};
public:
    Watch(long int millis);
    Watch(long int millis, std::string label);
    Watch(unsigned short int hours, unsigned short int minutes, unsigned short int seconds);
    Watch(unsigned short int hours, unsigned short int minutes, unsigned short int seconds, std::string label);
    Watch(Watch&) = default; // not going to be copying watches
    ~Watch() = default;

    inline const std::string& get_label() const {return _label;};
    unsigned int get_remaining_time() const;
    unsigned int get_alarm_time() const;
    const std::string& get_readable_alarm_time() const;

    void set_final_message(std::function<void()>) noexcept;

    void start();

};

std::ostream& operator<<(std::ostream& o, const Watch& t);

#endif //MYKHLAB6_WATCH_H

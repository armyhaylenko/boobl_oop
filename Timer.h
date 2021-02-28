//
// Created by shadow on 2/28/21.
//

#ifndef MYKHLAB6_TIMER_H
#define MYKHLAB6_TIMER_H

#include <ctime>
#include <string>
#include <functional>

class Timer
{
private:
    bool _stopped = false;
    unsigned long int _start_time;
    unsigned int _millis_set;
    std::string _label;
    std::function<void()> _final_message;
public:
    explicit Timer(unsigned int millis); // user specifies in how many millis should the timer go off
    Timer(unsigned int millis, std::string label);
    Timer(Timer&) = default; // not going to be copying timers, potential thread exhaustion
    ~Timer() = default;

    unsigned int get_remaining_time() const;
    inline const std::string& get_label() const {return _label;};
    void set_final_message(std::function<void()>) noexcept;

    void start();

};

std::ostream& operator<<(std::ostream& o, const Timer& t);

#endif //MYKHLAB6_TIMER_H

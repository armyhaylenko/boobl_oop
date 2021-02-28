//
// Created by shadow on 2/28/21.
//

#include "Timer.h"
#include "Helpers.h"
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

Timer::Timer(unsigned int millis): _millis_set(millis), _start_time(0) {
    _label = create_uuid();
    _final_message = [this](){cout << "The timer " << _label << " has went off.\n";};
#ifndef NDEBUG
    cout << "Created " << *this << '\n';
#endif
}

Timer::Timer(unsigned int millis, std::string label): _millis_set(millis), _label(move(label)), _start_time(0) {
    _final_message = [this](){cout << _label << " has went off.\n";};
#ifndef NDEBUG
    cout << "Created " << *this << '\n';
#endif
}

unsigned int Timer::get_remaining_time() const {
    const auto now = system_clock::now();
    return _start_time + _millis_set - duration_cast<milliseconds>(now.time_since_epoch()).count();
}

void Timer::set_final_message(std::function<void()> fm) noexcept {
    _final_message = move(fm);
}

void Timer::start() {
    this->_stopped = false;
    thread t([=, this]() {
        if(_stopped) return; // guard against concurrent modification
        const auto now = system_clock::now();
        _start_time = duration_cast<milliseconds>(now.time_since_epoch()).count();
        this_thread::sleep_for(milliseconds(_millis_set));
        _stopped = true;
        _final_message();
    });
    t.detach();
}

ostream& operator<<(ostream& o, const Timer& t) {
    return o << "{Timer " << t.get_label() << '}';
}
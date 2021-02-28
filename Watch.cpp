//
// Created by shadow on 2/28/21.
//

#include "Watch.h"
#include "Helpers.h"
#include <iostream>
#include <thread>
#include <utility>
#include <uuid/uuid.h>

using namespace std;
using namespace std::chrono;

Watch::Watch(long int millis): _alarm_time(millis), _start_time(0) {
    _label = create_uuid();
    _readable_alarm_time = timestamp_to_h_readable(_alarm_time);
#ifndef NDEBUG
    cout << "Created " << *this << '\n';
#endif
}

Watch::Watch(long int millis, string label): _alarm_time(millis), _start_time(0), _label(move(label)) {
    _readable_alarm_time = timestamp_to_h_readable(static_cast<time_t>(millis));
#ifndef NDEBUG
    cout << "Created " << *this << '\n';
#endif
}

Watch::Watch(unsigned short hours, unsigned short minutes, unsigned short seconds): _start_time(0) {
    _alarm_time = create_alarm_time(hours, minutes, seconds);
    _label = create_uuid();
    _readable_alarm_time = timestamp_to_h_readable(static_cast<time_t>(_alarm_time));
#ifndef NDEBUG
    cout << "Created " << *this << '\n';
#endif
}

Watch::Watch(unsigned short hours, unsigned short minutes, unsigned short seconds, std::string label):
        _label(move(label)), _start_time(0) {
    _alarm_time = create_alarm_time(hours, minutes, seconds);
    _readable_alarm_time = timestamp_to_h_readable(static_cast<time_t>(_alarm_time));
}

unsigned int Watch::get_remaining_time() const {
    auto now = system_clock::now();
    auto now_seconds = duration_cast<seconds>(now.time_since_epoch()).count();
    return _alarm_time - now_seconds;
}

unsigned int Watch::get_alarm_time() const {
    return _alarm_time;
}

const std::string& Watch::get_readable_alarm_time() const {
    return _readable_alarm_time;
}

void Watch::set_final_message(std::function<void()> fm) noexcept {
    _final_message = move(fm);
}

void Watch::start() {
    _stopped = false;
    thread t([=, this](){
        if(_stopped) return;
        auto now = system_clock::now();
        _start_time = duration_cast<seconds>(now.time_since_epoch()).count();
        this_thread::sleep_until(system_clock::from_time_t(static_cast<time_t>(_alarm_time)));
        _stopped = true;
        _final_message();
    });
    t.detach();
}


ostream& operator<<(ostream& o, const Watch& w) {
    return o << "{Watch " << w.get_label() << '}';
}

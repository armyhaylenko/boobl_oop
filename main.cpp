#include <iostream>
#include <thread>
#include <chrono>
#include "Timer.h"
#include "Watch.h"

using namespace std;
using namespace std::chrono;

int main() {
    Timer t1(3000, "t1"); // 3 seconds
    t1.start();
    this_thread::sleep_for(milliseconds(2000));
    cout << t1.get_remaining_time() << " millis left until t1 fires." << '\n'; // should print around 1000

    Timer t2(5000);
    t2.start();
    this_thread::sleep_for(milliseconds(1000));
    cout << t2.get_remaining_time() << " millis left until t2 fires." << '\n'; // should print around 4000

    auto now = system_clock::now();

    Watch w1(duration_cast<seconds>(now.time_since_epoch()).count() + 10); // trigger in 10 seconds
    w1.start();
    cout << "w1 will fire on " << w1.get_readable_alarm_time() << '\n';
    this_thread::sleep_for(milliseconds(5000));
    cout << w1.get_remaining_time() << " seconds left until w1 fires." << '\n'; // 10 - 5 = 5 seconds until firing

    Watch w2(duration_cast<seconds>(now.time_since_epoch()).count() + 15);
    w2.start();
    w2.set_final_message([](){cout << "A new final message from w2!!\n";});
    this_thread::sleep_for(milliseconds(7000));

    this_thread::sleep_for(milliseconds(10000));
    cout << "passed all tests\n";
    return 0;
}

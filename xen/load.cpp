#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>

int INTERVAL = 20 * 1000;

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv)
{
    //generate load for 1 minute
    uint64_t start = timeSinceEpochMillisec();
    while(true)
    {
        uint64_t end = timeSinceEpochMillisec();
        if(end - start > INTERVAL)
        {
            break;
        }
    }

    return 0;
}
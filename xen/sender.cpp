#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include "CRC.h"

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void start_sender()
{
    std::cout << "GOOD";
    int toSend[] = {1,1,1,1,1,1,1};
    int length = 7;
    int currentBitIndex = 0;
    int INTERVAL = 50;

    while(true)
    {
        uint64_t start = timeSinceEpochMillisec();
        int bit = toSend[currentBitIndex];
        
        if(currentBitIndex == length)
        {
            break;
        }
        
        if(bit == 1)
        {
            while(true)
            {
                uint64_t end = timeSinceEpochMillisec();
                if(end - start > INTERVAL)
                {
                    std::cout << "Sending " << bit << std::endl;
                    break;
                }
            }
        }
        else
        {
            usleep(INTERVAL * 1000);
        }

        currentBitIndex += 1;
    }
}

int main() {
  
  for(int i = 0;;i++)
  {
        uint64_t milliseconds = timeSinceEpochMillisec();
        if (milliseconds % 10000 == 0)
        {
            std::cout << "Good" << std::endl;
            break;
        }
  }

  start_sender();

  return 0;
}
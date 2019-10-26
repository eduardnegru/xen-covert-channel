#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void start_receiver()
{
    std::cout << "GOOD";
    int toSend[] = {1,1,1,1,1,1,1};
    int length = 7;
    int currentBitIndex = 0;
    int INTERVAL = 50;

    while(true)
    {
        int i = 0;    
        uint64_t start = timeSinceEpochMillisec();

        while(true)
        {
            uint64_t end = timeSinceEpochMillisec();
            i += 1;
            if(end - start > INTERVAL)
            {
                std::cout << "Received " << i << std::endl;
                break;
            }    
        }
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

  start_receiver();

  return 0;
}
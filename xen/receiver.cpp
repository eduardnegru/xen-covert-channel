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
    int THRESHOLD = 20000;

    while(true)
    {
        int iterations = 0;    
        uint64_t start = timeSinceEpochMillisec();

        while(true)
        {
            uint64_t end = timeSinceEpochMillisec();
            if(end - start > INTERVAL)
            {
                if(iterations < THRESHOLD)
                {
                    std::cout << "Received 1 " << iterations << std::endl;
                }
                else
                {
                    std::cout << "Received 0 " << iterations << std::endl;
                }

                break;
            }
            iterations += 1;
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
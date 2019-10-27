#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;

int INTERVAL = 50;
int THRESHOLD = 20000;

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void start_receiver()
{
    bool waitForStartBit = true;

    while(true)
    {
        int iterations = 0;    
        uint64_t start = timeSinceEpochMillisec();
        int dataBitCount = 0;
        int data[9];

        while(true)
        {
            uint64_t end = timeSinceEpochMillisec();
            if(end - start > INTERVAL)
            {
                if(iterations < THRESHOLD)
                {
                    // std::cout << "Received 1 ";

                    if(waitForStartBit == false && dataBitCount < 9)
                    {
                        data[dataBitCount++] = 1;
                        std::cout << dataBitCount << std::endl;
                    }

                    if(dataBitCount == 9)
                    {
                        std::cout << "==========PACKET END==========" << std::endl;
                        //stop bit
                        waitForStartBit = true;
                        dataBitCount = 0;

                        for(int i = 0; i < 9; i++)
                        {
                            std::cout << data[i] << " ";
                            data[i] = 0;
                        }
                        std::cout << std::endl;
                    }
                }
                else
                {
                    std::cout << "Received 0 ";
                    if(waitForStartBit)
                    {
                        std::cout << "==========PACKET START==========" << std::endl;
                        //start bit
                        waitForStartBit = false;
                    }
                    else
                    {
                        if(dataBitCount < 9)
                        {
                            data[dataBitCount++] = 0;
                            std::cout << dataBitCount << std::endl;
                        }
                    }                
                }

                // std::cout << iterations << std::endl;
                break;
            }
            iterations += 1;
        }
    }
}

int main() {
  
 uint64_t milliseconds = timeSinceEpochMillisec();
   time_t now = time(0);   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   int sec = gmtm->tm_sec;
   int min = 1;

   uint64_t target_milliseconds = milliseconds + (60 - (milliseconds / 1000) % 60) * 1000;
   target_milliseconds = target_milliseconds - (target_milliseconds % 1000);

   if ((milliseconds / 1000) %  60 > 45)
   {
       target_milliseconds += 60 * 1000;
   }
   cout << "Target timestamp is " << target_milliseconds << endl; 

    for(int i = 0;;i++)
    {        
        uint64_t time = timeSinceEpochMillisec();

        if (time > target_milliseconds)
        {
            cout << "Sync done" << endl;
            break;
        }
    }

  start_receiver();

  return 0;
}
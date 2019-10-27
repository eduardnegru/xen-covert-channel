#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;

int INTERVAL = 100;
int THRESHOLD = 20000;

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void start_receiver()
{
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
                    std::cout << "Received 1 ";
                }
                else
                {
                    std::cout << "Received 0 ";
                }
                std::cout << iterations << std::endl;
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

   uint64_t target_milliseconds = milliseconds + (60 - (milliseconds / 1000) % 60) * 1000  + min * 60 * 1000;
   target_milliseconds = target_milliseconds - (target_milliseconds % 1000);


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
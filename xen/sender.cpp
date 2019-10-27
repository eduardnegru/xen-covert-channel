#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;

int INTERVAL = 50;


uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void send_high()
{
    uint64_t start = timeSinceEpochMillisec();

    while(true)
    {
        uint64_t end = timeSinceEpochMillisec();
        if(end - start > INTERVAL)
        {
            std::cout << "Sending 1" << std::endl;
            break;
        }
    }
}

void send_low()
{
    std::cout << "Sending 0" << std::endl;
    usleep(INTERVAL * 1000);
}

int compute_parity(int data[8])
{
    int sum = 0;

    for(int i = 0; i < 8; i++)
    {
        sum = sum ^ data[i];
    }

    return sum;
}

void send_packet(int data[8])
{
    //start bit
    send_low();

    //data bits
    int currentBitIndex = 0;

    while(true)
    {
        int bit = data[currentBitIndex];
        
        if(currentBitIndex == 8)
        {
            break;
        }
        
        if(bit == 1)
        {
            send_high();
        }
        else
        {
            send_low();
        }

        currentBitIndex += 1;
    }

    //parity
    int parity = compute_parity(data);

    if(parity == 0)
    {
        send_low();
    }
    else
    {
        send_high();
    }

    //stop
    send_high();
}

void start_sender()
{
    send_high();
    send_high();
    send_high();

    std::cout << "Sync finished. Sender started." << std::endl;

    int data[8] = {1,1,1,1,1,1,1,1};
    send_packet(data);

    int data2[8] = {1,0,1,0,0,1,1,1};
    send_packet(data2);

}

int main()
{  
    uint64_t milliseconds = timeSinceEpochMillisec();
    time_t now = time(0);   
    // convert now to string form
    char* dt = ctime(&now);

    cout << "The local date and time is: " << dt << endl;

    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    int sec = gmtm->tm_sec;

    uint64_t target_milliseconds = milliseconds + (60 - (milliseconds / 1000) % 60) * 1000;
    target_milliseconds = target_milliseconds - (target_milliseconds % 1000);

    if ((milliseconds / 1000) %  60 > 45)
    {
        target_milliseconds += 60 * 1000;
    }

    int hours = (target_milliseconds / (1000 * 60 * 60)) % 24 + 2;
    int mins = (target_milliseconds / (1000 * 60)) % 60;
    int seconds = (target_milliseconds / 1000) % 60;

    std::cout << "Scheduled at " << hours << ":" << mins << ":" << seconds << endl;

    for(int i = 0;;i++)
    {        
        uint64_t time = timeSinceEpochMillisec();

        if (time > target_milliseconds)
        {
            cout << "Sync done" << endl;
            break;
        }
    }

    start_sender();

    return 0;
}
#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

int INTERVAL = 50;
int THRESHOLD = 20000;
std::vector<int*> packets = std::vector<int*>();

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
void print_array(int* data)
{
    for(int i = 0; i < 8; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}
bool check_parity(int data[9])
{
    int parity = 0;
    for(int i = 0; i < 8; i++)
    {
        parity = parity ^ data[i];
    }

    return (bool)parity == data[8];
}

void start_receiver()
{
    bool waitForStartBit = true;
    int data[9];
    int dataBitCount = 0;

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
                    if(waitForStartBit == false && dataBitCount < 9)
                    {
                        data[dataBitCount++] = 1;
                    }

                    if(dataBitCount == 9)
                    {
                        int validPacket = check_parity(data);
                        if (validPacket)
                        {
                            std::cout << "Packet valid" << std::endl;
                        }
                        else
                        {
                            std::cout << "Packet invalid" << std::endl;
                        }

                        //stop bit
                        waitForStartBit = true;
                        dataBitCount = 0;
                        int copy[8];
                        
                        for(int i = 0; i < 9; i++)
                        {
                            if (i == 8)
                            {
                                std::cout << "Parity = " << data[i];
                            }
                            else
                            {
                                std::cout << data[i] << " ";
                            }
                            
                            if(i < 8)
                                copy[i] = data[i];
                            
                            data[i] = 0;
                        }

                        std::cout << std::endl;
                        std::cout << "==========PACKET END==========" << std::endl;
                        print_array(copy);
                        packets.push_back(copy);
                        return;
                    }
                }
                else
                {
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
                        }
                    }                
                }

                break;
            }
            iterations += 1;
        }
    }
}

void sync_sender_receiver()
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
}

int main(int argc, char** argv) {
  
    sync_sender_receiver();
    start_receiver();
    for (std::vector<int*>::iterator it = packets.begin() ; it != packets.end(); ++it)
        print_array(*it);
    return 0;
}
#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <fstream>

using namespace std;

int INTERVAL = 50, packetCount = 0;
int** packets;

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

    for(int i = 0; i < packetCount; i++)
    {
        send_packet(packets[i]);
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

int read_packets_from_file(int*** packets, char* filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::string delimiter = " ";
    int pos;

    std::getline(infile, line);
    int packetCount = std::stoi(line);

    *packets = (int**) new int*[packetCount];
    for (int i = 0; i < packetCount; ++i)
        (*packets)[i] = new int[8];

    int i = 0;

    while (std::getline(infile, line))
    {
        size_t pos = 0;
        
        std::string token;
        int j = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            (*packets)[i][j++] = std::stoi(token);
            line.erase(0, pos + delimiter.length());
        }

        (*packets)[i][j++] = std::stoi(token);
        i++;
    }

    return packetCount;
}

void print_packets()
{
    for(int i = 0; i < packetCount; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            cout << packets[i][j] << " ";
        }
        cout << endl;
    }
}
void free_memory(int** packets)
{
    for (int i = 0; i < packetCount; ++i)
        delete [] packets[i];
    delete [] packets;
}

int main(int argc, char** argv)
{  
    if(argc < 2)
    {
        cout << "Please add the input file name with input data as argument" << endl;
        return 0;
    }

    packetCount = read_packets_from_file(&packets, argv[1]);
    print_packets();
    sync_sender_receiver();

    start_sender();

    free_memory(packets);
    return 0;
}
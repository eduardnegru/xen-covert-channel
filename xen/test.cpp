#include <chrono>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

int INTERVAL = 100;

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv)
{  
    char* filename;
    int interval;

    if(argc < 3)
    {
        std::cout << "Arguments required: outputFileName and mesurement interval in milliseconds" << std::endl;
        return 0;
    }

    filename = argv[1];
    interval = atoi(argv[2]);      
    
    uint64_t start = timeSinceEpochMillisec();
    int i = 0;
    while(true)
    {
        uint64_t end = timeSinceEpochMillisec();
        if(end - start > 100)
        {
            break;
        }
        i++;
    }

    std::ofstream myfile;
    myfile.open (filename);
    myfile << i; 
    myfile.close();
    
    return 0;
}
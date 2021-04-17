#include "utils.h"

std::ostream& operator << (std::ostream& stream, const vector<string>& v)
{
    for (auto &command : v)
        stream << command << std::endl;

    return stream;
}

int main(int argc, char *argv[] )
{
    
    int N = 0;
    if (argc > 1)
       N = stoi(argv[1]);
    
    vector<string> packet;
    vector<string> packetDynamic;
    if (N == 0) {
        help();
    }
    else {
        for (std::string line; std::getline(std::cin, line);)
            if (IsRunPacketFile(line, packet, N, packetDynamic)) {
                RunPacket(line, packet, packetDynamic);
            }
    }
     
    return 0;
}


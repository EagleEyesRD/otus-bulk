#include "utils.h"

std::ostream& operator << (std::ostream& stream, const std::vector<std::string>& v)
{
    for (auto &command : v)
        stream << command << std::endl;

    return stream;
}

int main(int argc, char *argv[] )
{
    int N = 0;
    if (argc > 1)
       N = std::stoi(argv[1]);
    auto pm = new PackManager();
    if (N == 0) {
        help();
    }
    else {
        for (std::string line; std::getline(std::cin, line);)
            if (pm->IsRunPacketFile(line, N))
                pm->RunPacket(line);
    }
    return 0;
}


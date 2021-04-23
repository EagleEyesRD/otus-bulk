#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void help()
{
    std::cout << "It's programm for run packet commands" << std::endl;
    std::cout << "Run programm that format:" << std::endl;
    std::cout << "exe <N size of packet commands wich it waits>" << std::endl;
    std::cout << "You can put more commands between { .... and ...} symbols - it's dynamic list" << std::endl;
    std::cout << "The end of programm is EOF in any moment. After that it show in console commands's list of static in push order and dynamic list ignore." << std::endl;
}



bool IsEndOfDymamicPacket(vector<string>& vpack) {
    int cntOpenBrackets = 0;
    int cntCloseBrackets = 0;
    for (auto& xcomm : vpack) {
        if (xcomm == "{")
            cntOpenBrackets++;
        if (xcomm == "}")
            cntCloseBrackets++;
    }
    return (cntOpenBrackets == cntCloseBrackets && cntOpenBrackets > 0 && cntCloseBrackets > 0);
}

bool IsStartOfDynamicPacket(string command, vector<string>& pack) {
    int cntOpenBrackets = 0;
    int cntCommands = 0;
    pack.push_back(command);
    for (auto& xcomm : pack) {
        if (xcomm == "{") {
            cntOpenBrackets++;
        }
        else if (xcomm != "}")
            cntCommands++;
    }
    return cntOpenBrackets > 0 && cntCommands == 0;
}

bool AreThereSubPackets(vector<string>& vpack) {
    int cntOpenBrackets = 0;
    int cntCommands = 0;
    for (auto& xcomm : vpack) {
        if (xcomm == "{")
            cntOpenBrackets++;
        else if (xcomm != "}")
            cntCommands++;
    }
    return cntOpenBrackets > 0 && cntCommands > 1;
}

bool IsEndOfStaticPacket(string command, vector<string>& statpack, size_t limit, vector<string>& dynampack) {
    if (command == "EOF")
        return true;

    if (command == "{") {
        dynampack.push_back(command);
        if (statpack.size() > 0)
            return true;
        else
            return false;
    }
    else {
        statpack.push_back(command);
    }
    return statpack.size() == limit;
}

bool IsRunPacketFile(string command, vector<string>& statpack, size_t limit, vector<string>& dynampack) {

    if (dynampack.size() == 0) {
        if (IsEndOfStaticPacket(command, statpack, limit, dynampack))
            return true;

        return false;
    }
    else {
        if (command == "EOF")
            return true;

        if (!IsStartOfDynamicPacket(command, dynampack))
            if (IsEndOfDymamicPacket(dynampack))
                return true;

        return false;
    }
}

void RunPacket(string command, vector<string>& statpack, vector<string>& dynampack) {
    if (statpack.size() > 0) {
        for (string& xcommand : statpack)
            if (xcommand != "{")
                if (xcommand != "}")
                    if (xcommand != "EOF")
                        cout << xcommand << ", ";
        statpack.clear();
    }
    else {
        if (dynampack.size() > 0) {
            if (command != "EOF")
            {
                if (IsEndOfDymamicPacket(dynampack)) {
                    for (string& xcommand : dynampack)
                        if (xcommand != "{")
                            if (xcommand != "}")
                                cout << xcommand << ", ";
                }
            }
            dynampack.clear();
        }
    }
    cout << endl;
}

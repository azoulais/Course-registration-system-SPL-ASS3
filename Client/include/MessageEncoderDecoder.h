//
// Created by guy on 30/12/2020.
//

#ifndef ASSIGNMENT4_MESSAGEENCODERDECODER_H
#define ASSIGNMENT4_MESSAGEENCODERDECODER_H

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
//using namespace std;

class MessageEncoderDecoder {
public:
    MessageEncoderDecoder();
    //void stringToCharArray(std::string& str, char &buf, int bufSize);
    void createMessage(std::vector<std::string> &messageToEncode,std::vector<char> &buf);
    std::vector<short> decodeOpcodes(std::vector<char>&);
private:
    std::unordered_map<std::string,short>opCode;
    void twoPartsMessage(std::vector<std::string> &messageToEncode,std::vector<char> &buf);
    void onePartMessage(int index,std::vector<std::string> &messageToEncode,std::vector<char> &buf);
    void shortToBytes(short num, std::vector<char>&buf);
    short bytesToShort(std::vector<char>&, int index);
    bool from_string(short &t, const std::string &s, std::ios_base &(*f)(std::ios_base &)=std::dec);
    void pushStringAsShort(std::vector<std::string>& messageToEncode,std::vector<char> &buf);
};


#endif //ASSIGNMENT4_MESSAGEENCODERDECODER_H

//
// Created by guy on 30/12/2020.
//

#include "MessageEncoderDecoder.h"

MessageEncoderDecoder::MessageEncoderDecoder() : opCode({{"ADMINREG",     1},
                                                         {"STUDENTREG",   2},
                                                         {"LOGIN",        3},
                                                         {"LOGOUT",       4},
                                                         {"COURSEREG",    5},
                                                         {"KDAMCHECK",    6},
                                                         {"COURSESTAT",   7},
                                                         {"STUDENTSTAT",  8},
                                                         {"ISREGISTERED", 9},
                                                         {"UNREGISTER",   10},
                                                         {"MYCOURSES",    11},
                                                         {"ACK",          12},
                                                         {"ERR",          13}}) {

}


void MessageEncoderDecoder::twoPartsMessage(std::vector<std::string> &messageToEncode, std::vector<char> &buf) {
    //add to buf the first string+\0+ second string+\0
    for (int i = 1; i <= 2; i++) {
        onePartMessage(i, messageToEncode, buf);
        buf.push_back('\0');
    }
}

void
MessageEncoderDecoder::onePartMessage(int index, std::vector<std::string> &messageToEncode, std::vector<char> &buf) {
    //add to buf the vector[index] string
    int messageToEncodeSize = messageToEncode[index].size();
    for (int i = 0; i < messageToEncodeSize; ++i) {
        buf.push_back(messageToEncode[index][i]);
    }
}

void MessageEncoderDecoder::shortToBytes(short num, std::vector<char> &buf) {
    buf.push_back(((num >> 8) & 0xFF));
    buf.push_back((num & 0xFF));
}

short MessageEncoderDecoder::bytesToShort(std::vector<char> &messageToDecode, int index) {
    short result = (short) ((messageToDecode[index] & 0xff) << 8);
    result += (short) (messageToDecode[index + 1] & 0xff);
    return result;
}

void MessageEncoderDecoder::createMessage(std::vector<std::string> &messageToEncode, std::vector<char> &buf) {
    short command(opCode[messageToEncode[0]]);
    shortToBytes(command, buf);    //add opcode to the beginning of the buf
    switch (command) {
        //login+register
        case 1:
        case 2:
        case 3:
            twoPartsMessage(messageToEncode, buf);
            break;
            //opcode+ info (course number)
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
            pushStringAsShort(messageToEncode, buf);
            break;
            //opcode+info+ /0 at the end
        case 8:
            onePartMessage(1, messageToEncode, buf);
            buf.push_back('\0');
            break;
            //opcode
        default:
            break;
    }
}

std::vector<short> MessageEncoderDecoder::decodeOpcodes(std::vector<char> &messageToDecode) {
    short command(bytesToShort(messageToDecode, 0));
    short messageOpcode(bytesToShort(messageToDecode, 2));
    std::vector<short> commandAndMessageOpcode{command, messageOpcode};
    return commandAndMessageOpcode;
}

void MessageEncoderDecoder::pushStringAsShort(std::vector<std::string> &messageToEncode, std::vector<char> &buf) {
    //convert the course number from string to short and then push the short as bytes to the buffer
    short courseNum;
    if (!from_string(courseNum, messageToEncode[1]))
        std::cout << "failed to convert course number to short" << std::endl;
    shortToBytes(courseNum, buf);
}

bool MessageEncoderDecoder::from_string(short &t, const std::string &s, std::ios_base &(*f)(std::ios_base &)) {
    //converting string to short
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}



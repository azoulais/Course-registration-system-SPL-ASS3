#include "connectionHandler.h"
#include "MessageEncoderDecoder.h"
#include "Protocol.h"
#include <unordered_map>
#include <boost/thread/thread.hpp>


/**
 * This function will be run by the second thread.
 * This thread read an input from the keyboard, encode it and send the message to the server,
 * until the LOGOUT command is approved.
 *
 * @param connectionHandler ,messageEncoderDecoder ,protocol- references
 */
void readFromKeyboard(ConnectionHandler &connectionHandler, MessageEncoderDecoder &messageEncoderDecoder,
                      Protocol &protocol) {
    while (!protocol.getShouldTerminate()) {
        //read input from keyboard
        //and split it to strings by ' ' char
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string input(buf);

        std::vector<std::string> messageToEncode;
        boost::split(messageToEncode, input, boost::is_any_of(" "), boost::token_compress_on);

        //encode the message, and fill the bufferToSend array
        std::vector<char> buffer;
        messageEncoderDecoder.createMessage(messageToEncode, buffer);
        int bufferToSendSize = buffer.size();
        char bufferToSend[bufferToSendSize];
        for (int i = 0; i < bufferToSendSize; i++) {
            bufferToSend[i] = buffer[i];
        }

        //sending the message
        if (!connectionHandler.sendBytes(bufferToSend, bufferToSendSize)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        //in case of LOGOUT command, the thread waits until the answer from the server
        //so he will not wait on keyboard again (and will be stuck)
        if (messageToEncode[0] == "LOGOUT") {
            if (!protocol.getLogoutFuture().get())
                protocol.setNewPromise(); //logout fail we need new promise
        }
    }
}

/**
 * Main function of the client, the MAIN-thread will run this.
 * The thread:
 *      connect to the server,
 *      creates the message encoder-decoder, message protocol and the keyboard thread.
 *      read messages from the server, decoding them and prints them.
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    //connect to server
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    } else {
        std::cout << "connected" << std::endl;
    }

    //CREATE the meesage encoder-decoder, message protocol
    MessageEncoderDecoder messageEncoderDecoder;
    Protocol protocol;
    //CREATE the thread that read input keyboard and send the messages to server
    boost::thread keyboardThread(&readFromKeyboard, boost::ref(connectionHandler), boost::ref(messageEncoderDecoder),
                                 boost::ref(protocol));

    while (!protocol.getShouldTerminate()) {
        //we first read from the server the OPCODE of the ACK/ERROR
        //and the OPCODE of the message that was sent by the client
        char ch;
        std::vector<char> answerOpcodes;
        for (int i = 0; i < 4; i++) {
            if (!connectionHandler.getBytes(&ch, 1)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            answerOpcodes.push_back(ch);
        }
        std::vector<short> opcodesToProcess(messageEncoderDecoder.decodeOpcodes(answerOpcodes));
        bool extraInfo = protocol.process(opcodesToProcess);

        //for messages with optional info
        if (extraInfo) {//optional data
            std::string optionalData;
            if (!connectionHandler.getFrameAscii(optionalData, '\0')) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            std::cout << optionalData << std::endl;
        }
    }
    keyboardThread.join();
    return 0;
}

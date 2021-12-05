package bgu.spl.net.impl.BGRSServer;

import bgu.spl.net.srv.Server;

import java.io.IOException;

public class ReactorMain {
    public static void main(String[] args) {
        int port = Integer.parseInt(args[0]);
        int numOfThreads = Integer.parseInt(args[1]);
        if (!Database.getInstance().initialize("Courses.txt"))
            System.out.println("reading from courses file failed");
        else
            Server.reactor(numOfThreads, port, () -> new BGRSMessagingProtocol(), () -> new BGRSMessageEncoderDecoder()).serve();
    }
}

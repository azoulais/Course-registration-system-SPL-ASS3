package bgu.spl.net.impl.BGRSServer.callbacks;

import bgu.spl.net.impl.BGRSServer.BGRSMessagingProtocol;

import java.nio.charset.StandardCharsets;

public class IsRegisteredFunction implements BGRSCallback{
    private final static short OPCODE = 9;
    @Override
    public String run(BGRSMessagingProtocol protocol, byte[] msg) {
        if(!protocol.isUserConnected())
            return null;

        short courseNumber = Short.parseShort(new String(msg, StandardCharsets.UTF_8));
        return protocol.getUser().isRegisteredTo(courseNumber);
    }

    public short getOPCODE() {return this.OPCODE;}

}

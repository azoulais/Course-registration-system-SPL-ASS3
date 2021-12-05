package bgu.spl.net.impl.BGRSServer.callbacks;

import bgu.spl.net.impl.BGRSServer.BGRSMessagingProtocol;

public class CheckMyCoursesFunction implements BGRSCallback{
    private final static short OPCODE = 11;
    @Override
    public String run(BGRSMessagingProtocol protocol, byte[] msg) {
        if(!protocol.isUserConnected())
            return null;

        String str = protocol.getUser().getCoursesString();
        return protocol.getUser().getCoursesString();
    }

    public short getOPCODE() {return this.OPCODE;}

}

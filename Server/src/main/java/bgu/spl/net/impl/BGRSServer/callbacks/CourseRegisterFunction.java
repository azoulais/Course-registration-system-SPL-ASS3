package bgu.spl.net.impl.BGRSServer.callbacks;

import bgu.spl.net.impl.BGRSServer.BGRSMessagingProtocol;
import bgu.spl.net.impl.BGRSServer.DatabaseObjects.User;

import java.nio.charset.StandardCharsets;

public class CourseRegisterFunction implements BGRSCallback{

    private final static short OPCODE = 5;
    @Override
    public String run(BGRSMessagingProtocol protocol, byte[] msg) {
        if(!protocol.isUserConnected())
            return null;

        short courseNumber = Short.parseShort(new String(msg, StandardCharsets.UTF_8));

        User user = protocol.getUser();
        boolean success = user.courseRegister(courseNumber);
        return (success) ? "" : null;
    }

    public short getOPCODE() {return this.OPCODE;}


}

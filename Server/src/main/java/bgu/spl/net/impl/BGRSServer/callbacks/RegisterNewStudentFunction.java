package bgu.spl.net.impl.BGRSServer.callbacks;

import bgu.spl.net.impl.BGRSServer.BGRSMessagingProtocol;
import bgu.spl.net.impl.BGRSServer.Database;
import bgu.spl.net.impl.BGRSServer.DatabaseObjects.Student;

import java.nio.charset.StandardCharsets;

public class RegisterNewStudentFunction implements BGRSCallback {
    private final static short OPCODE = 2;
    @Override
    public String run(BGRSMessagingProtocol protocol, byte[] msg) {
        String message = new String(msg, StandardCharsets.UTF_8);

        if(protocol.isUserConnected())
            return null;
        String username= message.substring(0,message.indexOf('\0'));
        if(Database.getInstance().isUserExist(username))
            return null;
        String password = message.substring(message.indexOf('\0')+1,message.length()-1);
        boolean out = Database.getInstance().addUser(new Student(username,password));

        return  (!out)? "" : null;
    }

    public short getOPCODE() {return this.OPCODE;}

}

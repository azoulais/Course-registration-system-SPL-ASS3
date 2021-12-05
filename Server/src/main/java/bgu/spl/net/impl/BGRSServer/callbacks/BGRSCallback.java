package bgu.spl.net.impl.BGRSServer.callbacks;

import bgu.spl.net.impl.BGRSServer.BGRSMessagingProtocol;

public interface BGRSCallback  {
     String run(BGRSMessagingProtocol protocol, byte[] msg);
     short getOPCODE();
}

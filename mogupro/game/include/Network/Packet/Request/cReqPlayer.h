#pragma once
#include <Network/Packet/cPacketBase.h>
#include <Network/Packet/PacketId.h>
namespace Network
{
namespace Packet
{
namespace Request
{
class cReqPlayer : public cPacketBase<cReqPlayer, PacketId::REQ_PLAYER>
{
public:
    cReqPlayer( );
	cReqPlayer(float x,float y,float z,float xTheta,float yTheta);
    void packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data ) override;
    ubyte2 packetExport( char* const data ) override;
    float xPos;
    float yPos;
    float zPos;
    float xTheta;
    float yTheta;
};
}
}
}
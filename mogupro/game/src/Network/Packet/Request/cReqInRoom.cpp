#include <Network/Packet/Request/cReqInRoom.h>
namespace Network
{
namespace Packet
{
namespace Request
{
cReqInRoom::cReqInRoom( ) : mRoomID(-1), mNetworkHandle("",0)
{
}
cReqInRoom::cReqInRoom( int roomID) : mRoomID(roomID), mNetworkHandle("", 0)
{
}

void cReqInRoom::packetImport(cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data)
{
}
ubyte2 cReqInRoom::packetExport( char* const data )
{
	return offset;
}
}
}
}
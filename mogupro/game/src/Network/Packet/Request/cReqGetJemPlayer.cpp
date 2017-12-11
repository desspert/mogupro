#include <Network/Packet/Request/cReqGetJemPlayer.h>
#include <Network/PackFunction.hpp>
namespace Network
{
namespace Packet
{
namespace Request
{
void cReqGetJemPlayer::packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data )
{
    mNetworkHandle = networkHandle;
    cImporter imp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // imp >> pos1 >> a1 >> pos2 >> a2;
    imp >> mPlayerId >> mGemId;
}
ubyte2 cReqGetJemPlayer::packetExport( char* const data )
{
    cExporter exp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // exp << pos1 << a1 << pos2 << a2;
    exp << mPlayerId << mGemId;
    return exp;
}
}
}
}
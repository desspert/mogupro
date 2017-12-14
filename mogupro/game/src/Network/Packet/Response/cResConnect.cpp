#include <Network/Packet/Response/cResConnect.h>
#include <Network/PackFunction.hpp>
namespace Network
{
namespace Packet
{
namespace Response
{
cResConnect::cResConnect( )
{

}
void cResConnect::packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data )
{
    mNetworkHandle = networkHandle;
    cImporter imp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // imp >> pos1 >> a1 >> pos2 >> a2;
}
ubyte2 cResConnect::packetExport( char* const data )
{
    cExporter exp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // exp << pos1 << a1 << pos2 << a2;
    return exp.getSize( );
}
}
}
}
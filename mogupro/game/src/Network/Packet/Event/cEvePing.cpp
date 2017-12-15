#include <Network/Packet/Event/cEvePing.h>
#include <Network/PackFunction.hpp>
namespace Network
{
namespace Packet
{
namespace Event
{
cEvePing::cEvePing( )
{

}
void cEvePing::packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data )
{
    cImporter imp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // imp >> pos1 >> a1 >> pos2 >> a2;
	imp >> time;
}
ubyte2 cEvePing::packetExport( char* const data )
{
    cExporter exp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // exp << pos1 << a1 << pos2 << a2;
	exp << time;
    return exp.getSize( );
}
}
}
}
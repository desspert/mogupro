#include <Network/Packet/Request/cReqEndStartTimer.h>
#include <Network/PackFunction.hpp>
namespace Network
{
namespace Packet
{
namespace Request
{
cReqEndStartTimer::cReqEndStartTimer( )
{

}
void cReqEndStartTimer::packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data )
{
	mNetworkHandle = networkHandle; 
}
ubyte2 cReqEndStartTimer::packetExport( char* const data )
{
    cExporter exp( data );
    // �g����: vec2 pos1, pos2; ubyte2 a1, a2;
    // exp << pos1 << a1 << pos2 << a2;
    return exp.getSize( );
}
}
}
}
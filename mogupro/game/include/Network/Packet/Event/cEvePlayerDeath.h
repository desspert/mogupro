#pragma once
#include <Network/Packet/cPacketBase.h>
#include <Network/Packet/PacketId.h>
namespace Network
{
namespace Packet
{
namespace Event
{
#pragma pack(1)
class cEvePlayerDeath : public cPacketBase<cEvePlayerDeath, PacketId::EVE_PLAYER_DEATH>
{
public:
    cEvePlayerDeath( );
    cEvePlayerDeath( std::string const& playerName );
    void packetImport( ubyte2 size, char const* const data ) override;
    ubyte2 packetExport( char* const data ) override;
    // 倒した相手の名前。
    std::string mPlayerName;
};
#pragma pack()
}
}
}
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
class cEvePlayerRobJem : public cPacketBase<cEvePlayerRobJem, PacketId::EVE_PLAYER_ROB_JEM>
{
public:
    cEvePlayerRobJem( );
    cEvePlayerRobJem( std::string const& playerName );
    void packetImport( ubyte2 size, char const* const data ) override;
    ubyte2 packetExport( char* const data ) override;
    // �D��������̖��O�B
    // ���̂���ID�Ƃ��ɂȂ肻���B
    std::string mPlayerName;
};
#pragma pack()
}
}
}
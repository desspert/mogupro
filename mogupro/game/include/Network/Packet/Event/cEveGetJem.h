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
class cEveGetJem : public cPacketBase<cEveGetJem, PacketId::EVE_GET_JEM>
{
public:
    cEveGetJem( );
    cEveGetJem( ubyte2 gemId );
    void packetImport( ubyte2 size, char const* const data ) override;
    ubyte2 packetExport( char* const data ) override;
    // �̂�������̖��O�B
    // ���@��@�ɂ����O��t���Ă����̂��A���ƂŘb������Ȃ��ƁI
    std::string mTargetName;
    // �t�B�[���h�ɂ���ǂ̃W�F���Ȃ̂��B
    ubyte2 mGemId;
};
#pragma pack()
}
}
}
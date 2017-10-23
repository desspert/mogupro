#pragma once
#include <Utility/cSingletonAble.h>
#include <Network/cUDP.h>
#include <Network/Packet/cPacketBase.h>
#include <Network/Packet/PacketId.h>
#include <cinder/Vector.h>
#include <cinder/Quaternion.h>
namespace Network
{
namespace Packet
{
namespace Deliver
{
class cDliBreakBlocks;
}
}
class cUDPClientManager : public Utility::cSingletonAble<cUDPClientManager>
{
public:
    cUDPClientManager( );
private:
    template <class Ty, Packet::PacketId packetId>
    void send( cNetworkHandle const& networkHandle, Packet::cPacketBase<Ty, packetId>* packetBase )
    {
        if ( packetBase == nullptr ) return;

        cPacketBuffer packetBuffer;
        packetBase->createPacket( packetBuffer );

        sendDataBufferAdd( networkHandle, packetBuffer );

        delete packetBase;
        packetBase = nullptr;
    }
public:
    void close( );
    void open( );
    bool isConnected( );
    void connect( cNetworkHandle const& handle );
    void update( );
private:
    void updateSend( );
    void updateRecv( );
private:
    void connection( );
    void ping( );
private:
    void sendDataBufferAdd( cNetworkHandle const& networkHandle, cPacketBuffer const& packetBuffer );
private:
    // �S�Ẵv���C���[�̍��W���s���B
    void allPlayersFormat( );
    // �S�Ă̌@��@�̐ݒu�C�x���g���s���B
    void allQuarrys( );
    // �S�ẴW�F���̎�C�x���g���s���B
    void allGems( );
    // �S�Ẵu���b�N�j��C�x���g���s���B
    void allBreakBlocks( );
public:
    // �u���b�N��j�󂵂���Ă�ł��������B
    void sendBreakBlock( cinder::vec3 const& position );
    // �܂Ƃ߂ău���b�N��j�󂵂���Ă�ł��������B
    void sendBreakBlocks( std::vector<cinder::vec3> const& positions );
    // �@��@��ݒu������Ă�ł��������B
    void sendSetQuarry( cinder::vec3 const& position, ubyte1 drillType );
    // �v���C���[�̈ʒu�����T�[�o�[�ɑ���܂��̂ŌĂ�ł��������B
    void sendPlayerFormat( cinder::vec3 const& position, cinder::quat const& rotation );
    // �v���C���[���W�F�����擾������Ă�ł��������B
    void sendGetGemPlayer( ubyte2 gemId );
    // �@��@���W�F�����擾������Ă�ł��������B
    void sendGetGemQuarry( ubyte1 drillId, ubyte2 gemId );
private:
    // ��L�ł��܂����u���b�N�����ۂɑ���܂��B
    void sendBreakBlocks( );
private:
    Packet::Deliver::cDliBreakBlocks* mBreakBlocksPecket = nullptr;
private:
    cUDP mSocket;
    std::map<cNetworkHandle, std::vector<char>> mSendDataBuffer;
    bool mIsConnected = false;
    cNetworkHandle mConnectServerHandle;
    float mCloseSecond;
};
}
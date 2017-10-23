#pragma once
#include <Utility/cSingletonAble.h>
#include <Network/NetworkDefines.h>
#include <cinder/Vector.h>
#include <cinder/Quaternion.h>
#include <vector>
namespace Network
{
namespace Packet
{
namespace Deliver
{
class cDliBreakBlocks;
}
}
}
namespace Game
{
namespace Trans
{
class cClientAdapter : public Utility::cSingletonAble<cClientAdapter>
{
public:
    cClientAdapter( );
    ~cClientAdapter( );
public:
    void update( );
private:
    // �S�Ẵv���C���[�̍��W���s���B
    void recvAllPlayersFormat( );
    // �S�Ă̌@��@�̐ݒu�C�x���g���s���B
    void recvAllQuarrys( );
    // �S�ẴW�F���̎�C�x���g���s���B
    void recvAllGems( );
    // �S�Ẵu���b�N�j��C�x���g���s���B
    void recvAllBreakBlocks( );
public:
    // �u���b�N��j�󂵂���Ă�ł��������B
    void sendBreakBlock( cinder::vec3 const& position );
    // �܂Ƃ߂ău���b�N��j�󂵂���Ă�ł��������B
    void sendBreakBlocks( std::vector<cinder::vec3> const& positions );
    // �@��@��ݒu������Ă�ł��������B
    void sendSetQuarry( cinder::vec3 const& position, Network::ubyte1 drillType );
    // �v���C���[�̈ʒu�����T�[�o�[�ɑ���܂��̂ŌĂ�ł��������B
    void sendPlayerFormat( cinder::vec3 const& position, cinder::quat const& rotation );
    // �v���C���[���W�F�����擾������Ă�ł��������B
    void sendGetGemPlayer( Network::ubyte2 gemId );
    // �@��@���W�F�����擾������Ă�ł��������B
    void sendGetGemQuarry( Network::ubyte1 drillId, Network::ubyte2 gemId );
private:
    // ��L�ł��܂����u���b�N�����ۂɑ���܂��B
    void sendBreakBlocks( );
private:
    Network::Packet::Deliver::cDliBreakBlocks* mBreakBlocksPecket = nullptr;
};
}
}

#pragma once
#include <Utility/cSingletonAble.h>
#include <Network/cUDPManager.h>
#include <cinder/Vector.h>
#include <cinder/Quaternion.h>
#include <Network/Packet/Deliver/cDliBreakBlocks.h>
namespace Network
{
class cUDPClientManager : public Utility::cSingletonAble<cUDPClientManager>
{
public:
    cUDPClientManager( );
public:
    void update( );
private:
    // �S�Ẵv���C���[�̍��W���s���B
    void allPlayersPosition( );
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
    void sendPlayerPosition( cinder::vec3 const& position, cinder::quat const& rotation );
    // �v���C���[���W�F�����擾������Ă�ł��������B
    void sendGetGemPlayer( ubyte2 gemId );
    // �@��@���W�F�����擾������Ă�ł��������B
    void sendGetGemQuarry( ubyte1 drillId, ubyte2 gemId );
private:
    // ��L�ł��܂����u���b�N�����ۂɑ���܂��B
    void sendBreakBlocks( );
private:
    cNetworkHandle mConnectServerHandle;
    Packet::Deliver::cDliBreakBlocks* mBreakBlocksPecket = nullptr;
};
}
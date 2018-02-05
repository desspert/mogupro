#pragma once
#include <Utility/cSingletonAble.h>
#include <Network/NetworkDefines.h>
#include <cinder/Vector.h>
#include <cinder/Quaternion.h>
#include <vector>
#include <Game/Field/cBreakBlockType.h>
namespace Network
{
namespace Packet
{
namespace Request
{
class cReqBreakBlocks;
}
}
}
namespace Game
{
class cClientAdapter : public Utility::cSingletonAble<cClientAdapter>
{
public:
    cClientAdapter( );
    ~cClientAdapter( );
public:
    void update( );
private:
    // �S�Ẵv���C���[�̍X�V���s���B
    void recvAllPlayers( );
    // �S�ẴW�F���̎�C�x���g���s���B
    void recvAllGems( );
    // �S�Ẵu���b�N�j��C�x���g���s���B
    void recvAllBreakBlocks( );
	// �S�ẴT�u�E�F�|���C�x���g���s���B
	void recvAllWeaponCapsules( );
	// �S�Ă̑�C�C�x���g���s���B
	void recvAllCannons( );
	//
	void recvAllGameInfo( );
public:
    // �u���b�N��j�󂵂���Ă�ł��������B
    void sendBreakBlock( cinder::vec3 const& position, float radius, Network::ubyte1 type );
    // �@��@��ݒu������Ă�ł��������B
    void sendSetQuarry( cinder::vec3 const& position );
    // �v���C���[�̈ʒu�����T�[�o�[�ɑ���܂��̂ŌĂ�ł��������B
    void sendPlayer( cinder::vec3 const& position, cinder::quat const& rotation );
    // �v���C���[���W�F�����擾������Ă�ł��������B
    void sendGetGemPlayer( Network::ubyte2 gemId );
    // �@��@���W�F�����擾������Ă�ł��������B
    void sendGetGemQuarry( Network::ubyte2 objectId, Network::ubyte2 gemId );
	// ���C�g�{���𓊂���B
	void sendLightBomb( cinder::vec3 const& position, cinder::vec3 const& speed );
	// �J�v�Z���𓊂���B
	void sendWeaponCapsule( cinder::vec3 const& position, cinder::vec3 const& speed, Network::ubyte1 type );
	// �N�����L��������Ă�ł��������B
	void sendKill( Network::ubyte1 enemyId );
	// �N���Ƀ_���[�W��^������Ă�ł��������B
	void sendDamage( Network::ubyte1 enemyId, float damage );
	//
	void sendRespawn( );
	//
	void sendAddCannonPower( Network::ubyte1 power, Network::ubyte1 playerOrQuarry );
	//
	void sendResult( );
	//
	void sendPlayerAttack( Network::ubyte1 playerId, Network::ubyte1 call );
private:
    // ��L�ł��܂����u���b�N�����ۂɑ���܂��B
    void sendBreakBlocks( );
private:
    Network::Packet::Request::cReqBreakBlocks* mBreakBlocksPecket = nullptr;
	Network::ubyte4 mPlayerSeq = 0U;
};
}

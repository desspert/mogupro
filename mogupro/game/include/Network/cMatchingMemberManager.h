#pragma once
#include <Network.hpp>
#include <Utility/cSingletonAble.h>

//! @file MatchingMemberManager
//! @brief MatchingMember���擾�ł��܂�
//! @note 
//!      ���ケ��𕡐��ɂ���ꍇ�����邩������Ȃ�
//! @date 2017-10-20
//! @author Taka Nomoto

namespace Network
{
class cMatchingMemberManager : public Utility::cSingletonAble<cMatchingMemberManager>
{
public:
	cMatchingMemberManager();
	~cMatchingMemberManager();
	//�����o�[�ǉ�
	bool addRoomMembers(Network::cNetworkHandle addMember);
	//�����o�[�ɂ��邩�ǂ��� (�m��Ȃ��z����̒ʐM�͂�������)
	bool checkInMembers(Network::cNetworkHandle member);
	//Team�Ƀ����o�[�ǉ� �R�[�h���������烊�t�@�N�^�����O�K�v
	bool checkTeamIn(int teamNum,Network::cNetworkHandle addMember);
	bool checkMaster(cNetworkHandle masterHandle);
	cNetworkHandle mMasterHandle;
	std::map<cNetworkHandle, int> mRoomMembers;
};
}

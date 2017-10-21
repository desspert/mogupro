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
	bool addRoomMembers(Network::cNetworkHandle addMember);
	cNetworkHandle mMasterHandle;
	std::vector<cNetworkHandle> mRoomMembers;
	//���ꕪ����K�v������̂�
	std::vector<cNetworkHandle> m1PMembers;
	std::vector<cNetworkHandle> m2PMembers;

};
}

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
	struct PlayerData
	{
		ubyte1 teamNum;
		std::string nameStr;
		ubyte1 playerID;
		cNetworkHandle networkHandle;
		bool canUpdate;
		bool startGame;
		PlayerData()
		{

		}

		PlayerData(ubyte1 _teamNum, std::string _nameStr, ubyte1 _playerID, cNetworkHandle _networkHandle) :
			teamNum(_teamNum), nameStr(_nameStr), playerID(_playerID),networkHandle(_networkHandle), canUpdate(false), startGame(false)
		{

		}
	};

class cMatchingMemberManager : public Utility::cSingletonAble<cMatchingMemberManager>
{
public:
	cMatchingMemberManager();
	~cMatchingMemberManager();
	//�����o�[�ǉ�
	bool addRoomMembers(Network::cNetworkHandle addMember);
	//�����o�[�ǉ� 2017/12/14 yumayo �ϐ�p
	bool addRoomMembersWatching( Network::cNetworkHandle addMember );
	//�����o�[�ɂ��邩�ǂ��� (�m��Ȃ��z����̒ʐM�͂�������)
	bool checkInMembers(Network::cNetworkHandle member);
	//�`�[���ԍ��̕ύX
	bool changeTeamNum(int teamNum, Network::cNetworkHandle member);
	//�}�X�^�[���ǂ����̔��f
	bool checkMaster(cNetworkHandle masterHandle);
	// �ϐ�҂����������ߕ��� yuamyo
	//void addPlayerDatas(std::string playerStr,ubyte1 teamNum, cNetworkHandle networkHandle);
	void addPlayerDatas(std::string playerStr, ubyte1 teamNum, ubyte1 playerID,cNetworkHandle networkHandle);
	cNetworkHandle mMasterHandle;
	std::vector<PlayerData> mPlayerDatas;
	std::map<int, bool> mEmptyIds; // 2017/12/14 �ϐ�҂������Ă���ID�Ǘ����ʓ|�ɂȂ������߁B
    int mPlayerID = 0;
	int mPlayerTeamNum = 0;
private:
	int teamCount[2];
};
}

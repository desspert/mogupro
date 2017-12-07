#pragma once
#include <Utility/cSingletonAble.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>
#include <Node/node.h>
namespace Game
{
class cGameManager : public Utility::cSingletonAble<cGameManager>
{
public:
	cGameManager( );
	~cGameManager( ) = default;
public:
	enum class State
	{
		// ���[�h���I����đS����ҋ@���Ă��鎞
		STAND_BY,
		// �v���C���[�ɃJ�������ړ����A�{���Ƀo�g�����J�n�����܂ł̊�
		READY,
		// �Q�[����
		BATTLE,
		// �Q�[�����I�������U���g�ֈڍs��
		BATTLE_END,
		// ���U���g���\��
		RESULT,
	};
public:
	// �Q�[���J�n�p�P�b�g���͂�����X�e�[�g���Ƃ̐�Έڍs���Ԃ������Ă��������B
	void setup( boost::posix_time::ptime ready, boost::posix_time::ptime battle, boost::posix_time::ptime battleEnd );
	inline bool isStandBy( ) { return state == State::STAND_BY; }
	inline bool isStandByShift( ) { return flash && ( state == State::BATTLE ); }
	inline bool isReady( ) { return state == State::READY; }
	inline bool isReadyShift( ) { return flash && ( state == State::READY ); }
	inline bool isBattle( ) { return state == State::BATTLE; }
	inline bool isBattleShift( ) { return flash && ( state == State::BATTLE ); }
	inline bool isBattleEnd( ) { return state == State::BATTLE_END; }
	inline bool isBattleEndShift( ) { return flash && ( state == State::BATTLE_END ); }
	inline bool isResult( ) { return state == State::RESULT; }
	inline bool isResultShift( ) { return flash && ( state == State::RESULT ); }
	std::string getLeftBattleTime( );
	void shiftResult( );
	void preUpdate( float delta );
	void update( float delta );
	void draw( );
private:
	void shift( State state );
	// ���݂̃X�e�[�g
	State state = State::STAND_BY;
	// ��t���[���O�̃X�e�[�g
	State prevState = state;
	// �X�e�[�g���ڂ����u��
	bool flash = false;

	bool isShiftResult = false;

	// �X�e�[�g���Ƃ̐�Έڍs���ԁB
	// �Q�[�����C���Ɉړ��������_�Ŗ��m�Ɍ��߂Ă����܂��B
	std::map<State, boost::posix_time::ptime> shiftSeconds;

	// 
	std::map<State, std::function<void( float )>> mUpdates;
	// 
	std::map<State, std::function<void( float )>> mPreUpdates;

	hardptr<Node::node> root;
};
}

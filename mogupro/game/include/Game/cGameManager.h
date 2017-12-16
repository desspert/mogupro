#pragma once
#include <Utility/cSingletonAble.h>
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
		//
		INIT,
		// ���������[�h���⑼�̃v���C���[�̃��[�h��҂��Ă�����
		LOAD,
		// �����̃`�[���̊m�F�����Ă�����
		MY_TEAM,
		//�@�G�̃`�[���̊m�F�����Ă�����
		ENEMY_TEAM,
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
	void setTime( float loadTime );
	std::string getLeftBattleTime( );
	void preUpdate( float delta );
	void update( float delta );
	void draw( );
private:
	void skipReady( );
	void addPreUpdate( State state, std::function<void( float )> method );
	void addUpdate( State state, std::function<void( float )> method );
	void next( );
	//���[�v�̊J�n�ƏI���͂܂��������ł��O�A�O������Ă�
	void playBgm( const std::string& name, const float gain, const float loopbegin, const float loopend );
	void stopBgm( const std::string& name );
	// ���݂̃X�e�[�g
	State state = State::INIT;
	// ��t���[���O�̃X�e�[�g
	State prevState = state;
	// �X�e�[�g���ڂ����u��
	bool flash = false;

	bool timeEmpty( );

	// �X�e�[�g���Ƃ̐�Έڍs���ԁB
	// �Q�[�����C���Ɉړ��������_�Ŗ��m�Ɍ��߂Ă����܂��B
	std::map<State, float> shiftSeconds;

	// 
	std::map<State, std::function<void( float )>> mUpdates;
	// 
	std::map<State, std::function<void( float )>> mPreUpdates;

	hardptr<Node::node> root;
};
}

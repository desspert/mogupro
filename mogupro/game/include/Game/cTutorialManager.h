#pragma once
#include <Utility/cSingletonAble.h>
#include <map>
#include <Node/node.h>
#include <dessUI/UIPlate/TutorialUI/TutorialUI.h>
namespace Game
{
class cTutorialManager : public Utility::cSingletonAble<cTutorialManager>
{
public:
	cTutorialManager( );
	~cTutorialManager( ) = default;
public:
	enum class State
	{
		//����
		Description,
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
	void draw2D();
	bool getTutorialStan() { return ui.getTutorialStan(); }
private:
	void skipReady( );
	void addPreUpdate( State state, std::function<void( float )> method );
	void addUpdate( State state, std::function<void( float )> method );
	void next( );
	//���[�v�̊J�n�ƏI���͂܂��������ł��O�A�O������Ă�
	void playBgm( const std::string& name, const float gain, const float loopbegin, const float loopend );
	void stopBgm( const std::string& name );
	
	TutorialUI ui;
	// ���݂̃X�e�[�g
	State state = State::Description;
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

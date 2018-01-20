#pragma once
#include <string>
#include <functional>
#include <set>
#include <Utility/cUserPointer.hpp>
namespace Utility
{
class cStateNode;
class cStateAllow
{
public:
	cStateAllow( Utility::hardptr<cStateNode> nextNode, std::function<bool( Utility::softptr<cStateNode> n )> transitionInfo );
	//! ���̑J�ڐ�
	Utility::hardptr<cStateNode> nextNode;
	//! �Ԃ�l��true�ɂȂ�����X�e�[�g���J�ڂ��܂��B
	std::function<bool( Utility::softptr<cStateNode> n )> transitionInfo;
};
class cStateNode : public std::enable_shared_from_this<cStateNode>
{
public:
	//! �J�ڐ��null�����B
	static const Utility::hardptr<cStateNode> none;
	//! ���݂̃X�e�[�g�̖��O
	std::string name;
	//! �J�ڂ��ꂽ�u�ԂɌĂ΂�܂��B
	std::function<void( Utility::softptr<cStateNode> prev )> onStateIn;
	//! �J�ڂ���u�ԂɌĂ΂�܂��B
	std::function<void( Utility::softptr<cStateNode> next )> onStateOut;
	//! ���݂̃X�e�[�g���I������Ă����疈�t���[���Ă΂�܂��B
	std::function<void( Utility::softptr<cStateNode> self )> onStateStay;
	//! �J�ڐ�̕ێ�
	std::set<Utility::hardptr<cStateAllow>> nextNodes;
	//! �m�[�h���J�ڂ����悤�ȏ�Ԃł���ΑJ�ڐ��Ԃ��܂��Bdefault: none
	Utility::softptr<cStateNode> update( );
	//! ���̃m�[�h�Ɍq����m�[�h�Ɩ����w�肵�܂��B
	void join( Utility::hardptr<cStateAllow> allow );
};
class cStateMachineBehaviour
{
public:
    cStateMachineBehaviour( ) = default;
    ~cStateMachineBehaviour( ) = default;
	void init( Utility::hardptr<cStateNode> entry );
	void update( );
private:
	Utility::hardptr<cStateNode> entry;
	Utility::softptr<cStateNode> current;
};
}

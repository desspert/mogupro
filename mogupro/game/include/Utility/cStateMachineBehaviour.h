#pragma once
#include <string>
#include <functional>
#include <vector>
#include <boost/any.hpp>
#include <Utility/cUserPointer.hpp>
namespace Utility
{
class cStateNode;
class cStateAllow
{
public:
	cStateAllow( Utility::softptr<cStateNode> nextNode, std::function<bool( Utility::softptr<cStateNode> )> transitionInfo, std::function<boost::any( Utility::softptr<cStateNode> )> message );
	//! ���̑J�ڐ�
	Utility::softptr<cStateNode> nextNode;
	//! �Ԃ�l��true�ɂȂ�����X�e�[�g���J�ڂ��܂��B
	std::function<bool( Utility::softptr<cStateNode> n )> transitionInfo;
	//! �J�ڐ�ɑ���悤�̃��b�Z�[�W�ł��B
	std::function<boost::any( Utility::softptr<cStateNode> )> message;
};
class cStateNode : public std::enable_shared_from_this<cStateNode>
{
public:
	//! ���̃X�e�[�g�̖��O
	std::string name;
	//! �J�ڂ��ꂽ�u�ԂɌĂ΂�܂��B
	std::function<void( boost::any message )> onStateIn;
	//! �J�ڂ���u�ԂɌĂ΂�܂��B
	std::function<void( )> onStateOut;
	//! ���݂̃X�e�[�g���I������Ă����疈�t���[���Ă΂�܂��B
	std::function<void( Utility::softptr<cStateNode> self )> onStateStay;
	//! �m�[�h���Ă΂ꑱ������莞�Ԃ������Ă����܂��B
	float time = 0.0F;
	//! �m�[�h���J�ڂ����悤�ȏ�Ԃł���ΑJ�ڐ��Ԃ��܂��Bdefault: none
	Utility::softptr<cStateAllow> update( float delta );
	//! ���̃m�[�h�Ɍq��������w�肵�܂��B
	void join( Utility::hardptr<cStateNode> nextNode, std::function<bool( Utility::softptr<cStateNode> )> transitionInfo, std::function<boost::any( Utility::softptr<cStateNode> )> message = nullptr );
private:
	//! �J�ڐ�̕ێ�
	std::vector<Utility::hardptr<cStateAllow>> nextNodes;
};
class cStateMachineBehaviour
{
public:
    cStateMachineBehaviour( ) = default;
	~cStateMachineBehaviour( ) = default;
	Utility::softptr<cStateNode> generate( std::string const& name );
	#define STATE_GENERATE(stateMachine, name) auto name = stateMachine.generate( #name )
	void setEntryNode( Utility::softptr<cStateNode> entry );
	void update( float delta );
	bool isCurrentState( std::string const& stateName ) const;
	std::string const& getCurrentStateName( ) const;
private:
	Utility::softptr<cStateNode> entry;
	Utility::softptr<cStateNode> current;
	std::vector<Utility::hardptr<cStateNode>> nodes;
};
}

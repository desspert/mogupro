#pragma once
#include <string>
#include <functional>
#include <set>
#include <vector>
#include <Utility/cUserPointer.hpp>
namespace Utility
{
class cStateNode : public std::enable_shared_from_this<cStateNode>
{
private:
	class cStateAllow
	{
	public:
		cStateAllow( Utility::softptr<cStateNode> nextNode, std::function<bool( Utility::softptr<cStateNode> )> transitionInfo );
		//! ���̑J�ڐ�
		Utility::softptr<cStateNode> nextNode;
		//! �Ԃ�l��true�ɂȂ�����X�e�[�g���J�ڂ��܂��B
		std::function<bool( Utility::softptr<cStateNode> n )> transitionInfo;
	};
public:
	//! �J�ڐ��null�����B
	static const Utility::hardptr<cStateNode> none;
	//! ���̃X�e�[�g�̖��O
	std::string name;
	//! �J�ڂ��ꂽ�u�ԂɌĂ΂�܂��B
	std::function<void( Utility::softptr<cStateNode> prev )> onStateIn;
	//! �J�ڂ���u�ԂɌĂ΂�܂��B
	std::function<void( Utility::softptr<cStateNode> next )> onStateOut;
	//! ���݂̃X�e�[�g���I������Ă����疈�t���[���Ă΂�܂��B
	std::function<void( Utility::softptr<cStateNode> self )> onStateStay;
	//! �m�[�h���J�ڂ����悤�ȏ�Ԃł���ΑJ�ڐ��Ԃ��܂��Bdefault: none
	Utility::softptr<cStateNode> update( );
	//! ���̃m�[�h�Ɍq��������w�肵�܂��B
	void join( Utility::hardptr<cStateNode> nextNode, std::function<bool( Utility::softptr<cStateNode> )> transitionInfo );
private:
	//! �J�ڐ�̕ێ�
	std::set<Utility::hardptr<cStateAllow>> nextNodes;
};
class cStateMachineBehaviour
{
public:
    cStateMachineBehaviour( ) = default;
    ~cStateMachineBehaviour( ) = default;
	Utility::softptr<cStateNode> generate( std::string const& name = "" );
	void setEntryNode( Utility::softptr<cStateNode> entry );
	void update( );
	bool isCurrentState( std::string const& stateName ) const;
private:
	Utility::softptr<cStateNode> entry;
	Utility::softptr<cStateNode> current;
	std::vector<Utility::hardptr<cStateNode>> nodes;
};
}

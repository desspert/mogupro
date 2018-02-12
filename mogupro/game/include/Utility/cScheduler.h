#pragma once
#include <Utility/cSingletonAble.h>
#include <cinder/Timeline.h>
#include <Node/node.h>
#include <limits>
#include <set>
#include <Utility/cIdentifier.h>
namespace Utility
{
class cScheduler : public Utility::cSingletonAble<cScheduler>
{
public:
    cScheduler( );
    ~cScheduler( ) = default;
public:
	// ���b�����Ɏ��s�������̂�
	// ���s���������\�b�h
	// �Ă�ŗ~������ default:�����ɌJ��Ԃ�
	hardptr<int> apply( float updateSeconds, std::function<void()> method, int callNum = std::numeric_limits<int>::max( ) );
	hardptr<int> applyLimitUpdate( float updateSeconds, std::function<void(float)> method, std::function<void()> finalizeMethod = nullptr );
	void update( float delta );
private:
	hardptr<Node::node> mRoot;
	std::set<hardptr<int>> mHandles;
	Utility::cIdentifier mIdGen;
	struct LimitUpdateMethod { std::function<void(float)> update; std::function<void()> finalize; };

	std::map<float, LimitUpdateMethod> mUpdateMethods;
	std::map<hardptr<int>, float> mUpdateMethodHandles;
};
}

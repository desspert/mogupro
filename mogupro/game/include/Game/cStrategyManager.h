#pragma once
#include"Utility\cSingletonAble.h"
#include"Game\cObjectBase.h"
#include"Game/Strategy/cStrategyObjectBase.h"
#include"cinder\AxisAlignedBox.h"
#include<list>

namespace Game
{
class cStrategyManager : public Utility::cSingletonAble<cStrategyManager>
{
public:
    cStrategyManager();
    ~cStrategyManager();
    void setup();
    void draw();
    void update(const float& deltatime = 0);
    template<class T>
    void CreateStrategyObject( T _object );
    bool isAABB( const ci::AxisAlignedBox & a, const ci::AxisAlignedBox & b );
private:
    std::list<std::shared_ptr<Strategy::cStrategyObjectBase>>strategyobjects;
    void deleteObject();
	int id_counter = 0;
};

template<class T>
inline void cStrategyManager::CreateStrategyObject( T _object )
{
    strategyobjects.push_back( std::make_shared<T>( _object ) );
	id_counter++;
}

}
#define STRM Game::cStrategyManager::getInstance()
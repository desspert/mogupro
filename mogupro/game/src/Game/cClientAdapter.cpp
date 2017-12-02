#include <Game/cClientAdapter.h>
#include <Network/cUDPClientManager.h>
#include <Network/cDeliverManager.h>
#include <Network/cEventManager.h>
#include <Network/cRequestManager.h>
#include <Network/cResponseManager.h>
#include <Game/cGemManager.h>
#include <Game/cPlayerManager.h>
#include <Game/cStrategyManager.h>
#include <Game/cFieldManager.h>
#include <Game/cSubWeaponManager.h>
using namespace cinder;
using namespace Network;
using namespace Network::Packet;
using namespace Network::Packet::Deliver;
using namespace Network::Packet::Event;
using namespace Network::Packet::Request;
using namespace Network::Packet::Response;
namespace Game
{
cClientAdapter::cClientAdapter( )
    : mBreakBlocksPecket( new cDliBreakBlocks( ) )
{
}
cClientAdapter::~cClientAdapter( )
{
    delete mBreakBlocksPecket;
}
void cClientAdapter::update( )
{
    // ブロックだけはまとめてで送信します。
    sendBreakBlocks( );

    // サーバーから受信したものがあった場合は取り出して、
    // 各マネージャーに伝えます。
    recvAllPlayers( );
    recvAllQuarrys( );
    recvAllGems( );
    recvAllBreakBlocks( );
	recvAllBombs( );
}
void cClientAdapter::recvAllPlayers( )
{
    auto e = cEventManager::getInstance( );
	auto s = cResponseManager::getInstance( );

    while ( auto packet = e->getEvePlayers( ) )
    {
        auto players = Game::cPlayerManager::getInstance( )->getPlayers( );
        for ( auto& o : packet->mPlayerFormats )
        {
            players[o.playerId]->setPos( o.position );
        }
    }
	while ( auto packet = e->getEveDamage( ) )
	{
		// TODO:プレイヤーにダメージを与える。
	}
	while ( auto packet = e->getEvePlayerDeath( ) )
	{
		// TODO:プレイヤーをキルする。
	}
	while ( auto packet = s->getResCheckPlayerDeath( ) )
	{
		if ( !packet->isSuccess ) continue;
		// TODO:プレイヤーをキルする。かつ成功ならキル表示をする。
	}
	while ( auto packet = e->getEveRespawn( ) )
	{
		// TODO:プレイヤーをリスポーンさせる。
	}
}
void cClientAdapter::recvAllQuarrys( )
{
    auto res = cResponseManager::getInstance( );
    while ( auto packet = res->getResCheckSetQuarry( ) )
    {
        if ( packet->mIsSucceeded )
        {
            Game::cStrategyManager::getInstance( )->CreateDrill(
                packet->mPosition,
                packet->mDrillId,
                static_cast<Game::Strategy::cDrill::DrillType>( packet->mType ),
                true
            );
        }
    }
    auto eve = cEventManager::getInstance( );
    while ( auto packet = eve->getEveSetQuarry( ) )
    {
        Game::cStrategyManager::getInstance( )->CreateDrill(
            packet->mPosition,
            packet->mDrillId,
            static_cast<Game::Strategy::cDrill::DrillType>( packet->mType ),
            packet->mTeamId == Game::cPlayerManager::getInstance()->getActivePlayerTeamId( )
        );
    }
}
void cClientAdapter::recvAllGems( )
{
    auto eve = cEventManager::getInstance( );
    while ( auto packet = eve->getEveGetJemQuarry( ) )
    {
        Game::cStrategyManager::getInstance( )->HitDrillToGem(
            packet->mDrillId,
            packet->mGemId
        );
    }
    while ( auto packet = eve->getEveGetJemPlayer( ) )
    {
		// TODO: プレイヤーが宝石を取得する。
    }
    auto res = cResponseManager::getInstance( );
    while ( auto packet = res->getResCheckGetJemQuarry( ) )
    {
        if ( !packet->mIsSuccessed ) continue;
        Game::cStrategyManager::getInstance( )->HitDrillToGem(
            packet->mDrillId,
            packet->mGemId
        );
    }
    while ( auto packet = res->getResCheckGetJemPlayer( ) )
    {
        if ( !packet->mIsSuccessed ) continue;
		// TODO: プレイヤーが宝石を取得する。
    }
}
void cClientAdapter::recvAllBreakBlocks( )
{
    auto eve = cEventManager::getInstance( );
    while ( auto packet = eve->getEveBreakBlocks( ) )
    {
        for ( auto& o : packet->mBreakFormats )
        {
            Game::cFieldManager::getInstance( )->blockBreakNetwork(
                o.position, o.radius, o.type
            );
        }
    }
}
void cClientAdapter::recvAllBombs( )
{
	auto eve = cEventManager::getInstance( );
	while ( auto packet = eve->getEveLightBomb( ) )
	{
		SUBWM->createLightBomb( packet->position, packet->speed, cinder::vec3(0.5F), packet->playerId );
	}
}
void cClientAdapter::sendBreakBlock( cinder::vec3 const & position, float radius, Network::ubyte1 type )
{
    // ブロック破壊は一旦バッファに詰めておきます。
    mBreakBlocksPecket->mBreakFormats.emplace_back( position, radius, type );
}
void cClientAdapter::sendSetQuarry( cinder::vec3 const & position, Network::ubyte1 drillType )
{
    auto packet = new cReqCheckSetQuarry( );
    packet->mPosition = position;
    packet->mType = drillType;
    packet->mTeamId = cPlayerManager::getInstance( )->getActivePlayerTeamId( );
    cUDPClientManager::getInstance( )->send( packet );
}
void cClientAdapter::sendPlayer( cinder::vec3 const & position, cinder::quat const & rotation )
{
    auto packet = new cDliPlayer( );
    packet->mFormat.playerId = cPlayerManager::getInstance( )->getActivePlayerId( );
    packet->mFormat.position = position;
    packet->mFormat.rotation = rotation;
    cUDPClientManager::getInstance( )->send( packet );
}
void cClientAdapter::sendGetGemPlayer( Network::ubyte2 gemId )
{
    auto packet = new cReqCheckGetJemPlayer( );
    packet->mPlayerId = cPlayerManager::getInstance( )->getActivePlayerId( );
    packet->mGemId = gemId;
    cUDPClientManager::getInstance( )->send( packet );
}
void cClientAdapter::sendGetGemQuarry( Network::ubyte2 drillId, Network::ubyte2 gemId )
{
    auto packet = new cReqCheckGetJemQuarry( );
    packet->mDrillId = drillId;
    packet->mGemId = gemId;
    cUDPClientManager::getInstance( )->send( packet );
}
void cClientAdapter::sendLightBomb( cinder::vec3 const & position, cinder::vec3 const & speed )
{
	auto packet = new cReqCheckLightBomb( );
	packet->playerId = cPlayerManager::getInstance( )->getActivePlayerId( );
	packet->position = position;
	packet->speed = speed;
	cUDPClientManager::getInstance( )->send( packet );
}
void cClientAdapter::sendKill( Network::ubyte1 enemyId )
{
	auto p = new cReqCheckPlayerDeath( );
	p->enemyId = enemyId;
	p->playerId = cPlayerManager::getInstance( )->getActivePlayerId( );
	cUDPClientManager::getInstance( )->send( p );
}
void cClientAdapter::sendDamage( Network::ubyte1 enemyId, float damage )
{
	auto p = new cReqDamage( );
	p->enemyId = enemyId;
	p->playerId = cPlayerManager::getInstance( )->getActivePlayerId( );
	p->damage = damage;
	cUDPClientManager::getInstance( )->send( p );
}
void cClientAdapter::sendRespawn( )
{
	auto p = new cReqRespawn( );
	p->playerId = cPlayerManager::getInstance( )->getActivePlayerId( );
	cUDPClientManager::getInstance( )->send( p );
}
void cClientAdapter::sendBreakBlocks( )
{
    if ( !mBreakBlocksPecket->mBreakFormats.empty( ) )
    {
        cUDPClientManager::getInstance( )->send( mBreakBlocksPecket );
        mBreakBlocksPecket = new Packet::Deliver::cDliBreakBlocks( );
    }
}
}

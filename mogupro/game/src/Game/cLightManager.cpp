#include <Game/cLightManager.h>
#include <Game/cGemManager.h>
#include <Game/cPlayerManager.h>
#include <random>
namespace Game
{
void cLightManager::setup( )
{
	// プレイヤーにポイントライトを適用します。
	// ※100個しか作成できないのでaddしすぎないように。
	auto const& players = Game::cPlayerManager::getInstance( )->getPlayers( );
	for ( int i = 0; i < players.size( ); ++i )
	{
		cinder::vec3 color;
		switch ( players[i]->getWhichTeam( ) )
		{
		case Game::Player::Team::Blue:
			color = { 0.8, 0.8, 1 };
			break;
		case Game::Player::Team::Red:
			color = { 1, 0.8, 0.8 };
			break;
		default:
			break;
		}
		mPointLightHandles.emplace_back( Game::cLightManager::getInstance( )->addPointLight( players[i]->getPos( ), color, 0.0F ) );
	}
	// ジェムにポイントライトを適用します。
	//for ( int i = 0; i < GemManager->getGems( ).size( ); ++i )
	//{
	//	Game::cLightManager::getInstance( )->addPointLight( GemManager->getGems( )[i]->getPos( ), GemManager->getGems( )[i]->getColor( ), 0.0F );
	//}
}
void cLightManager::update( )
{
	auto const& players = Game::cPlayerManager::getInstance( )->getPlayers( );
	for ( int i = 0; i < players.size( ); ++i )
	{
		mPointLightHandles[i]->position = players[i]->getPos( );
	}
}
std::set<Utility::hardptr<PointLightParam>> const & cLightManager::getPointLights( ) const
{
	return mPointLights;
}
Utility::softptr<PointLightParam> cLightManager::addPointLight( cinder::vec3 position, cinder::vec3 color, float radius )
{
	auto temp = mPointLights.insert( std::make_shared<PointLightParam>( position, color, radius ) );
	if ( !temp.second )
	{
		throw std::runtime_error( "やばい。" );
	}
	return *temp.first;
}
void cLightManager::removePointLight( Utility::softptr<PointLightParam> handle )
{
	mPointLights.erase( handle );
}
}

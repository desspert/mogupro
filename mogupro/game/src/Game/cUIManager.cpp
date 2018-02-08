#include <Game/cUIManager.h>
#include <Node/renderer.hpp>
#include <boost/date_time.hpp>
#include <cinder/gl/gl.h>
#include <Node/action.hpp>
#include <Game/cPlayerManager.h>
#include <Game/cGameManager.h>
#include <Resource/cImageManager.h>
#include <Resource/cObjectManager.h>
#include <Game/UI/cItemUIGenerator.h>
#include <Game/UI/cCannonMeter.h>
#include <Game/UI/cItemSlot.h>
#include <Game/UI/cPlayerNameUIs.h>
#include <Game/UI/cTips.h>
#include <Scene/cSceneManager.h>
#include <Scene/Member/Tutorial.h>
#include <Game/UI/cTargetCannon.h>
//Weapons::SubWeapon::SubWeaponType
using namespace ci;
namespace Game
{
void cUIManager::awake( )
{
	// ���[�g�쐬
	mRoot = Node::node::create( );
	mRoot->set_content_size( app::getWindowSize( ) );
	mRoot->set_schedule_update( );
	mRoot->set_scale( vec2( 1, -1 ) );
	mRoot->set_position( mRoot->get_content_size( ) * vec2( -0.5F, 0.5F ) );

	//�v���C���[���_���[�W���󂯂����̉�ʂ̎���̌�
	mPlayerScreenEffect = mRoot->add_child( Node::node::create( ) );
	auto damage_effect = mPlayerScreenEffect->add_child( Node::Renderer::sprite::create( "Player/screeneffect.png" ) );
	damage_effect->set_name( "player_screen_effect" );
	damage_effect->set_position( mRoot->get_content_size( ) * vec2( 0.5F ) );

	mSlot = mRoot->add_child( UI::cItemSlot::create( mRoot->get_content_size( ) ) );
}
void cUIManager::setup( )
{
	auto playerTeamId = ( Player::Team )cPlayerManager::getInstance( )->getActivePlayerTeamId( );
	mRedTeamCannonMeter = mRoot->add_child( UI::cCannonMeter::create( mRoot->get_content_size( ), playerTeamId, Player::Team::Red ) );
	mBlueTeamCannonMeter = mRoot->add_child( UI::cCannonMeter::create( mRoot->get_content_size( ), playerTeamId, Player::Team::Blue ) );

	mRoot->add_child( UI::cPlayerNameUIs::create( ) );

	mRoot->add_child( UI::cTargetCannon::create( playerTeamId ) );

	if (!Scene::cSceneManager::getInstance()->isCurrentScene<Scene::Member::cTutorial>())
	{
		// �^�C�}�[�쐬
		mTime = mRoot->add_child(Node::Renderer::sprite::create(Resource::cImageManager::getInstance()->find("gameMainUI/timer.png")));
		mTime->set_anchor_point(vec2(0.5F, 0.0F));
		mTime->set_position(mRoot->get_content_size() * vec2(0.5F, 0.0F));
		mTime->set_pivot(vec2(0.5F, 0.125F));
		auto l = mTime->add_child(Node::Renderer::letter::create("AMEMUCHIGOTHIC-06.ttf", 36.0F));
		l->set_space(-9.0F);
		l->set_name("letter");
		l->set_text("12:34");
		l->set_color(ColorA(0, 0, 0));

		mRoot->add_child(UI::cTips::create(mRoot->get_content_size(), playerTeamId));
	}
}
void cUIManager::update( float delta )
{
	mRoot->entry_update( delta );

	if (mTime)
	{
		auto l = mTime->get_child_by_name("letter").dynamicptr<Node::Renderer::letter>();
		l->set_text(cGameManager::getInstance()->getLeftBattleTime());
	}

	for ( auto player : cPlayerManager::getInstance( )->getPlayers( ) )
	{
		auto const pID = player->getPlayerId( );
		if ( ( pID == 3U ) || ( pID == 7U ) )
			continue;

		softptr<Node::node> target;

		if ( pID >= 0.0F && pID <= 2 ) //! red
		{
			switch ( pID )
			{
			case 0:
				target = mRedTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player1;
				break;
			case 1:
				target = mRedTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player2;
				break;
			case 2:
				target = mRedTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player3;
				break;
			default:
				break;
			}
		}
		else //! blue
		{
			switch ( pID )
			{
			case 4:
				target = mBlueTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player1;
				break;
			case 5:
				target = mBlueTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player2;
				break;
			case 6:
				target = mBlueTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->player3;
				break;
			default:
				break;
			}
		}
		
		target->get_child_by_name( "live" )->set_visible( !player->isDead( ) );
		target->get_child_by_name( "dead" )->set_visible( player->isDead( ) );
		target->get_child_by_name( "watch" )->set_visible( cPlayerManager::getInstance( )->getWatchingTargetPlayerId( ) == player->getPlayerId( ) );
	}

	//�v���C���[���_���[�W���󂯂����̉�ʂ̎���̌�
	int player_hp = cPlayerManager::getInstance( )->getActivePlayer( )->getStatus( ).hp;
	mPlayerScreenEffect->get_child_by_name( "player_screen_effect" )->set_color( ci::ColorA( 1, 1, 1, 1 - ( player_hp / 100 ) ) );

}
void cUIManager::draw( )
{
	mRoot->entry_render( mat4( ) );
}
void cUIManager::setRedCannonPower( int value )
{
	mRedTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->addPower( value );
}
void cUIManager::setBlueCannonPower( int value )
{
	mBlueTeamCannonMeter.dynamicptr<UI::cCannonMeter>( )->addPower( value );
}
void cUIManager::setItem( boost::optional<int> currentItem, boost::optional<int> nextItem )
{
	auto capsules = mSlot.dynamicptr<UI::cItemSlot>( )->capsules;
	auto current = capsules->get_child_by_name( "current" );
	auto next = capsules->get_child_by_name( "next" );
	if ( currentItem && current->get_children( ).empty( ) )
	{
		current->add_child( UI::cItemUIGenerator::createItem( static_cast<Weapons::SubWeapon::SubWeaponType>( *currentItem ) ) );
	}
	else if ( nextItem && next->get_children( ).empty( ) )
	{
		next->add_child( UI::cItemUIGenerator::createItem( static_cast<Weapons::SubWeapon::SubWeaponType>( *nextItem ) ) );
	}
	else if ( !nextItem && !next->get_children( ).empty( ) )
	{
		current->remove_all_children( );
		next->get_children( ).front( )->set_parent( current );
	}
	else
	{
		current->remove_all_children( );
	}
}
void cUIManager::enable( )
{
	mRoot->set_block_visible( false );
}
void cUIManager::disable( )
{
	mRoot->set_block_visible( true );
}
}

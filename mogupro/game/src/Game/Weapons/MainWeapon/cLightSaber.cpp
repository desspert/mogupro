#include <Game/Weapons/MainWeapon/cLightSaber.h>
#include <cinder/gl/gl.h>
#include <Utility/cInput.h>
#include <CameraManager/cCameraManager.h>
#include <Resource/cObjectManager.h>
#include <Resource/TextureManager.h>
#include <Resource/cSoundManager.h>
#include <Game/cGemManager.h>
#include <Particle/cParticleManager.h>
#include <Game/cClientAdapter.h>
#include <Math/Quat.h>
#include <cinder/gl/gl.h>
#include <Node/action.hpp>
#include <Game/cPlayerManager.h>
#include <Game/cLightManager.h>
using namespace Node::Action;
using namespace cinder;
namespace Game
{
namespace Weapons
{
namespace MainWeapon
{
cLightSaber::cLightSaber( Player::cPlayer const& player )
	: cBase( player )
{

}
void cLightSaber::setup( )
{
	STATE_GENERATE( stateMachine, idle );
	STATE_GENERATE( stateMachine, left_slash );
	STATE_GENERATE( stateMachine, right_slash );
	STATE_GENERATE( stateMachine, chage_hold );
	STATE_GENERATE( stateMachine, shot );
	STATE_GENERATE( stateMachine, chage_hold_max );
	STATE_GENERATE( stateMachine, shot_max );

	// �A�C�h�� 
	{
		idle->join( left_slash, [ &, this ]( auto n )
		{
			// 0.2�b�ȓ��ɃN���b�N�𗣂�����X���b�V��
			return ( n->time < 0.2F ) && pull;
		} );
		idle->join( chage_hold, [ this ] ( auto n )
		{
			// 0.2�b�ȏ�z�[���h��Ԃ���������z�[���h
			return ( n->time >= 0.2F ) && press;
		} );
		idle->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 1, 0, 0 ) );
				gl::drawCube( vec3(0), vec3(0.1F) );
			};
		};
	}
	// ���X���b�V�����ۂ̓���
	{
		left_slash->join( right_slash, [ this ] ( auto n )
		{
			// 1.0 ~ 1.6�b�̊ԂɃN���b�N�������������x�X���b�V��������
			return  ( n->time >= 1.0F ) && ( n->time < 1.6F ) && push;
		} );
		left_slash->join( idle, [ this ] ( auto n )
		{
			// ���X���b�V�����������鎞�Ԃ��߂�����A�C�h��
			return ( n->time >= 1.6F );
		} );
		left_slash->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 0, 1, 0 ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}
	// �E�X���b�V��
	{
		right_slash->join( idle, [ this ] ( auto n )
		{
			return ( n->time >= 1.6F );
		} );
		right_slash->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 0, 0, 1 ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}
	// �`���[�W�V���b�g����
	{
		chage_hold->join( chage_hold_max, [ this ] ( auto n )
		{
			return n->time >= 2.0F;
		} );
		chage_hold->join( shot, [ this ] ( auto n )
		{
			// �r���Ŕ��˂����ꍇ�B
			return ( n->time < 2.0F ) && pull;
		}, [ ] ( auto n )
		{
			return n->time / 2.0F;
		} );
		chage_hold->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 1, 1, 0 ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}
	// �`���[�W�V���b�g����
	{
		shot->onStateIn = [ this ] ( auto m )
		{
			float power = boost::any_cast<float>( m );
		};
		shot->join( idle, [ this ] ( auto n )
		{
			return n->time > 2.0F;
		} );
		shot->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 0, 1, 1 ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}
	// �`���[�W�V���b�g���E�l���
	{
		chage_hold_max->join( shot_max, [ this ] ( auto n )
		{
			return pull;
		} );
		chage_hold_max->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 1, 0, 1 ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}
	// �`���[�W�V���b�g����
	{
		shot_max->join( idle, [ this ] ( auto n )
		{
			return n->time > 2.0F;
		} );
		shot_max->onStateIn = [ this ] ( auto m )
		{
			drawFunc = [ this ]
			{
				gl::ScopedColor col( ColorA( 1, 0.5F, 0.5F ) );
				gl::drawCube( vec3( 0 ), vec3( 0.1F ) );
			};
		};
	}

	stateMachine.setEntryNode( idle );
}
void cLightSaber::update( const float& delta_time )
{
	stateMachine.update( delta_time );
	flashInput( );
}
void cLightSaber::draw( )
{
	drawFunc( );
}
void cLightSaber::reset( )
{

}
}
}
}
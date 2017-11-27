#include <Utility/cInput.h>
#include <cinder/app/App.h>
#include <Node/action.hpp>
#include <Windows.h>
#include <CameraManager/cCameraManager.h>
extern "C"
{
	#include <GamePad.h>
}
#pragma comment(lib,"winmm.lib")
#if _DEBUG
#pragma comment(lib,"Gamepad_d.lib")
#else
#pragma comment(lib,"Gamepad.lib")
#endif 
namespace Utility
{
#pragma region �O������A�N�Z�X�����֐��Q
cInputAll::cInputAll( )
	: cursor_captured( false )
	, mouse_active( false )
{
}
void cInputAll::setMouseControl( const bool & flag )
{
	mouse_active = flag;
}
ci::vec2 cInputAll::getMouseVec( )
{
	return mouse_vec;
}
ci::vec2 cInputAll::getMousePos( )
{
	return mouse_pos;
}
bool cInputAll::pressKey( const int& pressed_key ) {
	return press.find( pressed_key ) != press.end( );
}
bool cInputAll::pushKey( const int & pressed_key )
{
	return push.find( pressed_key ) != push.end( );
}
bool cInputAll::pullKey( const int & pressed_key )
{
	return pull.find( pressed_key ) != pull.end( );
}
bool cInputAll::anyKey( )
{
	return !press.empty( );
}
bool cInputAll::isPadPush( const int & num )
{
	if ( padpush.find( num ) == padpush.end( ) )
		return false;
	padpush.erase( padpush.find( num ) );
	return true;
}
bool cInputAll::isPadPress( const int & num )
{
	if ( padpress.find( num ) == padpress.end( ) )
		return false;
	return true;
}
bool cInputAll::isPadPull( const int & num )
{
	if ( padpull.find( num ) == padpull.end( ) )
		return false;
	padpull.erase( padpull.find( num ) );
	return true;
}
//�O�ō��X�e�B�b�N�̍��E�i���j
//�P�ō��X�e�B�b�N�̏㉺�i���j�����Ӂ@�㉺���t
//�Q�A�R���E�X�e�B�b�N
float cInputAll::getPadAxis( const int & pad_num )
{
	if ( pad_stick_axis_value.find( pad_num ) == pad_stick_axis_value.cend( ) )
		return 0.0f;

	//�������Ȃ��Ă������̂Ő���
	if ( std::abs( pad_stick_axis_value.find( pad_num )->second ) <= 0.2f )
		return 0.0f;

	return pad_stick_axis_value.find( pad_num )->second;
}
void cInputAll::flashInput( )
{
	push.clear( );
	pull.clear( );
	padpush.clear( );
	padpull.clear( );
}
#pragma endregion
#pragma region �v���C�x�[�g�֐��Q
void cInputAll::setup( )
{
	Gamepad_deviceAttachFunc( [ ] ( Gamepad_device* device, void * context )
	{
		// TODO: �p�b�h�����������̏���
		ci::app::console( ) << "Device ID " << device->deviceID << " attached (vendor = " << device->vendorID << "; product = " << device->productID << ") with context" << context << std::endl;
	}, (void *)0x1 );
	Gamepad_deviceRemoveFunc( [ ] ( Gamepad_device* device, void * context )
	{
		// TODO: �p�b�h�𔲂������̏���
		ci::app::console( ) << "Device ID " << device->deviceID << " removed with context " << context << std::endl;
	}, (void *)0x2 );
	Gamepad_buttonDownFunc( [ ] ( Gamepad_device* device, unsigned int buttonID, double timestamp, void * context )
	{
		ENV->setPadPush( buttonID );
		ENV->setPadPress( buttonID );
	}, (void *)0x3 );
	Gamepad_buttonUpFunc( [ ] ( Gamepad_device* device, unsigned int buttonID, double timestamp, void * context )
	{
		ENV->setPadPull( buttonID );
		ENV->erasePadPress( buttonID );
	}, (void *)0x4 );
	Gamepad_axisMoveFunc( [ ] ( Gamepad_device* device, unsigned int axisID, float value, float lastValue, double timestamp, void * context )
	{
		if ( value < 0.3f || value > 0.3f )
		{
			ENV->setPadAxis( axisID, value );
		}
	}, (void *)0x5 );
	Gamepad_init( );

	pad_stick_axis_value.insert( std::make_pair( STICK_LEFT_HORIZONTAL, 0.0f ) );
	pad_stick_axis_value.insert( std::make_pair( STICK_LEFT_VERTICAL, 0.0f ) );
	pad_stick_axis_value.insert( std::make_pair( STICK_RIGHT_HORIZONTAL, 0.0f ) );
	pad_stick_axis_value.insert( std::make_pair( STICK_RIGHT_VERTICAL, 0.0f ) );
	pad_stick_axis_value.insert( std::make_pair( CROSS_HORIZONTAL, 0.0f ) );
	pad_stick_axis_value.insert( std::make_pair( CROSS_VERTICAL, 0.0f ) );

	// �Q�[���p�b�h�����������󋵂̍X�V�����܂��B
	using namespace Node::Action;
	mPadScheduler = Node::node::create( );
	mPadScheduler->set_schedule_update( );
	mPadScheduler->run_action( repeat_forever::create( sequence::create( delay::create( 1.0F ), call_func::create( [ this ]
	{
		Gamepad_detectDevices( );
	} ) ) ) );
}
void cInputAll::update( float delta )
{
	mPadScheduler->entry_update( delta );
}
void cInputAll::cleanup( )
{
	Gamepad_processEvents( );
}
void cInputAll::setPadPush( const int & num )
{
	if ( padpress.find( num ) == padpress.end( ) )
		padpush.emplace( num );
}
void cInputAll::setPadPress( const int & num )
{
	padpress.emplace( num );
}
void cInputAll::setPadPull( const int & num )
{
	padpull.emplace( num );
}
void cInputAll::erasePadPress( const int & num )
{
	padpress.erase( padpress.find( num ) );
}

void cInputAll::setPadAxis( const int & num, const float & value_ )
{
	pad_stick_axis_value.find( num )->second = value_;
}
void cInputAll::keyDown( const ci::app::KeyEvent& event ) {
	if ( !pressKey( event.getCode( ) ) )
	{
		push.insert( event.getCode( ) );
	}
	press.insert( event.getCode( ) );
}
void cInputAll::keyUp( const ci::app::KeyEvent& event )
{
	press.erase( event.getCode( ) );

	pull.insert( event.getCode( ) );
}
void mouseCursolFixed( const ci::app::MouseEvent& event, ci::vec2& inc_pos,
					   ci::vec2& mouse_vec, bool& cursor_captured, ci::ivec2& last_cursor_pos ) {
	//�P�t���[���ڈȍ~
	if ( cursor_captured ) {
		POINT pt;

		GetCursorPos( &pt );
		POINT delta;
		delta.x = pt.x - last_cursor_pos.x;
		delta.y = pt.y - last_cursor_pos.y;

		if ( delta.x != 0 || delta.y != 0 ) {
			SetCursorPos( last_cursor_pos.x, last_cursor_pos.y );
			CAMERA->setCameraAngle( ci::vec2( -delta.x, -delta.y ) * 0.005f );
		}
	}
	//�P�t���[���ڂ͉������Ȃ�
	else {

		SetCursorPos( ci::app::getWindowPos( ).x + ( ci::app::getWindowSize( ).x / 2 ),
					  ci::app::getWindowPos( ).y + ( ci::app::getWindowSize( ).y / 2 ) );
		POINT pt;
		GetCursorPos( &pt );
		last_cursor_pos.x = pt.x;
		last_cursor_pos.y = pt.y;
		mouse_vec.x = last_cursor_pos.x;
		mouse_vec.y = last_cursor_pos.y;
		cursor_captured = true;
	}
}
void setMousePos( ci::vec2& pos ) {
	POINT pt;
	GetCursorPos( &pt );
	pos.x = pt.x;
	pos.y = pt.y;
}
void cInputAll::mouseMove( const ci::app::MouseEvent & event )
{
	setMousePos( mouse_pos );
	if ( !mouse_active ) return;
	mouseCursolFixed( event, inc_pos, mouse_vec, cursor_captured, last_cursor_pos );
}
void cInputAll::mouseDrag( const ci::app::MouseEvent & event )
{
	if ( !mouse_active ) return;
	mouseCursolFixed( event, inc_pos, mouse_vec, cursor_captured, last_cursor_pos );
}
void cInputAll::mouseDown( const ci::app::MouseEvent& event )
{
	if ( event.isLeft( ) )
	{
		press.insert( ci::app::MouseEvent::LEFT_DOWN );
		push.insert( ci::app::MouseEvent::LEFT_DOWN );
	}
	if ( event.isRight( ) )
	{
		press.insert( ci::app::MouseEvent::RIGHT_DOWN );
		push.insert( ci::app::MouseEvent::RIGHT_DOWN );
	}
	if ( event.isMiddle( ) )
	{
		press.insert( ci::app::MouseEvent::MIDDLE_DOWN );
		push.insert( ci::app::MouseEvent::MIDDLE_DOWN );
	}
}
void cInputAll::mouseUp( const ci::app::MouseEvent& event )
{
	if ( event.isLeft( ) )
	{
		pull.insert( ci::app::MouseEvent::LEFT_DOWN );
		press.erase( ci::app::MouseEvent::LEFT_DOWN );
	}
	if ( event.isRight( ) )
	{
		pull.insert( ci::app::MouseEvent::RIGHT_DOWN );
		press.erase( ci::app::MouseEvent::RIGHT_DOWN );
	}
	if ( event.isMiddle( ) )
	{
		pull.insert( ci::app::MouseEvent::MIDDLE_DOWN );
		press.erase( ci::app::MouseEvent::MIDDLE_DOWN );
	}
}
#pragma endregion
}

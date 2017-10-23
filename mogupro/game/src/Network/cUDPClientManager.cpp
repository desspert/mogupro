#include <Network/cUDPClientManager.h>
#include <Network/cDeliverManager.h>
#include <Network/cEventManager.h>
#include <Network/cRequestManager.h>
#include <Network/cResponseManager.h>
#include <cinder/app/App.h>
#include <limits>
#include <Utility/MessageBox.h>
#include <Network/cUDPManager.h>
#include <Scene/cSceneManager.h>
#include <Scene/Member/cMatching.h>
namespace Network
{
cUDPClientManager::cUDPClientManager( )
    : mCloseSecond( std::numeric_limits<float>::max( ) )
{
}
void cUDPClientManager::close( )
{
    mSocket.close( );
}
void cUDPClientManager::open( )
{
    mSocket.open( );
}
bool cUDPClientManager::isConnected( )
{
    return mConnectServerHandle;
}
void cUDPClientManager::connect( cNetworkHandle const & handle )
{
    mCloseSecond = cinder::app::getElapsedSeconds( ) + 5.0F;

    auto packet = new Packet::Request::cReqConnect( );
    cPacketBuffer packetBuffer;
    packet->createPacket( packetBuffer );
    mSocket.write( handle, packetBuffer.transferredBytes, packetBuffer.buffer.data( ) );
    delete packet;
}
void cUDPClientManager::update( )
{
    updateSend( );
    updateRecv( );
}
void cUDPClientManager::updateSend( )
{
    if ( mConnectServerHandle )
    {
        // ���M������̂�����΃o�b�t�@�[������o���đ���B
        auto& buffer = mSendDataBuffer;
        // �]���Ă���p�P�b�g�𑗂�܂��B
        if ( !buffer.empty( ) )
        {
            mSocket.write( mConnectServerHandle, buffer.size( ), buffer.data( ) );
            buffer.clear( );
            buffer.shrink_to_fit( );
        }
    }
}
void cUDPClientManager::updateRecv( )
{
    // ��M�������̂�����΃o�b�t�@�[������o���ăp�P�b�g�̕��ʂ��s���B
    while ( !mSocket.emptyChunk( ) )
    {
        auto chunk = mSocket.popChunk( );
        cUDPManager::getInstance( )->onReceive( chunk );
    }

    connection( );
    ping( );
}
void cUDPClientManager::connection( )
{
    while ( auto p = cResponseManager::getInstance( )->getResConnect( ) )
    {
        mConnectServerHandle = p->mNetworkHandle;
    }
}
void cUDPClientManager::ping( )
{
    while ( auto p = cEventManager::getInstance( )->getEvePing( ) )
    {
        mCloseSecond = cinder::app::getElapsedSeconds( ) + 5.0F;
    }
    if ( mCloseSecond < cinder::app::getElapsedSeconds( ) )
    {
        close( );
        Utility::MessageBoxOk( "�T�[�o�[�Ƃ̐ڑ����؂�܂����B", [ ]
        {
            cSceneManager::getInstance( )->change<Scene::Member::cMatching>( );
        } );
    }
}
void cUDPClientManager::sendDataBufferAdd( cPacketBuffer const & packetBuffer )
{
    if ( !isConnected( ) )
    {
        close( );
        Utility::MessageBoxOk( "connect����������O�ɒʐM�����Ȃ��ł��������B", [ ]
        {
            cSceneManager::getInstance( )->change<Scene::Member::cMatching>( );
        } );
    }

    auto& buf = mSendDataBuffer;

    // �p�P�b�g���傫���Ȃ肻���Ȃ��ɑ����Ă��܂��܂��B
    if ( 1024 < buf.size( ) )
    {
        mSocket.write( mConnectServerHandle, buf.size( ), buf.data( ) );
        buf.clear( );
        buf.shrink_to_fit( );
    }

    ubyte2 const& byte = packetBuffer.transferredBytes;
    cBuffer const& buffer = packetBuffer.buffer;

    buf.resize( buf.size( ) + byte );
    memcpy( buf.data( ) + buf.size( ) - byte, &buffer, byte );
}
}
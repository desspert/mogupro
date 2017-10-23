#include <Network/cUDPServerManager.h>
#include <Network/cUDPManager.h>
#include <Network/cDeliverManager.h>
#include <Network/cEventManager.h>
#include <Network/cRequestManager.h>
#include <Network/cResponseManager.h>
#include <cinder/app/App.h>
#include <limits>
namespace Network
{
void cUDPServerManager::close( )
{
    mSocket.close( );
}
void cUDPServerManager::open( )
{
    mSocket.open( 25565 );
}
void cUDPServerManager::update( )
{
    updateSend( );
    updateRecv( );
}
void cUDPServerManager::updateSend( )
{
    // ���M������̂�����΃o�b�t�@�[������o���đ���B
    for ( auto& buffer : mSendDataBuffer )
    {
        // �]���Ă���p�P�b�g�𑗂�܂��B
        if ( !buffer.second.empty( ) )
        {
            mSocket.write( buffer.first, buffer.second.size( ), buffer.second.data( ) );
            buffer.second.clear( );
            buffer.second.shrink_to_fit( );
        }
    }
}
void cUDPServerManager::updateRecv( )
{
    // ��M�������̂�����΃o�b�t�@�[������o���ăp�P�b�g�̕��ʂ��s���B
    while ( !mSocket.emptyChunk( ) )
    {
        auto chunk = mSocket.popChunk( );
        if ( mHandle.find( chunk.networkHandle ) != mHandle.end( ) )
        {
            cUDPManager::getInstance( )->onReceive( chunk );
        }
    }

    connection( );
    ping( );
}
void cUDPServerManager::sendDataBufferAdd( cNetworkHandle const & networkHandle, cPacketBuffer const & packetBuffer )
{
    auto& buf = mSendDataBuffer[networkHandle];

    // �p�P�b�g���傫���Ȃ肻���Ȃ��ɑ����Ă��܂��܂��B
    if ( 1024 < buf.size( ) )
    {
        mSocket.write( networkHandle, buf.size( ), buf.data( ) );
        buf.clear( );
        buf.shrink_to_fit( );
    }

    ubyte2 const& byte = packetBuffer.transferredBytes;
    cBuffer const& buffer = packetBuffer.buffer;

    buf.resize( buf.size( ) + byte );
    memcpy( buf.data( ) + buf.size( ) - byte, &buffer, byte );
}
void cUDPServerManager::connection( )
{
    while ( auto p = cRequestManager::getInstance( )->getReqConnect( ) )
    {
        mHandle.insert( std::make_pair( p->mNetworkHandle, cinder::app::getElapsedSeconds( ) + 5.0F ) );
        send( p->mNetworkHandle, new Packet::Response::cResConnect( ) );
    }
}
void cUDPServerManager::ping( )
{
    while ( auto p = cDeliverManager::getInstance( )->getDliPing( ) )
    {
        mHandle[p->mNetworkHandle] = cinder::app::getElapsedSeconds( ) + 5.0F;
    }
    for ( auto itr = mHandle.begin( ); itr != mHandle.end( ); )
    {
        if ( itr->second < cinder::app::getElapsedSeconds( ) )
        {
            mHandle.erase( itr );
            mSendDataBuffer.erase( itr->first );
            continue;
        }
        itr++;
    }
}
}
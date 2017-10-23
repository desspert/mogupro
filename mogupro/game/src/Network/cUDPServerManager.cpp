#include <Network/cUDPServerManager.h>
#include <Network/cUDPManager.h>
#include <Network/cDeliverManager.h>
#include <Network/cEventManager.h>
#include <Network/cRequestManager.h>
#include <Network/cResponseManager.h>
#include <Game/cGemManager.h>
#include <Game/cPlayerManager.h>
#include <Game/cStrategyManager.h>
#include <Game/cFieldManager.h>
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
        cUDPManager::getInstance( )->onReceive( chunk );
    }

    connection( );
    ping( );

    sendPlayersPosition( );
    sendSetQuarry( );
    sendGetGemPlayer( );
    sendGetGemQuarry( );
    sendBreakBlocks( );
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
        mHandle.insert( std::make_pair( p->mNetworkHandle, std::numeric_limits<float>::max( ) ) );
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
void cUDPServerManager::sendPlayersPosition( )
{
    auto m = Network::cDeliverManager::getInstance( );
    while ( auto packet = m->getDliPlayer( ) )
    {
        auto id = mHandlePlayers[packet->mNetworkHandle];
        //Game::cPlayerManager::getInstance( )->setPlayerPosition( 
        //    id, 
        //    packet->mPosition, 
        //    packet->mRotation
        //);
    }
    //std::vector<cinder::vec3> const& playersPosition = Game::cPlayerManager::getInstance( )->getPlayersPosition( );
    //std::vector<cinder::quat> const& playersRotation = Game::cPlayerManager::getInstance( )->getPlayersRotation( );
    //for ( auto& players : mHandlePlayers )
    //{
    //    for(int i = 0; i <  )
    //    cUDPManager::getInstance( )->send( players.first,
    //                                       new );
    //}
}
void cUDPServerManager::sendSetQuarry( )
{
}
void cUDPServerManager::sendGetGemPlayer( )
{
}
void cUDPServerManager::sendGetGemQuarry( )
{
}
void cUDPServerManager::sendBreakBlocks( )
{
}
}
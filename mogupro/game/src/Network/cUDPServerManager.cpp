#include <Network/cUDPServerManager.h>
#include <Network/cUDPManager.h>
#include <cinder/app/App.h>
#include <limits>
#include <Node/action.hpp>
#include <Utility/MessageBox.h>
#include <Network/IpHost.h>
namespace Network
{
cUDPServerManager::cUDPServerManager( )
{
	closeAccepter( );
	mRoot = Node::node::create( );
	mRoot->set_schedule_update( );
	mServerTime = 0.0F;
}
void cUDPServerManager::close( )
{
    mRoot.reset( );
    mSocket.close( );
    closeAccepter( );
}
void cUDPServerManager::open( )
{
    mRoot = Node::node::create( );
	mServerTime = 0.0F;
    mRoot->set_schedule_update( );
    mSocket.open( 25565 );
    openAccepter( );
}
void cUDPServerManager::closeAccepter( )
{
	mIsAccept = false;
	mIdCount = 0;
	mHolder.clear( );
}
void cUDPServerManager::openAccepter( )
{
    mIsAccept = true;
}
void cUDPServerManager::update( float delta )
{
    updateRecv( );
    updateSend( );
    mRoot->entry_update( delta );
	mServerTime += delta;
}
ubyte1 cUDPServerManager::getPlayerId( cNetworkHandle const & handle )
{
    auto itr = mHolder.find( handle );
    if ( itr != mHolder.end( ) )
    {
        return itr->second.connection.id;
    }
    else
    {
        throw std::runtime_error( "Networkhandle nothing" );
    }
}
float const & cUDPServerManager::getServerTime( )
{
	return mServerTime;
}
std::vector<cUDPManager*> cUDPServerManager::getUDPManager( )
{
	std::vector<cUDPManager*> mans;
	for ( auto& m : mHolder )
	{
		mans.push_back( &m.second.manager );
	}
	return mans;
}
void cUDPServerManager::updateSend( )
{
    // ���M������̂�����΃o�b�t�@�[������o���đ���B
    for ( auto& holder : mHolder )
    {
		auto& handle = holder.first;
		auto& buf = holder.second.connection.buffer;

		// �����C�A�u���ȃf�[�^���l�߂܂��B
		auto reliableData = holder.second.connection.reliableManager.update( );
		std::copy( reliableData.begin(), reliableData.end(), std::back_inserter( buf ) );

        // �]���Ă���p�P�b�g�𑗂�܂��B
        if ( !buf.empty( ) )
        {
			mSocket.write( handle, buf.size( ), buf.data( ) );
            buf.clear( );
            buf.shrink_to_fit( );
        }
    }
}
void cUDPServerManager::updateRecv( )
{
    // ��M�������̂�����΃o�b�t�@�[������o���ăp�P�b�g�̕��ʂ��s���B
    while ( !mSocket.emptyChunk( ) )
    {
        auto chunk = mSocket.popChunk( );
		auto itr = mHolder.find( chunk.networkHandle );
		if ( cUDPManager::isConnectPacket( chunk ) )
		{
			if ( mIsAccept )
			{
				// ���łɐڑ����Ă��鑊�肪�����ꍇ�o�^���������܂��B
				if ( itr != mHolder.end( ) )
				{
					mHolder.erase( chunk.networkHandle );
					mRoot->remove_action_by_tag( itr->second.connection.id );
				}

				auto inserted = mHolder.insert( std::make_pair( chunk.networkHandle, mIdCount++ ) );
				inserted.first->second.manager.onReceive( chunk );
				inserted.first->second.manager.ReqConnect.get( );

				auto response = new Packet::Response::cResConnect( );
				response->time = mServerTime;
				send( chunk.networkHandle, response, false );

				// ping�R���[�`���𑖂点��B
				using namespace Node::Action;
				auto act = repeat_forever::create( sequence::create( delay::create( 1.5F ), call_func::create( 
					[networkHandle = chunk.networkHandle, this]
				{
					auto p = new Packet::Event::cEvePing( );
					p->time = mServerTime;
					send( networkHandle, p );
				} ) ) );
				act->set_tag( inserted.first->second.connection.id );
				mRoot->run_action( act );
			}
		}
		if ( itr != mHolder.end( ) )
		{
			// �ʏ�̃p�P�b�g�������Ă����ꍇ�B
			itr->second.manager.onReceive( chunk );
		}
		else
		{
			// �ڑ����Ȃ��Ńp�P�b�g�𑗂��Ă����ꍇ�B

			// nothing
		}
    }

    ping( );
}
void cUDPServerManager::sendDataBufferAdd( cNetworkHandle const & networkHandle, cPacketBuffer const & packetBuffer, bool reliable )
{
    auto itr = mHolder.find( networkHandle );
    if ( itr == mHolder.end( ) ) return;

    auto& buf = itr->second.connection.buffer;

	// �p�P�b�g���傫���Ȃ肻���Ȃ��ɑ����Ă��܂��܂��B
	if ( 1024 < buf.size( ) )
	{
		mSocket.write( networkHandle, buf.size( ), buf.data( ) );
		buf.clear( );
		buf.shrink_to_fit( );
	}

	ubyte2 const& byte = packetBuffer.transferredBytes;
	cBuffer const& buffer = packetBuffer.buffer;

	if ( reliable )
	{
		std::vector<char> buf;
		buf.resize( buf.size( ) + byte );
		memcpy( buf.data( ) + buf.size( ) - byte, &buffer, byte );
		itr->second.connection.reliableManager.append( std::move( buf ) );
	}
	else
	{
		buf.resize( buf.size( ) + byte );
		memcpy( buf.data( ) + buf.size( ) - byte, &buffer, byte );
	}
}
void cUDPServerManager::ping( )
{
	for ( auto& m : getUDPManager( ) )
    while ( auto p = m->ReqPing.get( ) )
    {
        auto itr = mHolder.find( p->networkHandle );
        if ( itr != mHolder.end( ) )
        {
            itr->second.connection.closeSecond = cinder::app::getElapsedSeconds( ) + PING_HOLD_SECOND;
        }
    }

    for ( auto itr = mHolder.begin( ); itr != mHolder.end( ); )
    {
        // ���[�J���̏ꍇ�̓J�E���g�_�E�������܂���B
        if ( itr->first.ipAddress != Network::getLocalIpAddressHost( ) )
        {
            if ( itr->second.connection.closeSecond < cinder::app::getElapsedSeconds( ) )
            {
                mRoot->remove_action_by_tag( itr->second.connection.id );
				mHolder.erase( itr++ );
                continue;
            }
        }
        ++itr;
    }
}
}
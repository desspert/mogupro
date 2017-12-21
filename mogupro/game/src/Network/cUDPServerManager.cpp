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
	mInfo.clear( );
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
    auto itr = mInfo.find( handle );
    if ( itr != mInfo.end( ) )
    {
        return itr->second.id;
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
	for ( auto& m : mPacket )
	{
		mans.push_back( &m.second );
	}
	return mans;
}
void cUDPServerManager::updateSend( )
{
    // ���M������̂�����΃o�b�t�@�[������o���đ���B
    for ( auto& holder : mInfo )
    {
		auto& handle = holder.first;
		auto& buf = holder.second.buffer;

		// �����C�A�u���ȃf�[�^���l�߂܂��B
		auto reliableData = holder.second.reliableManager.update( );
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
        if ( mPacket[chunk.networkHandle].isConnectPacket( chunk ) ||
            ( mPacket.find( chunk.networkHandle ) != mPacket.end( ) ) )
        {
			mPacket[chunk.networkHandle].onReceive( chunk );
        }
        else
        {
            // �R�l�N�V�������m�����Ȃ��܂ܑ��M���Ă����ꍇ�B
        }
    }

    connection( );
    ping( );
}
void cUDPServerManager::sendDataBufferAdd( cNetworkHandle const & networkHandle, cPacketBuffer const & packetBuffer, bool reliable )
{
    auto itr = mInfo.find( networkHandle );
    if ( itr == mInfo.end( ) ) return;

    auto& buf = itr->second.buffer;

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
		itr->second.reliableManager.append( std::move( buf ) );
	}
	else
	{
		buf.resize( buf.size( ) + byte );
		memcpy( buf.data( ) + buf.size( ) - byte, &buffer, byte );
	}
}
void cUDPServerManager::connection( )
{
	for( auto& m : getUDPManager( ) )
    while ( auto p = m->ReqConnect.get( ) )
    {
        if ( !mIsAccept ) continue;

        cinder::app::console( ) << p->mNetworkHandle.ipAddress << ":" << p->mNetworkHandle.port << "��";
        cinder::app::console( ) << "cUDPServerManager: " << "connecting..." << (int)mIdCount << std::endl;

		auto itr = mInfo.insert( std::make_pair( p->mNetworkHandle, mIdCount ) );
		mPacket.insert( std::make_pair( p->mNetworkHandle, std::move( cUDPManager( ) ) ) );
        if ( itr.second )
        {
            cinder::app::console( ) << p->mNetworkHandle.ipAddress << ":" << p->mNetworkHandle.port << "��";
            cinder::app::console( ) << "cUDPServerManager: " << "connect success!! " << (int)mIdCount << std::endl;

            mIdCount += 1;

			auto response = new Packet::Response::cResConnect( );
			response->time = mServerTime;

            send( p->mNetworkHandle, response, false );

			// ping�R���[�`���𑖂点��B
            using namespace Node::Action;
            auto act = repeat_forever::create( sequence::create( delay::create( 1.5F ), call_func::create( [ networkHandle = p->mNetworkHandle, this ]
            {
				auto p = new Packet::Event::cEvePing( );
			    p->time = mServerTime;
                send( networkHandle, p );
                cinder::app::console( ) << "cUDPServerManager: " << "ping to " << (int)getPlayerId( networkHandle ) << std::endl;
            } ) ) );
            act->set_tag( itr.first->second.id );
            mRoot->run_action( act );
        }
        else
        {
			// �Ăѐڑ����Ă����ꍇ�B

			// �ēo�^
			mInfo.erase( p->mNetworkHandle );
			mInfo.insert( std::make_pair( p->mNetworkHandle, mIdCount ) );
			mPacket.erase( p->mNetworkHandle );
			mPacket.insert( std::make_pair( p->mNetworkHandle, std::move( cUDPManager( ) ) ) );

            cinder::app::console( ) << p->mNetworkHandle.ipAddress << ":" << p->mNetworkHandle.port << "��";
            cinder::app::console( ) << "cUDPServerManager: " << "reconnect success!! " << (int)itr.first->second.id << std::endl;

			auto response = new Packet::Response::cResConnect( );
			response->time = mServerTime;

			send( p->mNetworkHandle, response, false );

			// ping�R���[�`���𑖂点��B
			mRoot->remove_action_by_tag( itr.first->second.id );
			using namespace Node::Action;
			auto act = repeat_forever::create( sequence::create( delay::create( 1.5F ), call_func::create( [networkHandle = p->mNetworkHandle, this]
			{
				send( networkHandle, new Packet::Event::cEvePing( ) );
			cinder::app::console( ) << "cUDPServerManager: " << "ping to " << (int)getPlayerId( networkHandle ) << std::endl;
			} ) ) );
			act->set_tag( itr.first->second.id );
			mRoot->run_action( act );
        }
    }
}
void cUDPServerManager::ping( )
{
	for ( auto& m : getUDPManager( ) )
    while ( auto p = m->ReqPing.get( ) )
    {
        auto itr = mInfo.find( p->networkHandle );
        if ( itr != mInfo.end( ) )
        {
            itr->second.closeSecond = cinder::app::getElapsedSeconds( ) + PING_HOLD_SECOND;
        }
    }

    for ( auto itr = mInfo.begin( ); itr != mInfo.end( ); )
    {
        // ���[�J���̏ꍇ�̓J�E���g�_�E�������܂���B
        if ( itr->first.ipAddress != Network::getLocalIpAddressHost( ) )
        {
            if ( itr->second.closeSecond < cinder::app::getElapsedSeconds( ) )
            {
                cinder::app::console( ) << itr->first.ipAddress << ":" << itr->first.port << "��";
                cinder::app::console( ) << "cUDPServerManager: " << "disconnect" << itr->second.id << std::endl;
                mRoot->remove_action_by_tag( itr->second.id );
				mPacket.erase( itr->first );
				mInfo.erase( itr++ );
                continue;
            }
        }
        ++itr;
    }
}
}
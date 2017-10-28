#include <Network/cUDP.h>
#include <Utility/cScopedMutex.h>
#include <boost/lexical_cast.hpp>
#include <Utility/MessageBox.h>
using udp = boost::asio::ip::udp;
namespace Network
{
cUDP::cUDP( )
    : mUdpSocket( mIoService )
{
    mRemoteBuffer.fill( 0 );
}
void cUDP::write( cNetworkHandle const& networkHandle, size_t sendDataByteNumber, char const * sendData )
{
    try
    {
        udp::resolver resolver( mIoService );
        udp::resolver::query query( udp::v4( ),
                                    networkHandle.ipAddress,
                                    boost::lexical_cast<std::string>( networkHandle.port ) );
        mUdpSocket.send_to( boost::asio::buffer( sendData, sendDataByteNumber ),
                            resolver.resolve( query )->endpoint( ) );
    }
    catch ( boost::system::error_code& e )
    {
        // ���M�ł��Ȃ����ɌĂ΂�܂��B
        // �l�b�g���[�N�f�o�C�X���������ɂȂ��Ă���Ƃ���A
        // �l�b�g���[�N�ɂȂ����Ă��Ȃ��Ƃ��ɌĂ΂�܂��B
        Utility::MessageBoxOk( e.message( ), [ ] { } );
    }
}
void cUDP::close( )
{
    mIsPause = true;
    mIoService.stop( );
    mUdpSocket.close( );
    if ( mUpdateIoService.joinable( ) )
    {
        mUpdateIoService.join( );
    }
}
void cUDP::open( )
{
    open( 0 );
}
void cUDP::open( int port )
{
    mIsPause = false;
    if ( !mUdpSocket.is_open( ) )
    {
        boost::system::error_code e;
        mUdpSocket.open( udp::v4( ), e );
        if ( e )
        {
            // open�ł��Ȃ�������
            Utility::MessageBoxOk( e.message( ), [ ] { } );
        }
        mUdpSocket.bind( udp::endpoint( udp::v4( ), port ), e );
        if ( e )
        {
            // bind�ł��Ȃ�������
            Utility::MessageBoxOk( e.message( ), [ ] { } );
        }
    }
    mUpdateIoService = std::thread( [ this ]
    {
        while ( !mIsPause )
        {
            receive( );
            mIoService.run( );
            mIoService.reset( );
        }
    } );
}
void cUDP::clearChunk( )
{
    Utility::cScopedMutex m( mMutex );
    mChacheEndpoints.clear( );
    mChacheEndpoints.shrink_to_fit( );
}
bool cUDP::emptyChunk( )
{
    Utility::cScopedMutex m( mMutex );
    return mChacheEndpoints.empty( );
}
cPacketChunk cUDP::popChunk( )
{
    Utility::cScopedMutex m( mMutex );
    auto front = mChacheEndpoints.front( );
    mChacheEndpoints.pop_front( );
    return front;
}
void cUDP::receive( )
{
    mUdpSocket.async_receive_from( boost::asio::buffer( mRemoteBuffer ),
                                   mRemoteEndpoint,
                                   [ this ] ( const boost::system::error_code& e, size_t transferredBytes )
    {
        if ( e )
        {
            // ��M�ł��Ȃ��������ɌĂ΂�܂��B
            // ���p�P�b�g���X�Ƃ��̔��f�͂����ł͏o���܂���B
            // �Ƃ������������Ă΂ꂽ�Ƃ�����������Ƃ��Ȃ��ł��B
            Utility::MessageBoxOk( e.message( ), [ ] { } );
        }
        else
        {
            Utility::cScopedMutex m( mMutex );
            mChacheEndpoints.emplace_back( mRemoteEndpoint.address( ).to_string( ), mRemoteEndpoint.port( ), transferredBytes, mRemoteBuffer );
            std::fill_n( mRemoteBuffer.begin( ), transferredBytes, 0 );
        }
    } );
}
}
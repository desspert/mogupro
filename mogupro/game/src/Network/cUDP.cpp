#include <Network/cUDP.h>
#include <Utility/cScopedMutex.h>
#include <boost/lexical_cast.hpp>
using udp = boost::asio::ip::udp;
namespace Network
{
cUDP::cUDP( )
    : mUdpSocket( mIoService )
{
    mRemoteBuffer.fill( 0 );
}
void cUDP::write( std::string ipaddress, int port, size_t sendDataByteNumber, char const * sendData )
{
    try
    {
        udp::resolver resolver( mIoService );
        udp::resolver::query query( udp::v4( ),
                                    ipaddress,
                                    boost::lexical_cast<std::string>( port ) );
        mUdpSocket.send_to( boost::asio::buffer( sendData, sendDataByteNumber ),
                            resolver.resolve( query )->endpoint( ) );
    }
    catch ( boost::system::error_code& e )
    {
        // ���M�ł��Ȃ����ɌĂ΂�܂��B
        // �l�b�g���[�N�f�o�C�X���������ɂȂ��Ă���Ƃ���A
        // �l�b�g���[�N�ɂȂ����Ă��Ȃ��Ƃ��ɌĂ΂�܂��B
    }
}
void cUDP::close( )
{
    mIsPause = true;
    mIoService.stop( );
    mUpdateIoService.join( );
    mUdpSocket.close( );
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
        }
        mUdpSocket.bind( udp::endpoint( udp::v4( ), port ), e );
        if ( e )
        {
            // bind�ł��Ȃ�������
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
void cUDP::clearRemoteBuffer( )
{
    Utility::cScopedMutex m( mMutex );
    mRemoteBuffers.clear( );
    mRemoteBuffers.shrink_to_fit( );
}
bool cUDP::emptyRemoteBuffer( )
{
    Utility::cScopedMutex m( mMutex );
    return mRemoteBuffers.empty( );
}
cPacketRaw&& cUDP::popRemoteBuffer( )
{
    Utility::cScopedMutex m( mMutex );
    auto front = mRemoteBuffers.front( );
    mRemoteBuffers.pop_front( );
    return std::move( front );
}
void cUDP::receive( )
{
    mUdpSocket.async_receive_from( boost::asio::buffer( mRemoteBuffer ),
                                   mRemoteEndpoint,
                                   [ this ] ( const boost::system::error_code& e, size_t bytes_transferred )
    {
        if ( e )
        {
            // ��M�ł��Ȃ��������ɌĂ΂�܂��B
            // ���p�P�b�g���X�Ƃ��̔��f�͂����ł͏o���܂���B
            // �Ƃ������������Ă΂ꂽ�Ƃ�����������Ƃ��Ȃ��ł��B
        }
        else
        {
            Utility::cScopedMutex m( mMutex );
            mRemoteEndpoints.emplace_back( mRemoteEndpoint );
            mRemoteBuffers.emplace_back( bytes_transferred, mRemoteBuffer );
            std::fill_n( mRemoteBuffer.begin( ), bytes_transferred, 0 );
        }
    } );
}
}
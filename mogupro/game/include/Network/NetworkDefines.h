#pragma once
#include <array>
#include <tuple>
namespace Network
{
static_assert( sizeof( unsigned short ) == 2, "<unsinged short>��\"2�o�C�g\"���Ⴀ��܂���B" );
static_assert( sizeof( unsigned int ) == 4, "<unsinged int>��\"4�o�C�g\"���Ⴀ��܂���B" );
using ubyte1 = unsigned char;
using ubyte2 = unsigned short;
using ubyte4 = unsigned int;
static_assert( sizeof( short ) == 2, "<short>��\"2�o�C�g\"���Ⴀ��܂���B" );
static_assert( sizeof( int ) == 4, "<int>��\"4�o�C�g\"���Ⴀ��܂���B" );
using byte1 = char;
using byte2 = short;
using byte4 = int;
constexpr ubyte2 PACKET_MAX_BYTE = 4096U;
using cBuffer = std::array<char, PACKET_MAX_BYTE>;
constexpr float HOLD_SECOND = 60.0F;
constexpr ubyte1 RELIABLE_COUNT = 7U; // �M������ۏ؂��邽�߂̉񐔁B
class cPacketBuffer
{
public:
    cPacketBuffer( ) = default;
    cPacketBuffer( ubyte2 transferredBytes, cBuffer const& buffer )
        : transferredBytes( transferredBytes )
        , buffer( buffer )
    {

    }
    ubyte2 transferredBytes;
    cBuffer buffer;
};
class cNetworkHandle
{
public:
    cNetworkHandle( )
        : ipAddress( "" )
        , port( 0 )
    {

    }
    cNetworkHandle( std::string ipAddress, int port )
        : ipAddress( ipAddress )
        , port( port )
    {

    }
    cNetworkHandle& operator=( cNetworkHandle const& handle ) noexcept
    {
        const_cast<std::string&>( this->ipAddress ) = handle.ipAddress;
        const_cast<int&>( this->port ) = handle.port;
        return *this;
    }
    operator bool( ) const noexcept
    {
        return ( !this->ipAddress.empty( ) ) && ( this->port != 0 );
    }
    bool operator==( cNetworkHandle const& other ) const noexcept
    {
        return other.ipAddress == this->ipAddress;
    }
    bool operator!=( cNetworkHandle const& other ) const noexcept
    {
        return !( other.ipAddress == this->ipAddress );
    }
    bool operator<( cNetworkHandle const& other ) const noexcept
    {
        return other.ipAddress < this->ipAddress;
    }
    std::string const ipAddress;
    int const port;
};
class cPacketChunk
{
public:
    cPacketChunk( ) = default;
    cPacketChunk( cNetworkHandle networkHandle, cPacketBuffer const& packetBuffer )
        : networkHandle( networkHandle )
        , packetBuffer( packetBuffer )
    {

    }
    cPacketChunk( std::string ipAddress, int port, ubyte2 transferredBytes, cBuffer const& buffer )
        : networkHandle( ipAddress, port )
        , packetBuffer( transferredBytes, buffer )
    {

    }
    cNetworkHandle networkHandle;
    cPacketBuffer packetBuffer;
};
#pragma pack()
}
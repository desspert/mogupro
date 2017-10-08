#pragma once
#include <Utility/cSingletonAble.h>
#include <string>
#include <array>
#include <thread>
#include <Utility/cRecursionUsableMutex.h>
#include <Network/NetworkDefines.h>
#include <boost/asio.hpp>
#include <memory>
#include <deque>
namespace Network
{
class cUDP
{
public:
    cUDP( );
    void write( std::string ipaddress, int port, size_t sendDataByteNumber, char const * sendData );
    void close( );
    void open( );
    void open( int port );
    // socket�ɂ���f�[�^��S�č폜���܂��B
    void clearRemoteBuffer( );
    // socket�Ƀf�[�^�����邩�ǂ����B
    bool emptyRemoteBuffer( );
    // �Â��f�[�^����Ԃ��܂��B
    // ���̎��Ɉꏏ�ɂ��̃f�[�^�͍폜����܂��B
    cPacketRaw&& popRemoteBuffer( );
private:
    void receive( );
private:
    // ��M���͕ʃX���b�h�œ������܂��B
    bool mIsPause = false;
    std::thread mUpdateIoService;
    Utility::cRecursionUsableMutex mMutex;

    boost::asio::io_service mIoService;
    boost::asio::ip::udp::socket mUdpSocket;

    // �f�[�^�𑗂��ė��������ipaddress��port������܂��B
    boost::asio::ip::udp::endpoint mRemoteEndpoint;

    // �����Ă����f�[�^������܂��B
    // �����w��65536�ȏ�͑���Ȃ����ɂȂ��Ă���̂ł����ς��ɂȂ邱�Ƃ͂���܂���B
    cBuffer mRemoteBuffer;
    
    // ��M���Ă��������ipaddress��port�𗭂߂Ă����܂��B
    std::deque<boost::asio::ip::udp::endpoint> mRemoteEndpoints;
    // ��M�f�[�^�𗭂߂Ă����܂��B
    std::deque<cPacketRaw> mRemoteBuffers;
};
}
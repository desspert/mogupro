#pragma once
#include <Utility/cSingletonAble.h>
#include <string>
#include <array>
#include <thread>
#include <mutex>
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
	~cUDP( );
    void write( cNetworkHandle const& networkHandle, size_t sendDataByteNumber, char const * const sendData );
    void close( );
    void open( );
    void open( int port );
    // socket�ɂ���f�[�^��S�č폜���܂��B
    void clearChunk( );
    // socket�Ƀf�[�^�����邩�ǂ����B
    bool emptyChunk( );
    // �Â��f�[�^����Ԃ��܂��B
    // ���̎��Ɉꏏ�ɂ��̃f�[�^�͍폜����܂��B
    cPacketChunk popChunk( );
private:
    void receive( );

private:
    // ��M���͕ʃX���b�h�œ������܂��B
    bool mIsPause = false;
    std::thread mThreadIoService;

    boost::asio::io_service mIoService;
    boost::asio::ip::udp::socket mUdpSocket;

private:
    // ��M�f�[�^��Mutex�B
    std::mutex mDataMutex;

    // �f�[�^�𑗂��ė��������ipaddress��port������܂��B
    boost::asio::ip::udp::endpoint mRemoteEndpoint;

    // �����Ă����f�[�^������܂��B
    // �����w��65536�ȏ�͑���Ȃ����ɂȂ��Ă���̂ł����ς��ɂȂ邱�Ƃ͂���܂���B
    cBuffer mRemoteBuffer;
    
    // �����Ă����f�[�^��A�����ė�������̏���ۑ����Ă����܂��B
    std::deque<cPacketChunk> mCacheEndpoints;
};
}
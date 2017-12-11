#pragma once
#include <Network/NetworkDefines.h>
#include <Network/Packet/PacketId.h>
#include <tuple>
namespace Network
{
namespace Packet
{
#pragma pack(1)
struct PacketHeader
{
	enum State : ubyte1
	{
		NONE = 0,
		RELIABLE = 1 << 0,   // �M���������f�[�^
		ENCRYPTION = 1 << 1, // �Í����������f�[�^
	};
	State mState = State::NONE;

    // ���߃p�P�b�g�̔ԍ�������܂��B
    PacketId mPacketId = PacketId::INVALID_NUMBER;
    // ���邽�тɃV�[�P���X�ԍ��𑝂₵�Ă����܂��B
    // �Â��p�P�b�g�𗎂Ƃ�����A�p�P�b�g���X�̔���ȂǂɎg���܂��B
    ubyte4 mSequenceId = 0;
    // �y�C���[�h�Ƃ��ēn���T�C�Y���i�[���܂��B
    // ���̃N���X��A�p����̃T�C�Y���܂݂܂��B
    ubyte2 mPacketByte = 0;
};
#pragma pack()
template <class Ty, PacketId packetId>
class cPacketBase
{
public:
    virtual ~cPacketBase( ) {}
    void onReceive( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const packet )
    {
        // ��Ƀw�b�_�[��ǂݍ��ށB
        // �q���ɔj�󂳂ꂽ��ł�����Ȃ��̂ŁB
        memcpy( &mHeader, packet, sizeof( PacketHeader ) );

        // ���Ɏq���ɂ���Ă��炤�B
        packetImport( networkHandle, transferredBytes - sizeof( PacketHeader ), packet + sizeof( PacketHeader ) );
    }
    void createPacket( cPacketBuffer& packetBuffer, PacketHeader::State state )
    {
        ubyte2& packetByte = packetBuffer.transferredBytes;
        cBuffer& buffer = packetBuffer.buffer;

        // �q���̃p�P�b�g���ɋl�߂Ă��炤�B
        // �q���Ƀw�b�_�[�p�P�b�g���󂳂�ē�̃G���[���o�Ă����Ȃ̂ŁB
        char* childHeader = buffer.data( ) + sizeof( PacketHeader );
        ubyte2 childPacketByte = packetExport( childHeader );

        // �w�b�_�[�p�P�b�g��ǉ�����B
        PacketHeader header;
		header.mState = state;
        header.mPacketId = packetId;
        header.mSequenceId = ++sequenceCount;
        header.mPacketByte = childPacketByte + sizeof( PacketHeader );
        memcpy( buffer.data( ), &header, sizeof( PacketHeader ) );

        // �Ō��raw�f�[�^�̃T�C�Y����������B
        // �����65535���̂����g�����̂��Ƃ�����񂪂Ȃ��Ƒ��鎞�ɂ킩��Ȃ��Ȃ邩��B
        packetByte = header.mPacketByte;
    }
    //!@ LookMe : �p����Ŏ�M�����p�P�b�g�����Ƃɍ\���������Ă��������B
    // �w�b�_�[�f�[�^�͊܂܂�܂���B
    // packetByte���w�b�_�[���͊܂܂�܂���B
    // �����̊֐����Ă΂ꂽ�シ���Ɏ�M�p�P�b�g���폜����܂��B
    // �|�C���^��ۑ��Ƃ��킯�̂킩��񂱂Ƃ����Ȃ��悤�ɁB
    // �����ƃR�s�[������Ă��������B
    virtual void packetImport( cNetworkHandle networkHandle, ubyte2 transferredBytes, char const* const data ) = 0;
    //!@ LookMe : �p����ő��M����p�P�b�g���\�����Ă��������B
    // �w�b�_�[�f�[�^�͊܂܂Ȃ��đ��v�ł��B
    // �Ԃ�l�͌p����̑��肽���p�P�b�g�T�C�Y�B
    virtual ubyte2 packetExport( char* const packet ) = 0;
    ubyte4 getSequenceId( )
    {
        return mHeader.mSequenceId;
    }
    PacketId getPacketId( )
    {
        return mHeader.mPacketId;
    }
    ubyte2 getPacketByte( )
    {
        return mHeader.mPacketByte;
    }
protected:
    // �V�[�P���X�ԍ���ۑ����܂��B
    // �p����̃N���X���Ƃɐ�������܂��B
    static ubyte4 sequenceCount;

    PacketHeader mHeader;
};
template <class Ty, PacketId packetId>
ubyte4 cPacketBase<Ty, packetId>::sequenceCount = 0;
}
}
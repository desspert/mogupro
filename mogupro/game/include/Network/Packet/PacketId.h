#pragma once
#include <Network/NetworkDefines.h>
namespace Network
{
namespace Packet
{
enum class PacketId : ubyte1
{
    // �������p�ł��B
    // 0�Ŗ��߂Ă���̂ŁA�Ԉ���ČĂ΂�Ȃ��悤�ɕی����|���Ă����܂��B
    INVALID_NUMBER = 0U,

    //=========================================================//
    //                       Deliver                           //
    //=========================================================//
    // �N���C�A���g�ڐ��ŏ�����Ă��܂��B

    // <std::string>�𑗂�܂��B
    DLI_STRING,
    // �ڑ����ێ�����p�P�b�g�𑗂�܂��B
    DLI_PING,
    // ���@�̃v���C���[�����T�[�o�[�ɑ���܂��B
    DLI_PLAYER,
    // �u���b�N��j�󂵂��ƒm�点�܂��B
    DLI_BREAK_BLOCKS,

    //=========================================================//
    //                         Event                           //
    //=========================================================//
    // �T�[�o�[�ڐ��ŏ�����Ă��܂��B

    // <std::string>�𑗂�܂��B
    EVE_STRING,
    // �ڑ����ێ�����p�P�b�g�𑗂�܂��B
    EVE_PING,
    // ���̃v���C���[�̈ʒu���𑗂�܂��B
    EVE_PLAYERS,
    // ���̃v���C���[���t�B�[���h�̃W�F�����̂����ƒʒm���܂��B
    EVE_GET_JEM_PLAYER,
    // �@��@���t�B�[���h�̃W�F�����̂����ƒʒm���܂��B
    EVE_GET_JEM_QUARRY,
    // ���̃v���C���[��@��@���t�B�[���h�̃u���b�N��j�󂵂��ƒʒm���܂��B
    EVE_BREAK_BLOCKS,
    // ���̃v���C���[���@��@���t�B�[���h�ɐݒu�����ƒʒm���܂��B
    EVE_SET_QUARRY,
    // ���̃v���C���[�ɒD��ꂽ�ƒʒm���܂��B
    // �����̏u�ԂɃv���C���[�̓X�e�[�^�X��ς��Ă��������B
    EVE_PLAYER_ROB_JEM,
    // ���̃v���C���[�ɓ|���ꂽ�ƒʒm���܂��B
    // �����̏u�ԂɃv���C���[�̓X�e�[�^�X��ς��Ă��������B
    EVE_PLAYER_DEATH,
    //Member���ǂ��ɏ������Ă��邩�̑��M
    EVE_TEAM_MEMBER,
    // �v���C���[�̃��X�|�[���ʒu��ʒm���܂��B
    EVE_PLAYERS_RESPAWN,
    //=========================================================//
    //                        Request                          //
    //=========================================================//
    // �N���C�A���g�ڐ��ŏ�����Ă��܂��B

    // <std::string>�𑗂�܂��B
    REQ_STRING,
    // �T�[�o�[�ɐڑ���\�����݂܂��B
    REQ_CONNECT,
    // ���[���h�𐶐����邽�߂̃V�[�h�l��v�����܂��B
    REQ_GET_JEM_SEED,
    // ���ݎ����Ă���W�F���̐����T�[�o�[������񂹂܂��B
    REQ_GET_JEM_POINT,
    // �v���C���[���W�F�����擾�������Ƃ�m�点�܂��B
    // �����̃^�C�~���O�ł͎擾�ł��܂���B�T�[�o�[����̃��X�|���X��҂��Ă��������B
    REQ_CHECK_GET_JEM_PLAYER,
    // �@��@���W�F�����擾�������Ƃ�m�点�܂��B
    // �����̃^�C�~���O�ł͎擾�ł��܂���B�T�[�o�[����̃��X�|���X��҂��Ă��������B
    REQ_CHECK_GET_JEM_QUARRY,
    // �v���C���[�����̃v���C���[�̃W�F����D�������Ƃ�ʒm���܂��B
    // �����̃^�C�~���O�ł͒D��ł��܂���B�T�[�o�[����̃��X�|���X��҂��Ă��������B
    REQ_CHECK_PLAYER_ROB_JEM,
    // �@��@��ݒu�����ƒm�点�܂��B
    // �����̃^�C�~���O�ł͐ݒu�ł��܂���B�T�[�o�[����̃��X�|���X��҂��Ă��������B
    REQ_CHECK_SET_QUARRY,
    // ���̃v���C���[��|���������T�[�o�[�ɑ���B
    // �����̃^�C�~���O�ł͓|���܂���B�T�[�o�[����̃��X�|���X��҂��Ă��������B
    REQ_CHECK_PLAYER_DEATH,
	//Matching���ɃN���C�A���g�����������\��
	REQ_MAKE_ROOM,
	//Matching���ɃN���C�A���g�������ɓ���\��
	REQ_IN_ROOM,
	//Matching���ɂǂ����̃`�[���ɓ���̂��̐\��
	REQ_WANT_TEAM_IN,
	//Master����Q�[�����J�n�ł��邩�ǂ������m�F���邽�߂ɑ��M
	//!@ LookMe : ��M����Server����S���ɑ���
	REQ_CHECK_BEGIN_GAME,
	//���������[���ɂ��邱�Ƃ̑��M
	REQ_CHECK_MEMBER,
	//GameMain��Setup���I��������Ƃ̒ʒm
	REQ_END_GAMEMAIN_SETUP,
    //=========================================================//
    //                        Response                         //
    //=========================================================//
    // �T�[�o�[�ڐ��ŏ�����Ă��܂��B

    // <std::string>�𑗂�܂��B
    RES_STRING,
    // �N���C�A���g�̐ڑ��v���ɓ����܂��B
    RES_CONNECT,
    // ���[���h�𐶐����邽�߂̃V�[�h�l��n���܂��B
    RES_GET_JEM_SEED,
    // �v���C���[�������Ă���W�F���̐���n���܂��B
    RES_GET_JEM_POINT,
    // �v���C���[���W�F���̎擾�ɐ������������s�������A�ɂ��Ēʒm���܂��B
    RES_CHECK_GET_JEM_PLAYER,
    // �@��@���W�F���̎擾�ɐ������������s�������A�ɂ��Ēʒm���܂��B
    RES_CHECK_GET_JEM_QUARRY,
    // �W�F���̒D��ɐ������������s�������A�ɂ��Ēʒm���܂��B
    RES_CHECK_PLAYER_ROB_JEM,
    // �@��@�̐ݒu�ɐ������������s�������A�ɂ��Ēʒm���܂��B
    RES_CHECK_SET_QUARRY,
    // ���̃v���C���[�̃L���ɐ������������s�������A�ɂ��Ēʒm���܂��B
    RES_CHECK_PLAYER_DEATH,
	//Matching���ɃN���C�A���g�����������\���������A��ꂽ���ǂ���
	RES_MAKE_ROOM,
	//Matching���ɃN���C�A���g�������ɓ���\���������A���ꂽ���ǂ���
	RES_IN_ROOM,
	//Matching���ɂǂ����̃`�[���ɓ���̂��̐\���������A���ꂽ���ǂ���
	RES_WANT_TEAM_IN,
    //�Q�[�����J�n�ł��邩�ǂ���
	RES_CHECK_BEGIN_GAME,
	//���������[���ɂ��邱�Ƃ̑��M���Ă��炤
	RES_CHECK_MEMBER,
	//GameMain��Setup���I��������Ƃ̒ʒm���󂯂���ɑ΂�ServerAdapter��Update�J�n��ʒm���邩���p
	RES_END_GAMEMAIN_SETUP,
};
}
}
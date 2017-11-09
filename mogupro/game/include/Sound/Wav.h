#pragma once
#define NOMINMAX
#pragma comment(lib,"OpenAL32.lib")
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//Wav Header �̏ڍ�
//0 ~ 3  : "RIFF" ����
//4 ~ 7  : "���t�@�C���T�C�Y -8 (byte)"
//8 ~ 11 : "WAVE" ����
#define WAV_HEADER_SIZE (12)
//Wav Chunk �̏ڍ�
//0  ~ 3  : "fmt " �����@
//4  ~ 7  : �t�H�[�}�b�g�T�C�Y�@�f�t�H���g�l16 (���̂���S����16byte)
//8  ~ 9  : �t�H�[�}�b�g�R�[�h�@�񈳏k�̂o�b�l�t�H�[�}�b�g��1
//10 ~ 11 : �`�����l�����@���m������1�A�X�e���I��2
//12 ~ 15 : �T���v�����O���[�g�@44.1kHz�̏ꍇ�Ȃ�44100
//16 ~ 19 : �o�C�g�^�b�@�P�b�Ԃ̘^���ɕK�v�ȃo�C�g��
//20 ~ 21 : �u���b�N���E�@�X�e���I16bit�Ȃ�A16bit*2 = 32bit = 4byte
//22 ~ 23 : �r�b�g�^�T���v���@�P�T���v���ɕK�v�ȃr�b�g��
#define WAV_CHUNK_SIZE  (24)

//! @fn    Wav
//! @brief WavFile
//! @note 
//!        Wav�Đ������邽�߂�Class�ł��B
//!        WavClass�݂̂ōĐ��͂ł��܂���B
//! @date 2017-11-06
//! @author Taka Nomoto

namespace Sound
{
	class Wav
	{
	public:
		bool read(const std::string& file);
		unsigned int getValue(const char* p, const unsigned int num);
		//!@TODO : 2byte��Tag�ɑΉ����Ă��Ȃ�
		bool searchChunk(std::ifstream& fstr, const char* chunk);
		//�`�����l������Ԃ�
		unsigned int  channel() const { return chunkInfo.ch; }
		//�f�[�^���X�e���I�Ȃ�true��Ԃ�
		bool isStereo() const { return chunkInfo.ch == 2; }
		// �T���v�����O���[�g��Ԃ�
		unsigned int  sampleRate() const { return chunkInfo.sampleRate; }
		// �f�[�^�T�C�Y(�o�C�g��)��Ԃ�
		unsigned int  size() const { return chunkInfo.size; }
		// �Đ�����(�b)��Ԃ�
		float totalTime() const { return time; }
		// �g�`�f�[�^��Ԃ�
		const char* data() const { return &wavData[0]; }

		struct Chunk
		{
			unsigned int id;
			unsigned int ch;
			unsigned int sampleRate;
			unsigned int bit;
			unsigned int size;
		};

		std::vector<char> wavData;
		Chunk chunkInfo;
		float time;
	};
}

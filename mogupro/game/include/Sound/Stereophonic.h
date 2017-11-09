#pragma once
#include <Sound/Wav.h>
#include <Utility/cSingletonAble.h>
#include <memory>
#include <cinder/Vector.h>
#include <vector>
#include <Utility/cUserPointer.hpp>
//! @fn    Stereophonic
//! @brief ���̉������Đ�����Class�ł�
//! @note  �g�����ɂ���
//!
//!                1.read 
//!                2.bind 
//!                3.setListenerPos
//!                4.setListenerDirection
//!                5.setSourcePos
//!                6.play�Ƃ�
//!
//! @date 2017-11-06
//! @author Taka Nomoto

namespace Sound
{
	class Stereophonic
	{
	public:
		Stereophonic() {}
		Stereophonic(const std::string& file, std::shared_ptr<ci::vec3> listenerPos,
			std::shared_ptr<ci::vec3> listenerDir, std::shared_ptr<ci::vec3> sourcePos)
		{
			read(file);
			//bindWav();
			bind();
			setListenerPos(listenerPos);
			setListenerDirection(listenerDir);
			setSourcePos(sourcePos);
			play();
		}

		//Assets��Path�w�肵�Ă�������
		//Wav�ǂݍ���
		void read(const std::string& file);
		//wav��Data��vector<ALshort> data�ɕۑ����܂�
		void bindWav();
		//���C���X���b�h�Ńf�[�^��Bind���s��
		void bind();
		//�����ʒu�̐ݒ�
		void setListenerPos(std::shared_ptr<ci::vec3>);
		void setListenerPos();
		//���������̐ݒ� (up�x�N�g����vec3(0,1,0))
		void setListenerDirection(std::shared_ptr<ci::vec3>);
		void setListenerDirection();
		//�����̈ʒu�̐ݒ�
		void setSourcePos(std::shared_ptr<ci::vec3>);
		void setSourcePos();
		void play();

		void stop();

		void pause();

		void gain(const float value);

		void pitch(const float value);

		void looping(const bool value);

		bool isPlaying();

		float currentTime();

		void update();

		void clean();

		Wav wav;
		std::vector<ALshort> data;
	private:
		Utility::softptr<ci::vec3> listenerPosition;
		Utility::softptr<ci::vec3> listenerDirection;
		Utility::softptr<ci::vec3> sourcePosition;

		ALuint bufferId;
		ALuint sourceId;
	};

	// �f�B���C
	// input_samples ���H����g�`�f�[�^
	// attenuation   ������(0.0 ~ 1.0)
	// time          �x������(�b)
	// repeat        �J��Ԃ���
	void delay(Stereophonic& stereophonic, float attenuation, float time, int repeat);


	//! @fn    StereophonicManager
	//! @brief ���̉����Đ����܂Ƃ߂�Class�ł�
	//! @note  �g�����ɂ���
	//!
	//!                1.read 
	//!                2.bind 
	//!                3.setListenerPos
	//!                4.setListenerDirection
	//!                5.setSourcePos
	//!                6.play�Ƃ�
	//!
	//! @date 2017-11-09
	//! @author Taka Nomoto
	class StereophonicManager : public Utility::cSingletonAble<StereophonicManager>
	{
	public:
		void open();

		void close();

		void add(const std::string& file, std::shared_ptr<ci::vec3> listenerPos,
			std::shared_ptr<ci::vec3> listenerDir, std::shared_ptr<ci::vec3> sourcePos)
		{
			stereophonicList.push_back(Stereophonic(file, listenerPos,listenerDir,sourcePos));
		}

		void update()
		{
			for (int i = 0; i < stereophonicList.size(); ++i)
			{
				stereophonicList[i].update();
			}
		}

	private:
		ALCdevice*  device;
		ALCcontext* context;
		std::vector<Stereophonic> stereophonicList;
	};
}
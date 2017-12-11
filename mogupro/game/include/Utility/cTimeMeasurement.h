#pragma once
#include <Utility/cSingletonAble.h>
#include <iostream>
#include <chrono>

//! @file TimeMeasurement
//! @brief �Q�[�����̎��ԊǗ�������N���X�ł�
//! @note 
//!      �t���[�����ɃY���Ȃ���������������get()�������Ă�������
//!      �Q�[���J�n����̎��Ԃ��~�����ꍇ�́AtotalTime()�����Ă�������
//! @date 2017-10-12
//! @author Taka Nomoto

class cTimeMeasurement : public Utility::cSingletonAble<cTimeMeasurement>
{
public:

	cTimeMeasurement();

	//_totalTime��_deltaTime����
	//update�ŕK���ǂ�ł�������
	void make();

	//_deltaTime�擾
	//_deltaTime => 1Frame�Ɋ|����������
	float deltaTime();

	//exe�N������̑�������
	float totalTime();

private:

	//�R�s�[�R���X�g���N�^�֎~
	cTimeMeasurement(const cTimeMeasurement&) = delete;
	cTimeMeasurement& operater(const cTimeMeasurement&) = delete;

	std::chrono::steady_clock::time_point mNow;

	std::chrono::steady_clock::time_point mPrev;

	float mDeltaTime;

	float mTotalTime;
};
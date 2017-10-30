#pragma once

//! @file cSceneBase
//! @brief �S�Ă�Scene�Ɍp���������ՃN���X�ł�
//! @note
//!       Scene�؂�ւ���_isEnd �Ŕ��f���܂�
//! @date 2017-10-12
//! @author Taka Nomoto

class cSceneBase
{
public:
	//������
	virtual void setup() = 0;
	//Scene�̏I�����̃������폜�Ƃ�
	virtual void shutDown() = 0;

	virtual void update(float deltaTime) = 0;
	
	virtual void draw() = 0;

	virtual void drawFBO() = 0;

	virtual void draw2D() = 0;
	//�T�C�Y�ύX���ɌĂт����Ƃ�
	virtual void resize() = 0;
	//!@ Look Me : Scene�؂�ւ�����true�ɂ��Ă�������
	//������Scene�؂�ւ����̃o�O�o����悤�ŏ������Ă܂�
	bool isEnd() { return mIsEnd; }
protected:

	bool mIsEnd;
};
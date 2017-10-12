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
	virtual void update() = 0;
	//3D�`��
	virtual void draw() = 0;
	//���邩�킩��񂩂�ꉞ
	virtual void draw2D() = 0;
	//�T�C�Y�ύX���ɌĂт����Ƃ�
	virtual void resize() = 0;

	bool isEnd() { return mIsEnd; }

protected:

	bool mIsEnd;
};
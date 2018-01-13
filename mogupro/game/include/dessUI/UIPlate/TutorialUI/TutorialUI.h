#pragma once
#include "../UIPlate.h"

class TutorialUI : public UIPlate
{ 
private:
	enum TUTORIAL {
		NONE = 0,
		MOVE = 1,
		EYE = 2,
		DRILL = 3
	};
	TUTORIAL now_scene;
	std::unordered_map<std::string, ci::gl::Texture2dRef> font_texture;
	//�i�s�t���O
	std::unordered_map<std::string, bool> turo_flags;
	int buf_scene;
public:
	TutorialUI(){
	}
	//�v���C���[������
	void playerInit();
	//�e�L�X�g������
	void textInit();
	//�ړ�
	void tutorialMoveSetup(const float& delta_time);
	void tutorialMoveUpdate(const float& delta_time);

	//���_
	void tutorialEyeSetup(const float& delta_time);
	void tutorialEyeUpdate(const float& delta_time);

	//�@��
	void tutorialDrillSetup(const float& delta_time);
	void tutorialDrillUpdate(const float& delta_time);


	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;

};

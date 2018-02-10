#pragma once
#include "../UIPlate.h"

class TutorialUI : public UIPlate
{ 
private:
	enum TUTORIAL {
		NONE = 0,
		MOVE = 1,
		EYE = 2,
		DRILL = 3,
		GEM = 4,
		ATTACK = 5,
		DELIVERY = 6,
		ITEM = 7,
		END = 8
	};
	TUTORIAL now_scene;
	std::unordered_map<std::string, ci::gl::Texture2dRef> font_texture;
	//�i�s�t���O
	std::unordered_map<std::string, bool> turo_flags;
	std::unordered_map<std::string, float> tuto_counts;
	int buf_scene;
	float cannon_far = 20.0f;
	float player_far = 5.0f;
	bool tutorial_stan;
	ci::vec2 camera_angle_buf = cinder::vec2(-M_PI/2, 0);
public:
	TutorialUI(){
	}
	bool getTutorialStan() { return tutorial_stan; }
	//�v���C���[������
	void playerInit();
	//�e�L�X�g������
	void textInit();
	//���փ{�^��
	void enableNextButton();
	void disableNextButton();
	void tutorialNumbers(int num);
	//�ړ�
	void tutorialMoveSetup(const float& delta_time);
	void tutorialMoveUpdate(const float& delta_time);

	//���_
	void tutorialEyeSetup(const float& delta_time);
	void tutorialEyeUpdate(const float& delta_time);

	//�@��
	void tutorialDrillSetup(const float& delta_time);
	void tutorialDrillUpdate(const float& delta_time);

	//�W�F��
	void tutorialGemSetup(const float& delta_time);
	void tutorialGemUpdate(const float& delta_time);

	//�U��
	void tutorialAttackSetup(const float& delta_time);
	void tutorialAttackUpdate(const float& delta_time);

	//�[�i
	void tutorialDeliverySetup(const float& delta_time);
	void tutorialDeliveryUpdate(const float& delta_time);

	//�A�C�e��
	void tutorialItemSetup(const float& delta_time);
	void tutorialItemUpdate(const float& delta_time);

	//�I��
	void tutorialEndSetup(const float& delta_time);
	void tutorialEndUpdate(const float& delta_time);

	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;

};

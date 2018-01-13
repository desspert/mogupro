#include "TutorialUI.h"
#include <Utility/cInput.h>
#include <Game/cPlayerManager.h>
#include <Game/Field/FieldData.h>
#include <CameraManager/cCameraManager.h>
void TutorialUI::setup(const dess::SceneName & name)
{
	now_scene = TUTORIAL::MOVE;
	buf_scene = static_cast<int>(TUTORIAL::NONE);
	UIPlate::setup(name);
	textInit();
}
//�v���C���[������
void TutorialUI::playerInit()
{
	Game::cPlayerManager::getInstance()->getActivePlayer()->settingPosition(ci::vec3(Game::Field::WORLD_SIZE.x / 2, Game::Field::WORLD_SIZE.y + 0.5f, 17.0F));
	Game::cPlayerManager::getInstance()->getActivePlayer()->move(ci::vec3(0, 0, 0.1f));
	CAMERA->setCameraAngle(cinder::vec2(0, 0));
}
//�e�L�X�g������
void TutorialUI::textInit()
{
	ui_data["�������"]->fontSetText(u8"�������");
	ui_data["�ړ���������"]->fontSetText(u8"�ړ�");
	ui_data["�ړ�����"]->fontSetText(u8"���X�e�B�b�N�𓮂�����");
	ui_data["�ړ������Q"]->fontSetText(u8"�O�㍶�E�ֈړ��\�ł�");
	ui_data["�ړ������R"]->fontSetText(u8"�ړ����Ă݂܂��傤");
	
	ui_data["���_����"]->fontSetText(u8"���_�ړ�");
	ui_data["���_�����Q"]->fontSetText(u8"�E�X�e�B�b�N�𓮂�����");
	ui_data["���_�����R"]->fontSetText(u8"���_�𓮂����܂�");
	ui_data["���_�����S"]->fontSetText(u8"���_�𓮂����Ă݂܂��傤");

	ui_data["�@�����"]->fontSetText(u8"�@���Ēn�ʂ��ړ�����");
	ui_data["�@������Q"]->fontSetText(u8"�uLB�v�{�^���𒷉��������\n�n�ʂ��@�邱�Ƃ��ł��܂��B");
	//�������X�V
	//���Ȃ�d���̂ŕK���P�t���[�������Ă�
	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
		if (ui_data[(*it)]->getUIType() == UITYPE::FontUI) {
			ci::TextLayout font_buf;
			font_buf.setColor(ci::ColorA(
				ui_data[(*it)]->fontGetColorR(),
				ui_data[(*it)]->fontGetColorG(),
				ui_data[(*it)]->fontGetColorB(),
				ui_data[(*it)]->fontGetColorA()));
			font_buf.setFont(font_data);
			font_buf.addLine(ui_data[(*it)]->fontGetText());

			font[(*it)] = font_buf;

			font_texture[(*it)] = ci::gl::Texture2d::create(font[(*it)].render(true));
		}
	}
}
void TutorialUI::tutorialMoveSetup(const float & delta_time)
{
	Game::cPlayerManager::getInstance()->getActivePlayer()->settingPosition(ci::vec3(Game::Field::WORLD_SIZE.x / 2, Game::Field::WORLD_SIZE.y + 0.5f, 17.0F));
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�������"]->setActive(true);
	ui_data["�������"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�ړ�"] = false;
	turo_flags["�������"] = false;
	turo_flags["�ړ��I��"] = false;
	turo_flags["��"] = false;
	turo_flags["��"] = false;
	turo_flags["��"] = false;
	turo_flags["�E"] = false;

}
void TutorialUI::tutorialMoveUpdate(const float& delta_time)
{

	if (!turo_flags["�������"] && !ui_data["������"]->getActive()) {
		turo_flags["�������"] = true;
		ui_data["��������"]->setActive(true);
		ui_data["��������"]->setActive(false);
		ui_data["�ړ���������"]->setActive(true);
		ui_data["�ړ���������"]->setActive(false);
	}
	if (turo_flags["�������"] && !turo_flags["�ړ�"] && !ui_data["��������"]->getActive()) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�ړ�����"]->setActive(true);
		ui_data["�ړ������Q"]->setActive(true);

		ui_data["�R���g���[����"]->setActive(true);
		ui_data["�X�e�B�b�N��"]->setActive(true);
		/*ui_data["W"]->setActive(true);
		ui_data["A"]->setActive(true);
		ui_data["S"]->setActive(true);
		ui_data["D"]->setActive(true);
		*/
		ui_data["up"]->setActive(true);
		ui_data["down"]->setActive(true);
		ui_data["left"]->setActive(true);
		ui_data["right"]->setActive(true);

	}
	if (ENV->pullKey(ci::app::MouseEvent::RIGHT_DOWN)) {
		turo_flags["�ړ�"] = true;

		ui_data["�ړ���"]->setActive(false);
		ui_data["�ړ�����"]->setActive(false);
		ui_data["�ړ������Q"]->setActive(false);

		ui_data["�R���g���[����"]->setActive(false);
		ui_data["�X�e�B�b�N��"]->setActive(false);
		/*ui_data["W"]->setActive(true);
		ui_data["A"]->setActive(true);
		ui_data["S"]->setActive(true);
		ui_data["D"]->setActive(true);
		*/
		ui_data["up"]->setActive(false);
		ui_data["down"]->setActive(false);
		ui_data["left"]->setActive(false);
		ui_data["right"]->setActive(false);

	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�ړ�"] == true
		&& turo_flags["�ړ��I��"] == false) {
		ui_data["�����Q"]->setActive(true);
		ui_data["�ړ������R"]->setActive(true);
		auto player_vec = Game::cPlayerManager::getInstance()->getActivePlayer()->getPlayerVec();
		if (player_vec.z >= 0.1f) { turo_flags["��"] = true; }
		if (player_vec.z <= -0.1f) { turo_flags["��"] = true; }
		if (player_vec.x <= -0.1f) { turo_flags["��"] = true; }
		if (player_vec.x >= 0.1f) { turo_flags["�E"] = true; }

		if (turo_flags["��"] &&
			turo_flags["��"] &&
			turo_flags["��"] &&
			turo_flags["�E"]) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�ړ��I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::EYE;
	}
}
void TutorialUI::tutorialEyeSetup(const float & delta_time)
{
	playerInit();
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["���_����"]->setActive(true);
	ui_data["���_����"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["���_"] = false;
	turo_flags["���_�I��"] = false;

	turo_flags["��"] = false;
	turo_flags["��"] = false;
	turo_flags["��"] = false;
	turo_flags["�E"] = false;
}
void TutorialUI::tutorialEyeUpdate(const float & delta_time)
{
	if (!turo_flags["���_"] && !ui_data["������"]->getActive()) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["���_�����Q"]->setActive(true);
		ui_data["���_�����R"]->setActive(true);

		ui_data["�R���g���[���E"]->setActive(true);
		ui_data["�X�e�B�b�N�E"]->setActive(true);

		ui_data["up2"]->setActive(true);
		ui_data["down2"]->setActive(true);
		ui_data["left2"]->setActive(true);
		ui_data["right2"]->setActive(true);

	}


	if (ENV->pullKey(ci::app::MouseEvent::RIGHT_DOWN)) {
		turo_flags["���_"] = true;

		ui_data["�ړ���"]->setActive(false);
		ui_data["���_�����Q"]->setActive(false);
		ui_data["���_�����R"]->setActive(false);

		ui_data["�R���g���[���E"]->setActive(false);
		ui_data["�X�e�B�b�N�E"]->setActive(false);

		ui_data["up2"]->setActive(false);
		ui_data["down2"]->setActive(false);
		ui_data["left2"]->setActive(false);
		ui_data["right2"]->setActive(false);

	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["���_"] == true
		&& turo_flags["���_�I��"] == false) {

		ui_data["�����Q"]->setActive(true);
		ui_data["���_�����S"]->setActive(true);
		auto player_vec = CAMERA->getCameraAngle();
		if (player_vec.y >= 0.1f) { turo_flags["��"] = true; }
		if (player_vec.y <= -0.1f) { turo_flags["��"] = true; }
		if (player_vec.x <= -0.1f) { turo_flags["��"] = true; }
		if (player_vec.x >= 0.1f) { turo_flags["�E"] = true; }

		if (turo_flags["��"] &&
			turo_flags["��"] &&
			turo_flags["��"] &&
			turo_flags["�E"]) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["���_�I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::DRILL;
	}


}

void TutorialUI::tutorialDrillSetup(const float & delta_time) {
	playerInit();
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�@�����"]->setActive(true);
	ui_data["�@�����"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�@��"] = false;
	turo_flags["�@��I��"] = false;

}
void TutorialUI::tutorialDrillUpdate(const float & delta_time){

	if (!turo_flags["�@��"] && !ui_data["������"]->getActive()) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�@������Q"]->setActive(true);

		ui_data["�R���g���[��LR"]->setActive(true);
		ui_data["�R���g���[��L"]->setActive(true);

		ui_data["�@���Ă�摜"]->setActive(true);

	}


	if (ENV->pullKey(ci::app::MouseEvent::RIGHT_DOWN)) {
		turo_flags["���_"] = true;

		ui_data["�ړ���"]->setActive(false);
		ui_data["���_�����Q"]->setActive(false);
		ui_data["���_�����R"]->setActive(false);

		ui_data["�R���g���[���E"]->setActive(false);
		ui_data["�X�e�B�b�N�E"]->setActive(false);

		ui_data["up2"]->setActive(false);
		ui_data["down2"]->setActive(false);
		ui_data["left2"]->setActive(false);
		ui_data["right2"]->setActive(false);

	}
}
void TutorialUI::update(const float& delta_time)
{
	if (buf_scene != static_cast<int>(now_scene)) {
		buf_scene = static_cast<int>(now_scene);
		switch (now_scene) {
		case TUTORIAL::MOVE:
			tutorialMoveSetup(delta_time);
			break;
		case TUTORIAL::EYE:
			tutorialEyeSetup(delta_time);
			break;
		case TUTORIAL::DRILL:
			tutorialDrillSetup(delta_time);
			break;
		}
	}

	switch (now_scene) {
	case TUTORIAL::MOVE:
		tutorialMoveUpdate(delta_time);
		break;
	case TUTORIAL::EYE:
		tutorialEyeUpdate(delta_time);
		break;
	case TUTORIAL::DRILL:
		tutorialDrillUpdate(delta_time);
		break;
	}
	
	UIPlate::update(delta_time);
}

void TutorialUI::draw()
{
	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
		if (!ui_data[(*it)]->getActive()) continue;
		
		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI ||
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::AnimationUI
			) {
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			textures[(*it)]->bind();

			ci::Rectf drawRect(ci::vec2(
				ui_data[(*it)]->getPosX(),
				ui_data[(*it)]->getPosY()),
				ci::vec2(
					ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
					ui_data[(*it)]->getPosY() - ui_data[(*it)]->getSizeY()));

			ci::gl::draw(textures[(*it)], drawRect);
			ci::gl::color(1, 1, 1, 1);
			textures[(*it)]->unbind();

			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
				gauge_texture[(*it)]->bind();

				ci::Rectf drawGauge(ci::vec2(
					ui_data[(*it)]->gaugeGetPosX(),
					ui_data[(*it)]->gaugeGetPosY()),
					ci::vec2(
						ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
						ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY()));

				ci::gl::draw(gauge_texture[(*it)], drawGauge);
				gauge_texture[(*it)]->unbind();
				ci::gl::color(1, 1, 1, 1);
			}
		}
		else if (ui_data[(*it)]->getUIType() == UITYPE::ScrollUI) {
			ci::gl::pushModelView();
			ci::gl::translate(ci::vec2(ui_data[(*it)]->getPosX() + (ui_data[(*it)]->getSizeX() / 2), ui_data[(*it)]->getPosY() + (ui_data[(*it)]->getSizeY() / 2)));
			ci::gl::scale(ci::vec2(scroll_scales[(*it)], scroll_scales[(*it)]));
			ci::gl::translate(ci::vec2(-(ui_data[(*it)]->getSizeX() / 2), -(ui_data[(*it)]->getSizeY() / 2)));
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			textures[(*it)]->bind();
			ci::Rectf drawRect(ci::vec2(
				0,
				0),
				ci::vec2(
					ui_data[(*it)]->getSizeX(),
					ui_data[(*it)]->getSizeY()));

			ci::gl::draw(textures[(*it)], drawRect);
			ci::gl::color(1, 1, 1, 1);
			textures[(*it)]->unbind();

			ci::gl::translate(ui_data[(*it)]->fontGetPosX(), ui_data[(*it)]->fontGetPosY());
			ci::gl::translate(ci::vec2(-50, -50));
			ci::gl::scale(ci::vec2(ui_data[(*it)]->fontGetScale(), ui_data[(*it)]->fontGetScale()));
			ci::gl::color(
				ui_data[(*it)]->fontGetColorR(),
				ui_data[(*it)]->fontGetColorG(),
				ui_data[(*it)]->fontGetColorB(),
				ui_data[(*it)]->fontGetColorA());
			ci::gl::draw(ci::gl::Texture2d::create(font[(*it)].render(true)));

			ci::gl::color(ci::Color::white());
			ci::gl::popModelView();


		}
		else if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {

			ci::gl::pushModelView();
			ci::gl::translate(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY());
			ci::gl::translate(ci::vec2(-50, 50));
			ci::gl::scale(ci::vec2(ui_data[(*it)]->fontGetScale(), -ui_data[(*it)]->fontGetScale()));
			ci::gl::color(
				ui_data[(*it)]->fontGetColorR(),
				ui_data[(*it)]->fontGetColorG(),
				ui_data[(*it)]->fontGetColorB(),
				ui_data[(*it)]->fontGetColorA());
			ci::gl::draw(font_texture[(*it)]);

			ci::gl::color(ci::Color::white());

			ci::gl::popModelView();
		}
	}
}



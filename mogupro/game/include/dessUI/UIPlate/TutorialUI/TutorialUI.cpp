#include "TutorialUI.h"
#include <Utility/cInput.h>
#include <Game/cPlayerManager.h>
#include <Game/Field/FieldData.h>
#include <CameraManager/cCameraManager.h>
#include <Game/cStrategyManager.h>
#include <Network/cUDPClientManager.h>
#include <Game/cFieldManager.h>
#include <Game/cCapsuleManager.h>
#include <Scene/cSceneManager.h>
#include <Resource/cSoundManager.h>
#include <Scene/Member/cTitle.h>
void TutorialUI::setup(const dess::SceneName & name)
{
	now_scene = TUTORIAL::MOVE;
	buf_scene = static_cast<int>(TUTORIAL::NONE);
	UIPlate::setup(name);
	textInit();

	ENV->disableKeyButton();
	ENV->disablePadAxis();
	ENV->disablePadButton();
	ENV->disableMouseButton();
}
//�v���C���[������
void TutorialUI::playerInit()
{
	Game::cPlayerManager::getInstance()->getActivePlayer()->settingPosition(ci::vec3(Game::Field::WORLD_SIZE.x / 2, Game::Field::WORLD_SIZE.y + 0.5f, 17.0F));
	Game::cPlayerManager::getInstance()->getActivePlayer()->move(ci::vec3(0, 0, 0.1f));
	CAMERA->setCameraAngle(cinder::vec2(0, -0.3f));
	Game::cFieldManager::getInstance()->blockAllReset();
	Game::cPlayerManager::getInstance()->getActivePlayer()->useSubWeapon.clearSubWeapon();
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
	ui_data["�@������R"]->fontSetText(u8"�n�ʂ��@���Ĉړ����܂��傤�B");
	ui_data["�@������S"]->fontSetText(u8"�E�X�e�B�b�N�ňړ�����\n������ς��邱�Ƃ��ł��܂��B");

	ui_data["�W�F������"]->fontSetText(u8"�W�F�����W�߂�");
	ui_data["�W�F�������Q"]->fontSetText(u8"�n�ʂ̒��Ō����Ă�����̂�\n�u�W�F���v�ƌ����܂�\n�W�F���͔j�󂷂鎖�Ŏ擾�ł��܂��B");
	ui_data["�W�F�������R"]->fontSetText(u8"��");
	ui_data["�W�F�������S"]->fontSetText(u8"�uRT�v�{�^���ōU�����ł��܂�\n�W�F���͒n���ɂ���̂ŁA\n�@���ċ߂��܂ōs���A\n�U�������邱�ƂŎ擾�\�ł�");
	ui_data["�W�F�������T"]->fontSetText(u8"�U��");
	ui_data["�W�F�������U"]->fontSetText(u8"�n�ʂ̉��ɂ���W�F�����U�����ĉ�����܂��傤");
	
	ui_data["�U������"]->fontSetText(u8"�G��|��");
	ui_data["�U�������Q"]->fontSetText(u8"�U���͓G��|�������ł��܂��B\n�uRT�v�{�^���𒷉�������ƁA\n�`���[�W���鎖���ł��A�����Ɖ����̓G��\n�U���ł���u�`���[�W�V���b�g�v�ɂȂ�܂��B");
	ui_data["�U�������R"]->fontSetText(u8"�ڂ̑O�̓G��|���Ă�������");
	
	ui_data["�[�i����"]->fontSetText(u8"�擾�����W�F���́A�����̃`�[���̑�C�Ɏ����Ă����܂��B");
	ui_data["�[�i�����Q"]->fontSetText(u8"��C�̋߂��ɍs���Ƒ�C�ɃW�F����\n����邱�Ƃ��ł��܂��B\n�W�F��������ƁA��ʍ��ɂ���\n�Q�[�W�����܂��čs���܂��B\n�Q�[�W�𖞃^���ɂ���Ώ����ƂȂ�܂��B");
	ui_data["�[�i�����R"]->fontSetText(u8"�W�F�����C�ɓ���܂��傤");

	ui_data["�A�C�e������"]->fontSetText(u8"�A�C�e��");
	ui_data["�A�C�e�������Q"]->fontSetText(u8"�n�ʂɂ̓A�C�e�������܂��Ă��܂��B\n�߂Â����ƂŎ擾���ł��܂��B");
	ui_data["�A�C�e�������R"]->fontSetText(u8"�uRB�v�L�[�Ŏg�p�\�ł��B\n�ǂ�ǂ�g���Ă����܂��傤�I");
	ui_data["�A�C�e�������S"]->fontSetText(u8"�A�C�e�����擾���Ă��������B");
	ui_data["�A�C�e�������T"]->fontSetText(u8"�A�C�e�����g�p���Ă��������B");
	
	ui_data["�Ō����"]->fontSetText(u8"��������͈ȏ�ɂȂ�܂��B\n���̃Q�[���́A�u��C�̃Q�[�W�����^����\n�Ȃ������������v�ł��̂ŁA�ϋɓI��\n�W�F�����W�߂Ă����܂��傤�B");
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
	playerInit();
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

	//�J�E���g�̏�����
	tuto_counts["�ړ������̎���"] = 0.0f;

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

		tuto_counts["�ړ������̎���"] += delta_time;
	}
	if (tuto_counts["�ړ������̎���"] > 7.0f) {
		turo_flags["�ړ�"] = true;

		ui_data["�ړ���"]->setActive(false);
		ui_data["�ړ�����"]->setActive(false);
		ui_data["�ړ������Q"]->setActive(false);
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
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
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
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

	//�J�E���g�̏�����
	tuto_counts["���_����"] = 0.0f;
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

		tuto_counts["���_����"] += delta_time;
	}


	if (tuto_counts["���_����"] > 7) {
		turo_flags["���_"] = true;
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
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
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
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
	turo_flags["�@��Q��"] = false;
	turo_flags["�@��I��"] = false;

	//�J�E���g�̏�����
	tuto_counts["�@������P��"] = 0.0f;
	tuto_counts["�@������Q��"] = 0.0f;
	tuto_counts["�@��������"] = 0.0f;
}
void TutorialUI::tutorialDrillUpdate(const float & delta_time){

	if (!turo_flags["�@��"] && !ui_data["������"]->getActive() && turo_flags["�@��Q��"] == false) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�@������Q"]->setActive(true);

		ui_data["�R���g���[��LR"]->setActive(true);
		ui_data["�R���g���[��L"]->setActive(true);

		ui_data["�@���Ă�摜"]->setActive(true);

		tuto_counts["�@������P��"] += delta_time;
	}


	if (tuto_counts["�@������P��"] > 7
		&& turo_flags["�@��Q��"] == false) {
		turo_flags["�@��Q��"] = true;
		ui_data["�@������Q"]->setActive(false);
		ui_data["�R���g���[��LR"]->setActive(false);

		ui_data["�R���g���[��L"]->setActive(false);
		ui_data["�@���Ă�摜"]->setActive(false);


		ui_data["�@������S"]->setActive(true);
		ui_data["�R���g���[���E"]->setActive(true);
		ui_data["�X�e�B�b�N�E"]->setActive(true);

		ui_data["up2"]->setActive(true);
		ui_data["down2"]->setActive(true);
		ui_data["left2"]->setActive(true);
		ui_data["right2"]->setActive(true);
	}
	if (turo_flags["�@��Q��"]) {
		tuto_counts["�@������Q��"] += delta_time;
	}

	if (tuto_counts["�@������Q��"] > 5) {
		turo_flags["�@��"] = true;
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
		ui_data["�ړ���"]->setActive(false);

		ui_data["�@������S"]->setActive(false);
		ui_data["�R���g���[���E"]->setActive(false);
		ui_data["�X�e�B�b�N�E"]->setActive(false);

		ui_data["up2"]->setActive(false);
		ui_data["down2"]->setActive(false);
		ui_data["left2"]->setActive(false);
		ui_data["right2"]->setActive(false);
	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�@��"] == true
		&& turo_flags["�@��I��"] == false) {
		
		ui_data["�����Q"]->setActive(true);
		ui_data["�@������R"]->setActive(true);
		if (Game::cPlayerManager::getInstance()->getActivePlayer()->isDrilling()) {
			tuto_counts["�@��������"] += delta_time;
		}

		if (tuto_counts["�@��������"] > 6) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�@��I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::GEM;
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
	}
}

void TutorialUI::tutorialGemSetup(const float & delta_time) {
	playerInit();
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�W�F������"]->setActive(true);
	ui_data["�W�F������"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�W�F��"] = false;
	turo_flags["�W�F���Q��"] = false;
	turo_flags["�W�F���I��"] = false;

	//�J�E���g�̏�����
	tuto_counts["�W�F�������P��"] = 0.0f;
	tuto_counts["�W�F�������Q��"] = 0.0f;
}
void TutorialUI::tutorialGemUpdate(const float & delta_time) {
	if (!turo_flags["�W�F��"] && !ui_data["������"]->getActive() && turo_flags["�W�F���Q��"] == false) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�W�F�������Q"]->setActive(true);
		ui_data["�W�F�������R"]->setActive(true);


		ui_data["�W�F���擾�摜"]->setActive(true);
		ui_data["�W�F���擾�摜�Q"]->setActive(true);

		tuto_counts["�W�F�������P��"] += delta_time;
	}


	if (tuto_counts["�W�F�������P��"] > 10
		&& turo_flags["�W�F���Q��"] == false) {
		turo_flags["�W�F���Q��"] = true;
		ui_data["�W�F�������Q"]->setActive(false);
		ui_data["�W�F�������R"]->setActive(false);


		ui_data["�W�F���擾�摜"]->setActive(false);
		ui_data["�W�F���擾�摜�Q"]->setActive(false);


		ui_data["�W�F�������S"]->setActive(true);
		ui_data["�W�F�������T"]->setActive(true);
		ui_data["�R���g���[��LR"]->setActive(true);
		ui_data["�R���g���[��R2"]->setActive(true);
		ui_data["�W�F���擾�摜�R"]->setActive(true);
	}
	if (turo_flags["�W�F���Q��"]) {
		tuto_counts["�W�F�������Q��"] += delta_time;
	}

	if (tuto_counts["�W�F�������Q��"] > 10) {
		turo_flags["�W�F��"] = true;

		ui_data["�ړ���"]->setActive(false);

		ui_data["�W�F�������S"]->setActive(false);
		ui_data["�W�F�������T"]->setActive(false);
		ui_data["�R���g���[��LR"]->setActive(false);
		ui_data["�R���g���[��R2"]->setActive(false);
		ui_data["�W�F���擾�摜�R"]->setActive(false);
	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�W�F��"] == true
		&& turo_flags["�W�F���I��"] == false) {
		
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();

		ui_data["�����Q"]->setActive(true);
		ui_data["�W�F�������U"]->setActive(true);
		
		if (Game::cPlayerManager::getInstance()->getActivePlayer()->getgems.size() > 6) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�W�F���I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::DELIVERY;
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
	}
}

void TutorialUI::tutorialAttackSetup(const float & delta_time)
{
	playerInit();

	auto packet = new Network::Packet::Request::cReqPlayer();
	packet->mFormat.playerId = 5;
	packet->mFormat.position = ci::vec3(Game::Field::WORLD_SIZE.x / 2, Game::Field::WORLD_SIZE.y + 0.5f, 20.0F);
	packet->mFormat.rotation = ci::vec2(0);
	Network::cUDPClientManager::getInstance()->send(packet);

	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�U������"]->setActive(true);
	ui_data["�U������"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�U��"] = false;
	turo_flags["�U���I��"] = false;

	//�J�E���g�̏�����
	tuto_counts["�U������"] = 0.0f;
}

void TutorialUI::tutorialAttackUpdate(const float & delta_time)
{
	if (!turo_flags["�U��"] && !ui_data["������"]->getActive()) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�U�������Q"]->setActive(true);

		ui_data["�R���g���[��LR"]->setActive(true);
		ui_data["�R���g���[��R2"]->setActive(true);

		ui_data["�U���摜"]->setActive(true);

		tuto_counts["�U������"] += delta_time;
	}


	if (tuto_counts["�U������"] > 10) {
		turo_flags["�U��"] = true;
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
		ui_data["�ړ���"]->setActive(false);
		ui_data["�U�������Q"]->setActive(false);

		ui_data["�R���g���[��LR"]->setActive(false);
		ui_data["�R���g���[��R2"]->setActive(false);

		ui_data["�U���摜"]->setActive(false);

	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�U��"] == true
		&& turo_flags["�U���I��"] == false) {
		
		ui_data["�����Q"]->setActive(true);
		ui_data["�U�������R"]->setActive(true);


		auto enemy = Game::cPlayerManager::getInstance()->getPlayer(5);
		if (enemy->isDead()) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�U���I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::ITEM;
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
	}
}

void TutorialUI::tutorialDeliverySetup(const float & delta_time)
{
	playerInit();
	
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�[�i����"]->setActive(true);
	ui_data["�[�i����"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�[�i"] = false;
	turo_flags["�[�i�Q"] = false;
	turo_flags["�[�i�I��"] = false;

	//�J�E���g�̏�����
	tuto_counts["�[�i����"] = 0.0f;
	tuto_counts["�[�i�����Q"] = 0.0f;
	
	c_Easing::apply(camera_angle_buf.x, -3 * M_PI / 2, EasingFunction::Linear, 10);
	c_Easing::apply(camera_angle_buf.y, -0.7f, EasingFunction::Linear, 10);
	CAMERA->setCameraFar(cannon_far);
}

void TutorialUI::tutorialDeliveryUpdate(const float & delta_time)
{
	if (!turo_flags["�[�i"]) {
		CAMERA->setCameraAngle(camera_angle_buf);
		CAMERA->refPosition = Game::Field::CANNON_POINT[0];
	}

	if (!turo_flags["�[�i"] && !ui_data["������"]->getActive() && turo_flags["�[�i�Q"] == false) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�[�i�����Q"]->setActive(true);


		ui_data["�[�i�摜"]->setActive(true);
		ui_data["�[�i�摜�Q"]->setActive(true);
		ui_data["�[�i�摜�R"]->setActive(true);

		tuto_counts["�[�i����"] += delta_time;
	}


	if (tuto_counts["�[�i����"] > 10) {
		turo_flags["�[�i"] = true;
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
		ui_data["�ړ���"]->setActive(false);
		ui_data["�[�i�����Q"]->setActive(false);
		
		ui_data["�[�i�摜"]->setActive(false);
		ui_data["�[�i�摜�Q"]->setActive(false);
		ui_data["�[�i�摜�R"]->setActive(false);

		CAMERA->setCameraFar(player_far);
	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�[�i"] == true
		&& turo_flags["�[�i�I��"] == false) {

		ui_data["�����Q"]->setActive(true);
		ui_data["�[�i�����R"]->setActive(true);
		

		auto enemy = Game::cPlayerManager::getInstance()->getPlayer(5);
		if (Game::cStrategyManager::getInstance()->getCannons()[Game::cPlayerManager::getInstance()->getActivePlayer()->getWhichTeam()]->getGEmNum() > 0) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�[�i�I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::ATTACK;
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
	}
}

void TutorialUI::tutorialItemSetup(const float & delta_time) {
	playerInit();
	auto packet = new Network::Packet::Request::cReqPlayer();
	packet->mFormat.playerId = 5;
	packet->mFormat.position = ci::vec3(Game::Field::WORLD_SIZE.x / 2 - 0.5F, Game::Field::WORLD_SIZE.y + 1.0F, Game::Field::WORLD_SIZE.z - 8.0F );
	packet->mFormat.rotation = ci::vec2(0);
	Network::cUDPClientManager::getInstance()->send(packet);

	auto item_pos1 = ci::vec3(Game::Field::WORLD_SIZE.x / 2+2, Game::Field::WORLD_SIZE.y + 0.5f, 20.0F);
	auto item_pos2 = ci::vec3(Game::Field::WORLD_SIZE.x / 2-2, Game::Field::WORLD_SIZE.y + 0.5f, 20.0F);
	Game::cCapsuleManager::getInstance()->createCapsule(item_pos1, Game::Weapons::SubWeapon::LIGHT_BOMB, 99);
	Game::cCapsuleManager::getInstance()->createCapsule(item_pos2, Game::Weapons::SubWeapon::QUARRY, 100);
	ui_data["������"]->setActive(true);
	ui_data["������"]->setActive(false);
	ui_data["�A�C�e������"]->setActive(true);
	ui_data["�A�C�e������"]->setActive(false);
	ui_data["FadePlateIn"]->setActive(true);

	//�i�s�t���O������
	turo_flags["�A�C�e��"] = false;
	turo_flags["�A�C�e���Q��"] = false;
	turo_flags["�A�C�e���I��"] = false;

	turo_flags["�A�C�e���������"] = false;

	//�J�E���g�̏�����
	tuto_counts["�A�C�e�������P��"] = 0.0f;
	tuto_counts["�A�C�e�������Q��"] = 0.0f;
}
void TutorialUI::tutorialItemUpdate(const float & delta_time) {

	if (!turo_flags["�A�C�e��"] && !ui_data["������"]->getActive() && turo_flags["�A�C�e���Q��"] == false) {

		ui_data["�ړ���"]->setActive(true);
		ui_data["�A�C�e�������Q"]->setActive(true);

		ui_data["�A�C�e���摜"]->setActive(true);

		tuto_counts["�A�C�e�������P��"] += delta_time;
	}


	if (tuto_counts["�A�C�e�������P��"] > 7
		&& turo_flags["�A�C�e���Q��"] == false) {
		turo_flags["�A�C�e���Q��"] = true;
		ui_data["�A�C�e�������Q"]->setActive(false);

		
		ui_data["�A�C�e���摜"]->setActive(false);

		ui_data["�A�C�e���摜�Q"]->setActive(true);
		ui_data["�A�C�e���摜�R"]->setActive(true);

		ui_data["�A�C�e�������R"]->setActive(true);
		ui_data["�R���g���[��LR"]->setActive(true);
		ui_data["�R���g���[��R"]->setActive(true);
	}
	if (turo_flags["�A�C�e���Q��"]) {
		tuto_counts["�A�C�e�������Q��"] += delta_time;
	}

	if (tuto_counts["�A�C�e�������Q��"] > 5) {
		turo_flags["�A�C�e��"] = true;
		
		ui_data["�ړ���"]->setActive(false);

		ui_data["�A�C�e���摜�Q"]->setActive(false);
		ui_data["�A�C�e���摜�R"]->setActive(false);

		ui_data["�A�C�e�������R"]->setActive(false);
		ui_data["�R���g���[��LR"]->setActive(false);
		ui_data["�R���g���[��R"]->setActive(false);
	}

	if (ui_data["�ړ���"]->getActive() == false && turo_flags["�A�C�e��"] == true
		&& turo_flags["�A�C�e���I��"] == false) {
		ENV->enableKeyButton();
		ENV->enablePadAxis();
		ENV->enablePadButton();
		ENV->enableMouseButton();
		ui_data["�����Q"]->setActive(true);
		ui_data["�A�C�e�������S"]->setActive(true);

		auto item_size = Game::cPlayerManager::getInstance()->getActivePlayer()->useSubWeapon.getItemNum();

		if (item_size > 0) {
			turo_flags["�A�C�e���������"] = true;
			ui_data["�A�C�e�������S"]->setActive(false);
			ui_data["�A�C�e�������T"]->setActive(true);
		}

		if (turo_flags["�A�C�e���������"] && item_size <= 0) {
			ui_data["OK!"]->setActive(true);
			ui_data["FadePlateIn"]->setActive(false);
			for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
				ui_data[(*it)]->setActive(false);
			}
			turo_flags["�A�C�e���I��"] = true;
		}
	}
	if (!ui_data["FadePlateIn"]->getActive()) {
		now_scene = TUTORIAL::END;
		ENV->disableKeyButton();
		ENV->disablePadAxis();
		ENV->disablePadButton();
		ENV->disableMouseButton();
	}
}
void TutorialUI::tutorialEndSetup(const float & delta_time) {
	playerInit();
	
	ui_data["�ړ���"]->setActive(true);
	ui_data["�Ō����"]->setActive(true);
	ui_data["�Ō�摜"]->setActive(true);
	ui_data["�Ō�摜�Q"]->setActive(true);
	ui_data["FadePlateIn"]->setActive(true);

	//�J�E���g�̏�����
	tuto_counts["�Ō����"] = 0.0f;
}

void TutorialUI::tutorialEndUpdate(const float & delta_time)
{
	tuto_counts["�Ō����"] += delta_time;

	if (tuto_counts["�Ō����"] > 10) {
		ui_data["�ړ���"]->setActive(false);
		ui_data["�Ō����"]->setActive(false);
		ui_data["�Ō�摜"]->setActive(false);
		ui_data["�Ō�摜�Q"]->setActive(false);
		ui_data["FadePlateIn"]->setActive(false);
	}

	
	if (!ui_data["FadePlateIn"]->getActive()) {
		Resource::cSoundManager::getInstance()->findBgm("�g���s�J�����E.wav").stop();
		Scene::cSceneManager::getInstance()->shift<Scene::Member::cTitle>();
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
		case TUTORIAL::GEM:
			tutorialGemSetup(delta_time);
			break;
		case TUTORIAL::ATTACK:
			tutorialAttackSetup(delta_time);
			break;
		case TUTORIAL::DELIVERY:
			tutorialDeliverySetup(delta_time);
			break;
		case TUTORIAL::ITEM:
			tutorialItemSetup(delta_time);
			break;
		case TUTORIAL::END:
			tutorialEndSetup(delta_time);
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
	case TUTORIAL::GEM:
		tutorialGemUpdate(delta_time);
		break;
	case TUTORIAL::ATTACK:
		tutorialAttackUpdate(delta_time);
		break;
	case TUTORIAL::DELIVERY:
		tutorialDeliveryUpdate(delta_time);
		break;
	case TUTORIAL::ITEM :
		tutorialItemUpdate(delta_time);
		break;
	case TUTORIAL::END:
		tutorialEndUpdate(delta_time);
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



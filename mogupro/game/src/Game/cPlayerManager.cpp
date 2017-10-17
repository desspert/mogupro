#include <Game/Player/cPlayer.h>
#include <Game/cPlayerManager.h>
#include <Utility/cInput.h>
#include <CameraManager/cCameraManager.h>
#include <Game/cStrategyManager.h>
#include <Game/Strategy/cDrill.h>


void Game::cPlayerManager::playerInstance()
{
	//�l��(�ʐM�ő��)
	int player_number = 2;
	//���������삷�郆�[�U�[���ǂ���
	int active_user_number = 0;

	std::vector<ci::vec3> player_pos;
	player_pos.push_back(ci::vec3(20, 20, 0));
	player_pos.push_back(ci::vec3(30, 0, 30));


	//����
	for (int i = 0; i < player_number; i++) {
		//�ʐM�ő��
		if (active_user_number == 0) {
			player.push_back(std::make_shared<Player::cPlayer>(player_pos[i], ci::vec3(0, 0, 0), i, true));
			//�A�N�e�B�u���[�U�ɑ��
			active_player = player[i];
		}
		else {
			player.push_back(std::make_shared<Player::cPlayer>(player_pos[i], ci::vec3(0, 0, 0), i, false));
		}

	}
}

void Game::cPlayerManager::playerDrillMove(const float & delta_time)
{
	//�J�����̕����Ɉړ�
	float player_speed = delta_time * active_player->getSpeed();
	active_player->move(ci::vec3(CAMERA->getCameraLook().x * player_speed, CAMERA->getCameraLook().y * player_speed, CAMERA->getCameraLook().z * player_speed));
}

void Game::cPlayerManager::playerNormalMove(const float& delta_time)
{
	//�v���C���[�̑��x
	float player_speed = active_player->getSpeed() * delta_time;

	if (ENV->pressKey(ci::app::KeyEvent::KEY_w)) {
		active_player->move(ci::vec3(player_speed*sin(CAMERA->getCameraAngle().x), 0.0f, player_speed * cos(CAMERA->getCameraAngle().x)));
	}

	if (ENV->pressKey(ci::app::KeyEvent::KEY_s)) {
		active_player->move(ci::vec3(-player_speed*sin(CAMERA->getCameraAngle().x), 0.0f, -player_speed*cos(CAMERA->getCameraAngle().x)));
	}

	if (ENV->pressKey(ci::app::KeyEvent::KEY_d)) {
		active_player->move(ci::vec3(-player_speed*cos(CAMERA->getCameraAngle().x), 0, player_speed*sin(CAMERA->getCameraAngle().x)));
	}

	if (ENV->pressKey(ci::app::KeyEvent::KEY_a)) {
		active_player->move(ci::vec3(+player_speed*cos(CAMERA->getCameraAngle().x), 0, -player_speed*sin(CAMERA->getCameraAngle().x)));
	}
		

	if (ENV->pressKey(ci::app::KeyEvent::KEY_q)) {
		active_player->move(ci::vec3(0, -player_speed, 0));
	}

	if (ENV->pressKey(ci::app::KeyEvent::KEY_e)) {
		active_player->move(ci::vec3(0, player_speed, 0));
	}
	//�@��@�ݒu
	if (ENV->pushKey(ci::app::KeyEvent::KEY_o)) {
		Game::cStrategyManager::getInstance()->CreateStrategyObject(Game::Strategy::cDrill(active_player->getPos(), ci::vec3(1),0));
	}

}
void Game::cPlayerManager::playerMove(const float & delta_time)
{
	//�J�����̃}�E�X����ON�@OFF
	if (ENV->pushKey(ci::app::KeyEvent::KEY_ESCAPE)) {
		ENV->setMouseControl(mouse_on);
		if (mouse_on == true) {
			mouse_on = false;
		}
		else {
			mouse_on = true;
		}
	}
	//�p�b�h�̔��艼�u��
	if (ENV->isPadPush(ENV->BUTTON_1)) {
		CAMERA->shakeCamera(0.1f, 0.1f);
	}
	CAMERA->setCameraAngle(ci::vec2(ENV->getPadAxis(2)*(-0.05f), ENV->getPadAxis(3)*(-0.05f)));

	//�@�풆�͓��������ς��
	if (active_player->isDrilling()) {
		playerDrillMove(delta_time);
	}
	else {
		playerNormalMove(delta_time);
	}
	
	

	//�@�풆��true 
	active_player->Drilling(false);
	if (ENV->pressKey(ci::app::MouseEvent::LEFT_DOWN)) {
		active_player->Drilling(true);
	}
	if (ENV->pressKey(ci::app::KeyEvent::KEY_m)) {
		active_player->Drilling(true);
	}


	if (ENV->pressKey(ci::app::KeyEvent::KEY_UP)) {
		CAMERA->setCameraAngle(ci::vec2(0, 0.05f));
	}
	if (ENV->pressKey(ci::app::KeyEvent::KEY_DOWN))
		CAMERA->setCameraAngle(ci::vec2(0, -0.05f));

	if (ENV->pressKey(ci::app::KeyEvent::KEY_RIGHT))
		CAMERA->setCameraAngle(ci::vec2(-0.05f, 0));

	if (ENV->pressKey(ci::app::KeyEvent::KEY_LEFT))
		CAMERA->setCameraAngle(ci::vec2(0.05f, 0));
}
void Game::cPlayerManager::setup()
{
	playerInstance();
	//�|�W�V�����̎Q�ƂƃJ�����̃Y�[����ݒ�
	CAMERA->followingCamera(&active_player->getReferencePos(), 15);
	for (auto it : player) {
		it->setup();
	}
}

void Game::cPlayerManager::update(const float& delta_time)
{
	
	for (auto it : player) {
		it->update(delta_time);
	}
	playerMove(delta_time);
}

void Game::cPlayerManager::draw()
{
	for (auto it : player) {
		it->draw();
	}
}

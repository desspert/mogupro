#include <Game/Weapons/MainWeapon/LightSaber.h>
#include <cinder/gl/gl.h>
#include <Game/cPlayerManager.h>
#include <Utility/cInput.h>
#include <CameraManager/cCameraManager.h>
void Game::Weapon::LightSaber::Attack(const float & delta_time)
{
	player_pos = root->get_position_3d();
	//�v���C���[�̈ʒu����ray��aabb�𐶐�
	ray.setOrigin(player_pos);
	ray.setDirection(player_vec);
	//aabb.set(player_pos - player_size, player_pos + player_size);

	//hits�̃x�N�^�[�ɓ���邽�߂�i
	int i = 0;
	for (auto& it : cPlayerManager::getInstance()->getPlayers()) {
		i++;
		//�����̑��삵�Ă���v���C���[�Ȃ�Ԃ�
		if (it->getActiveUser())continue;

		//ray������������is_hit��true�ɂȂ�
		bool is_hit = it->getAABB().intersects(ray);
		//is_hit = it->getAABB().intersects(aabb);

		//�Ώۂ̃v���C���[��hit������
		if (is_hit) {
			//�����������̉��o�Ƃ��Ĉ�u�J������h�炷
			CAMERA->shakeCamera(0.1f, 0.1f);
			it->receiveDamage(is_hit, attack);
			//�Ώۂ�hit��true�ɂ���
			//�Ώی���Ńq�b�g�X�g�b�v�������蓖���蔻����Ȃ�������
			//�����
			hits[i - 1] = true;
		}
	}
}
using namespace Node::Action;
void Game::Weapon::LightSaber::Operation()
{
	if (ENV->pushKey(ci::app::KeyEvent::KEY_t)) {
		ci::app::console() << push << std::endl;
		//�v���C���[��pos��Vec��size���擾
		player_pos = cPlayerManager::getInstance()->getActivePlayer()->getPos();
		player_vec = player_pos + cPlayerManager::getInstance()->getActivePlayer()->getPlayerVec() * ci::vec3(range * 10);
		root->set_position_3d(player_pos);
		root->set_schedule_update();
		root->run_action(Node::Action::sequence::create(
			ease<ci::EaseOutCubic>::create(move_to::create(1.0F, player_pos + ci::vec3(2,0,0))),
			ease<ci::EaseOutCubic>::create(move_to::create(1.0F, player_pos + ci::vec3(-2, 0, 0)))
		));
	}
}

Game::Weapon::LightSaber::LightSaber()
{
	attack = 30;
	range = 3;
	player_pos = ci::vec3(0);
	player_vec = ci::vec3(0);
}

void Game::Weapon::LightSaber::setup()
{
	//����������Ԃ��v���C���[���Ƃɕێ����邽�߂�
	//�v���C���[�̌����v�b�V���o�b�N
	for (int i = 0; i < cPlayerManager::getInstance()->getPlayers().size();i++) {
		hits.push_back(false);
	}
	root = Node::node::create();
	root->set_schedule_update();
}

void Game::Weapon::LightSaber::update(const float & delta_time)
{
	Operation();
	root->entry_update(delta_time);
	Attack(delta_time);
}

void Game::Weapon::LightSaber::draw()
{
	ci::gl::drawVector(ray.getOrigin(), ray.getDirection());
}

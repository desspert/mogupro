#include <Game/Weapons/MainWeapon/LightSaber.h>
#include <cinder/gl/gl.h>
#include <Game/cPlayerManager.h>
#include <Utility/cInput.h>
void Game::Weapon::LightSaber::Attack()
{

}

void Game::Weapon::LightSaber::Operation()
{
}

Game::Weapon::LightSaber::LightSaber()
{
	attack = 30;
	range = 3;
}

void Game::Weapon::LightSaber::setup()
{
	//����������Ԃ��v���C���[���Ƃɕێ����邽�߂�
	//�v���C���[�̌����v�b�V���o�b�N
	for (int i = 0; i < cPlayerManager::getInstance()->getPlayers().size();i++) {
		hits.push_back(false);
	}
	
}

void Game::Weapon::LightSaber::update(const float & delta_time)
{

	//�v���C���[��pos��Vec��size���擾
	ci::vec3 player_pos = cPlayerManager::getInstance()->getActivePlayer()->getPos();
	ci::vec3 player_vec = cPlayerManager::getInstance()->getActivePlayer()->getPlayerVec();
	ci::vec3 player_size = ci::vec3(cPlayerManager::getInstance()->getActivePlayer()->getSize());

	//�v���C���[�̈ʒu����ray��aabb�𐶐�
	ray.setOrigin(player_pos);
	ray.setDirection(player_pos + player_vec * ci::vec3(range));
	aabb.set(player_pos - player_size, player_pos + player_size);
	
	//hits�̃x�N�^�[�ɓ���邽�߂�i
	int i = 0;
	for (auto& it : cPlayerManager::getInstance()->getPlayers()) {
		i++;
		//�����̑��삵�Ă���v���C���[�Ȃ�Ԃ�
		if (it->getActiveUser())continue;

		//ray������������is_hit��true�ɂȂ�
		bool is_hit = it->getAABB().intersects(ray);
		is_hit = it->getAABB().intersects(aabb);

		//�Ώۂ̃v���C���[��hit������
		if (hits[i - 1] == false) {
			it->receiveDamage(is_hit, attack);
			//�Ώۂ�hit��true�ɂ���
			//�Ώی���Ńq�b�g�X�g�b�v�������蓖���蔻����Ȃ�������
			//�����
			hits[i-1] = true;
		}
	}
}

void Game::Weapon::LightSaber::draw()
{
	ci::gl::drawVector(ray.getOrigin(), ray.getDirection()/ci::vec3(10));
}

#include <Game/Weapons/MainWeapon/LightSaber.h>
#include <cinder/gl/gl.h>
#include <Game/cPlayerManager.h>
#include <Utility/cInput.h>
#include <CameraManager/cCameraManager.h>
#include <Resource/cObjectManager.h>
#include <Resource/TextureManager.h>

float Linear(float t, float b, float e) {
	return (e - b) * t + b;
}
void Game::Weapon::LightSaber::Attack(const float & delta_time)
{
	if (!is_attack)return;
	weapon_draw_pos = player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x)));
	aabb = ci::AxisAlignedBox(weapon_draw_pos - ci::vec3(range/2), weapon_draw_pos + ci::vec3(range / 2));
	light->reAttachPositionWithRadius(light,weapon_draw_pos,2);
	//hits�̃x�N�^�[�ɓ���邽�߂�i
	int i = -1;
	for (auto& it : cPlayerManager::getInstance()->getPlayers()) {
		i++;
		//�����̑��삵�Ă���v���C���[�Ȃ�Ԃ�
		if (it->getActiveUser()) {
			continue;
		}
		//���ɓ������Ă�����Ԃ�
		if (hits[i -1]) {
			continue;
		}
		//AABB�ɓ����ĂȂ���Δ��肵�Ȃ�
		if (!aabb.intersects(it->getAABB()))continue;

		//ray������������is_hit��true�ɂȂ�
		bool is_hit = false;

		float min = 0.0F, max = 0.0F;
		
		ci::vec2 rotate_buf;
		//���x�������Ă�������悤�ɂP�t���[���ɂT�O����
		int split = 50;
		for (int k = 0; k < split; k++) {

			rotate_buf.x = Linear((float)k / split, rotate_before_frame.x, rotate.x);
			rotate_buf.y = Linear((float)k / split, rotate_before_frame.y, rotate.y);

			weapon_pos = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y), cos(rotate_buf.x + player_rotate_x))) / ci::vec3(10);

			weapon_vec = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y), cos(rotate_buf.x + player_rotate_x))) * ci::vec3(10) * ci::vec3(range);

			//�v���C���[�̈ʒu����ray��aabb�𐶐�
			ray[0].setOrigin(weapon_pos);
			ray[0].setDirection(weapon_vec);

			//�P��ڂ̍U��
			Rotation1(rotate_buf,M_PI / 5);

			for (int m = 0; m < 3; m++) {

				if (it->getAABB().intersect(ray[m], &min, &max) != 0)
				{
					if (min >= 0.0F && min <= 1.0F)
					{
						if (min < std::numeric_limits<float>::max())
						{
							is_hit = true;
						}
					}
				}
				if (is_hit)break;
			}
			if (is_hit)break;
		}
		//�Ώۂ̃v���C���[��hit������
		if (is_hit) {
			ci::app::console() << i - 1 << std::endl;
			//�����������̉��o�Ƃ��Ĉ�u�J������h�炷
			CAMERA->shakeCamera(0.1f, 0.1f);
			it->receiveDamage(attack);
			//�Ώۂ�hit��true�ɂ���
			//�Ώی���Ńq�b�g�X�g�b�v�������蓖���蔻����Ȃ�������
			//�����
			hits[i -1] = true;
		}
		
	}

	rotate_before_frame = rotate;
}
void Game::Weapon::LightSaber::Rotation1(ci::vec2 rotate_buf, float rotation)
{
	weapon_pos = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y + rotation), cos(rotate_buf.x + player_rotate_x))) / ci::vec3(10);

	weapon_vec = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y + rotation), cos(rotate_buf.x + player_rotate_x))) * ci::vec3(10) * ci::vec3(range);

	//�v���C���[�̈ʒu����ray��aabb�𐶐�
	ray[1].setOrigin(weapon_pos);
	ray[1].setDirection(weapon_vec);

	weapon_pos = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y - rotation), cos(rotate_buf.x + player_rotate_x))) / ci::vec3(10);

	weapon_vec = player_pos + glm::normalize(ci::vec3(sin(rotate_buf.x + player_rotate_x), sin(rotate_buf.y - rotation), cos(rotate_buf.x + player_rotate_x))) * ci::vec3(10) * ci::vec3(range);

	//�v���C���[�̈ʒu����ray��aabb�𐶐�
	ray[2].setOrigin(weapon_pos);
	ray[2].setDirection(weapon_vec);
}
using namespace Node::Action;
void Game::Weapon::LightSaber::Operation()
{
	
	if (!is_attack) {
		player_pos = cPlayerManager::getInstance()->getActivePlayer()->getPos();
		ray[0].setOrigin(player_pos);
		ray[0].setDirection(player_pos);
		
	}
	else {
		return;
	}

	if (push) {
		is_attack = true;
		light = Game::cLightManager::getInstance()->addPointLight(player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x))), ci::vec3(0.3f, 0.3f, 0.0f), 0.5f);

		//�v���C���[��pos��Vec��size���擾
		weapon_pos = cPlayerManager::getInstance()->getActivePlayer()->getPos();
		player_pos = cPlayerManager::getInstance()->getActivePlayer()->getPos();
		weapon_vec = cPlayerManager::getInstance()->getActivePlayer()->getPos();
		player_rotate_x = cPlayerManager::getInstance()->getActivePlayer()->getRotateY();
		player_rotate_y = cPlayerManager::getInstance()->getActivePlayer()->getRotateX();
		float time = 0.5f;

		root_x->set_schedule_update();
		root_x->run_action(Node::Action::sequence::create(
			ease<ci::EaseInOutAtan>::create(float_to::create(time, rotate.x, M_PI / 2, [this](float t) {
			this->rotate.x = t;
		})), Node::Action::call_func::create([this]() {
			this->rotate.x = -3*M_PI / 4;
			if (light != nullptr) {
				Game::cLightManager::getInstance()->removePointLight(light);
			}
		})
			));

		root_y->set_schedule_update();
		root_y->run_action(Node::Action::sequence::create(
			ease<ci::EaseInOutAtan>::create(float_to::create(time, rotate.y, -M_PI / 2, [this](float t) {
			this->rotate.y = t;
		})), Node::Action::call_func::create([this]() {
			//������
			this->rotate.y = M_PI / 2;
			is_attack = false;
			for (int i = 0; i < cPlayerManager::getInstance()->getPlayers().size();i++) {
				hits[i] = false;
			}
		})
			));
		rotate_before_frame = rotate;
	}
}

Game::Weapon::LightSaber::LightSaber()
{
	attack = 30;
	range = 2;
	player_rotate_x = 0;
	player_rotate_y = 0;
	is_attack = false;
	player_pos = ci::vec3(0);
	rotate = ci::vec2(-M_PI / 2, M_PI / 2);
	weapon_pos = ci::vec3(0);
	weapon_vec = ci::vec3(0);
	weapon_draw_pos = ci::vec3(0);
}

void Game::Weapon::LightSaber::setup()
{
	mesh = Resource::cObjectManager::getInstance()->findObject("montamogura/weapon.obj");
	TEX->set("weapon", "OBJ/montamogura/weapon.png");
	//����������Ԃ��v���C���[���Ƃɕێ����邽�߂�
	//�v���C���[�̌����v�b�V���o�b�N
	for (int i = 0; i < cPlayerManager::getInstance()->getPlayers().size();i++) {
		hits.push_back(false);
	}
	root_x = Node::node::create();
	root_x->set_schedule_update();
	root_y = Node::node::create();
	root_y->set_schedule_update();
}

void Game::Weapon::LightSaber::update(const float & delta_time)
{
	Operation();
	root_x->entry_update(delta_time);
	root_y->entry_update(delta_time);
	Attack(delta_time);
}

void Game::Weapon::LightSaber::draw()
{
	if (!is_attack) return;
	ci::gl::drawVector(ray[0].getOrigin(), ray[0].getDirection());
	//ci::gl::drawVector(ray[1].getOrigin(), ray[1].getDirection());
	//ci::gl::drawVector(ray[2].getOrigin(), ray[2].getDirection());
	ci::gl::ScopedTextureBind tex(TEX->get("weapon"));
	ci::gl::pushModelView();
	ci::gl::translate(weapon_draw_pos);
	ci::gl::rotate(M_PI / 2, ci::vec3(0, 1, 0));
	ci::gl::rotate(player_rotate_x, ci::vec3(0, 1, 0));
	ci::gl::rotate(-M_PI / 2, ci::vec3(0, 0, 1));
	ci::gl::rotate(-M_PI / 4, ci::vec3(0, 1, 0));
	ci::gl::rotate(M_PI / 2, ci::vec3(0, 0, 1));
	ci::gl::rotate(rotate.x, ci::vec3(0, 0, 1));

	ci::gl::scale(ci::vec3(0.02f, 0.02f, 0.02f));
	ci::gl::draw(mesh);
	ci::gl::popModelView();
}

#include <Game/Weapons/MainWeapon/LightSaber.h>
#include <cinder/gl/gl.h>
#include <Utility/cInput.h>
#include <CameraManager/cCameraManager.h>
#include <Resource/cObjectManager.h>
#include <Resource/TextureManager.h>
#include <Resource/cSoundManager.h>
#include <Game/cGemManager.h>
#include <Particle/cParticleManager.h>
#include <Game/cClientAdapter.h>
static float EasingLinear(float t, float b, float e) {
	return (e - b) * t + b;
}
using namespace Node::Action;
void Game::Weapon::LightSaber::Attack1()
{
	float time = motion1;
	root_x->set_schedule_update();
	root_x->run_action(Node::Action::sequence::create(
		ease<ci::EaseOutCubic>::create(float_to::create(time, rotate.x, M_PI / 2, [this](float t) {
		this->rotate.x = t;
	}))));

	root_y->set_schedule_update();
	
	root_y->run_action(Node::Action::sequence::create(
		ease<ci::EaseOutCubic>::create(float_to::create(time, rotate.y, -M_PI / 2, [this](float t) {
		this->rotate.y = t;
	}))));

}

void Game::Weapon::LightSaber::Attack2()
{
	float time = motion2;
	motion = Motion::attack_2;
	root_x->set_schedule_update();
	root_x->run_action(Node::Action::sequence::create(
		ease<ci::EaseOutCubic>::create(float_to::create(time, rotate.x, -M_PI / 2, [this](float t) {
		this->rotate.x = t;
	}))));

	rotate.y = 0;

}

void Game::Weapon::LightSaber::ShockCollisionPlayers()
{
	for (auto& it : cPlayerManager::getInstance()->getPlayers()) {		//�����̑��삵�Ă���v���C���[�Ȃ�Ԃ�
		
		if (it->getActiveUser()) {
			continue;
		}
		//�����̃`�[���̃v���C���[�Ȃ瓖����Ȃ��̂ŕԂ�
		if (it->getWhichTeam() == team) {
			continue;
		}
		//���ɓ������Ă�����Ԃ�
		if (hits[it->getPlayerId()]) {
			continue;
		}
		ci::vec3 shock_pos_buf_;
		bool is_hit = false;
		int split = 50;
		for (int k = 0; k < split; k++) {
			shock_pos_buf_.x = EasingLinear((float)k / split, shock_pos_buf.x, shock_pos.x);
			shock_pos_buf_.y = EasingLinear((float)k / split, shock_pos_buf.y, shock_pos.y);
			shock_pos_buf_.z = EasingLinear((float)k / split, shock_pos_buf.z, shock_pos.z);
			shock_aabb = ci::AxisAlignedBox(shock_pos_buf_ - ci::vec3(range / 4), shock_pos_buf_ + ci::vec3(range / 4));
			is_hit = shock_aabb.intersects(it->getAABB());
			if (is_hit) break;
		}
		if (is_hit) {
			CAMERA->shakeCamera(0.1f, 0.1f);
			if (charge_motion == ChargeMotion::charge_attack_1) {
				cClientAdapter::getInstance( )->sendDamage( it->getPlayerId( ), attack * 0.7F );
			}
			else if(charge_motion == ChargeMotion::charge_attack_2) {
				cClientAdapter::getInstance( )->sendDamage( it->getPlayerId( ), attack * 2.0F );
			}
			hits[it->getPlayerId()] = true;
		}
	}
}

void Game::Weapon::LightSaber::ShockCollisionDrills()
{
}

void Game::Weapon::LightSaber::CollisionPlayers()
{
	for (auto& it : cPlayerManager::getInstance()->getPlayers()) {
		
		//�����̑��삵�Ă���v���C���[�Ȃ�Ԃ�
		if (it->getActiveUser()) {
			continue;
		}
		//�����̃`�[���̃v���C���[�Ȃ瓖����Ȃ��̂ŕԂ�
		if (it->getWhichTeam() == team) {
			continue;
		}
		//���ɓ������Ă�����Ԃ�
		if (hits[it->getPlayerId()]) {
			continue;
		}
		//AABB�ɓ����ĂȂ���Δ��肵�Ȃ�
		if (!aabb.intersects(it->getAABB()))continue;

		//����������is_hit��true�ɂȂ�
		bool is_hit = false;
		ci::vec3 pos_buf_;
		int split = 50;
		for (int k = 0; k < split; k++) {
			pos_buf_.x = EasingLinear((float)k / split, player_buf_pos.x, weapon_draw_pos.x);
			pos_buf_.y = EasingLinear((float)k / split, player_buf_pos.y, weapon_draw_pos.y);
			pos_buf_.z = EasingLinear((float)k / split, player_buf_pos.z, weapon_draw_pos.z);
			shock_aabb = ci::AxisAlignedBox(pos_buf_ - ci::vec3(range / 4), pos_buf_ + ci::vec3(range / 4));
			is_hit = shock_aabb.intersects(it->getAABB());
			if (is_hit) break;
		}
		
		//�Ώۂ̃v���C���[��hit������
		if (is_hit) {
			//�����������̉��o�Ƃ��Ĉ�u�J������h�炷
			CAMERA->shakeCamera(0.1f, 0.1f);
			cClientAdapter::getInstance( )->sendDamage( it->getPlayerId(), attack );
			//�Ώۂ�hit��true�ɂ���
			//�Ώی���Ńq�b�g�X�g�b�v�������蓖���蔻����Ȃ�������
			//�����
			hits[it->getPlayerId()] = true;
		}
	}
}

void Game::Weapon::LightSaber::CollisionDrills()
{
}

void Game::Weapon::LightSaber::CollisionGems()
{
	for (auto& it : cGemManager::getInstance()->getGemStones()) {
		
		//���ɏ�������Ă�����Ԃ�
		if (!it->isActive()) {
			continue;
		}
		

		//AABB�ɓ����ĂȂ���Δ��肵�Ȃ�
		if (!it->getAabb().createAABB(it->getCenterPos()).intersects(aabb))continue;

		//����������is_hit��true�ɂȂ�
		bool is_hit = false;
		ci::vec3 pos_buf_;
		int split = 50;
		for (int k = 0; k < split; k++) {
			pos_buf_.x = EasingLinear((float)k / split, player_buf_pos.x, weapon_draw_pos.x);
			pos_buf_.y = EasingLinear((float)k / split, player_buf_pos.y, weapon_draw_pos.y);
			pos_buf_.z = EasingLinear((float)k / split, player_buf_pos.z, weapon_draw_pos.z);
			shock_aabb = ci::AxisAlignedBox(pos_buf_ - ci::vec3(range / 4), pos_buf_ + ci::vec3(range / 4));
			is_hit = shock_aabb.intersects(it->getAabb().createAABB(it->getCenterPos()));
			if (is_hit) break;
		}

		//�Ώۂ̃v���C���[��hit������
		if (is_hit) {
			//�����������̉��o�Ƃ��Ĉ�u�J������h�炷
			CAMERA->shakeCamera(0.1f, 0.1f);
			cGemManager::getInstance()->breakGemStone(it->getId());
		}

	}
}

void Game::Weapon::LightSaber::Attack(const float & delta_time)
{
	if (charge_is_attack) {
		if (light != nullptr) {
			light->color = ci::vec3(shock_wave_time, shock_wave_time, 0);
			light->reAttachPositionWithRadius(weapon_draw_pos, shock_wave_time);
		}
		weapon_draw_pos = player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x)));
	}
	else {
		if (is_attack) {
			if (light != nullptr) {
				light->color = ci::vec3(0.5f, 0.5f, 0);
				light->reAttachPositionWithRadius(weapon_draw_pos, 2);
			}
		}
	}
	
	if (!is_attack)return;
	weapon_draw_pos = player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x)));
	aabb = ci::AxisAlignedBox(weapon_draw_pos - ci::vec3(range / 2), weapon_draw_pos + ci::vec3(range / 2));
	CollisionPlayers();
	CollisionDrills();
	CollisionGems();
	if (charge_is_attack_now) {
		if (charge_light != nullptr) {
			charge_light->color = ci::vec3(1, 1, 0);
			charge_light->reAttachPositionWithRadius(shock_pos, 2);
		}
		ShockCollisionPlayers();
	}
	else {
		shock_aabb = ci::AxisAlignedBox(shock_pos, shock_pos);
	}
	player_buf_pos = weapon_draw_pos;
	rotate_before_frame = rotate;
	shock_pos_buf = shock_pos;
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

void Game::Weapon::LightSaber::Operation(const float & delta_time)
{
	//�v���C���[��pos��Vec��size���擾
	weapon_pos = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
	player_pos = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
	weapon_vec = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
	player_rotate_x = cPlayerManager::getInstance()->getPlayer(player_id)->getRotateY();
	player_rotate_y = cPlayerManager::getInstance()->getPlayer(player_id)->getRotateX();
	
	if (push) {
		is_push = true;
	}
	if (pull) {
		is_push = false;;
	}

	if (!is_attack) {
		//������
		if (light != nullptr) {
			light->reAttachPositionWithRadius(weapon_draw_pos, 0);
		}
		player_pos = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
		ray[0].setOrigin(player_pos);
		ray[0].setDirection(player_pos);

	}
	else if(charge_is_attack) {
		;
	}
	else {
		return;
	}

	if (is_push) {
		if (light == nullptr) {
			light = Game::cLightManager::getInstance()->addPointLight(player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x))), ci::vec3(0.5f, 0.5f, 0.0f), 0.5f);
		}
		rotate = ci::vec2(-M_PI / 2, M_PI / 2);
		charge_is_attack = true;
	}
	

	//�P�i�K�ڏՌ���
	if (pull &&
		charge_flag1 &&
		shock_wave_time < shock_wave_second) {
		is_push = false;
		charge_motion = ChargeMotion::charge_attack_1;
		charge_is_attack_now = true;
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").stop();
		Resource::cSoundManager::getInstance()->findSe("Player/swing2.wav").stop();
		Resource::cSoundManager::getInstance()->findSe("Player/katana-slash5.wav").setGain(0.2f);
		Resource::cSoundManager::getInstance()->findSe("Player/katana-slash5.wav").play();
		charge_flag1 = false;
		charge_flag2 = false;
		charge_is_attack = false;
		shock_wave_time = 0;
		if (charge_light == nullptr) {
			charge_light = Game::cLightManager::getInstance()->addPointLight(player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x))), ci::vec3(0.5f, 0.5f, 0.0f), 0.5f);
		}

		root_shock->set_schedule_update();
		root_shock->set_position_3d(cPlayerManager::getInstance()->getPlayer(player_id)->getPos());
		shock_pos = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
		player_vec = cPlayerManager::getInstance()->getPlayer(player_id)->getPlayerVec();
		
		
		root_shock->run_action(Node::Action::sequence::create(
			Node::Action::move_to::create(0.5f, shock_pos + ci::vec3(player_vec.x, 0, player_vec.z)* range * ci::vec3(8)),
			Node::Action::call_func::create([this]() {
			//������
			this->charge_is_attack_now = false;
			if (light != nullptr) {
				charge_light->reAttachPositionWithRadius(weapon_draw_pos, 0);
			}
		})));

		for (auto it : cPlayerManager::getInstance()->getPlayers()) {
			hits[it->getPlayerId()] = false;
		}
		shock_pos_buf = shock_pos;
	}

	//2�i�K�ڏՌ���
	if (pull &&
		shock_wave_time >= shock_wave_second) {
		is_push = false;
		charge_motion = ChargeMotion::charge_attack_2;
		charge_is_attack_now = true;
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").stop();
		Resource::cSoundManager::getInstance()->findSe("Player/swing2.wav").stop();
		Resource::cSoundManager::getInstance()->findSe("Player/iainuki1.wav").setGain(0.2f);
		Resource::cSoundManager::getInstance()->findSe("Player/iainuki1.wav").play();
		charge_flag1 = false;
		charge_flag2 = false;
		charge_is_attack = false;
		shock_wave_time = 0;
		if (charge_light == nullptr) {
			charge_light = Game::cLightManager::getInstance()->addPointLight(player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x))), ci::vec3(0.5f, 0.5f, 0.0f), 0.5f);
		}
		root_shock->set_position_3d(cPlayerManager::getInstance()->getPlayer(player_id)->getPos());
		root_shock->set_schedule_update();
		shock_pos = cPlayerManager::getInstance()->getPlayer(player_id)->getPos();
		player_vec = cPlayerManager::getInstance()->getPlayer(player_id)->getPlayerVec();
		root_shock->run_action(Node::Action::sequence::create(
			Node::Action::move_to::create(0.5f, shock_pos + ci::vec3(player_vec.x, 0, player_vec.z)* range * ci::vec3(16)),
			Node::Action::call_func::create([this]() {
			//������
			this->charge_is_attack_now = false;
			if (light != nullptr) {
				charge_light->reAttachPositionWithRadius(weapon_draw_pos, 0);
			}
		})));

		for (auto it : cPlayerManager::getInstance()->getPlayers()) {
			hits[it->getPlayerId()] = false;
		}
		shock_pos_buf = shock_pos;
	}

	//�Ђ���������
	if (pull) {
		is_push = false;
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").stop();
		charge_flag1 = false;
		charge_flag2 = false;
		charge_is_attack = false;
		shock_wave_time = 0;
		Resource::cSoundManager::getInstance()->findSe("Player/swing2.wav").setGain(0.2f);
		Resource::cSoundManager::getInstance()->findSe("Player/swing2.wav").play();
		if (light == nullptr) {
			charge_light = Game::cLightManager::getInstance()->addPointLight(player_pos + glm::normalize(ci::vec3(sin(rotate.x + player_rotate_x), sin(rotate.y), cos(rotate.x + player_rotate_x))), ci::vec3(0.5f, 0.5f, 0.0f), 0.5f);
		}
		
		
		
		if (motion == Motion::attack_2) {
			rotate = ci::vec2(-M_PI / 2, M_PI / 2);
			Attack1();
			motion = Motion::attack_1;
			is_attack = true;
			for (auto it : cPlayerManager::getInstance()->getPlayers()) {
				hits[it->getPlayerId()] = false;
			}
			timer = 0;
		}

		if (timer > 0.3f && timer <= 1 && motion == Motion::attack_1) {
			rotate = ci::vec2(2*M_PI / 3, 0);
			Attack2();
			motion = Motion::attack_2;
			timer = 0;
			for (auto it : cPlayerManager::getInstance()->getPlayers()) {
				hits[it->getPlayerId()] = false;
			}
			is_attack = true;
		}
		rotate_before_frame = rotate;
	}
	//���߂�p�[�e�B�N���P
	if (shock_wave_time >= shock_wave_first / 2 &&
		charge_flag1 == false) {
		charge_flag1 = true;
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").setGain(0.2f);
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").setLooping(true);
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").play();
		/*Particle::cParticleManager::getInstance()->create(Particle::ParticleParam().position(weapon_pos)
			.scale(0.3f).
			vanishTime(0.5f).
			speed(1.0f).
			textureType(Particle::ParticleTextureType::SPARK).
			color(ci::ColorA::white()).
			moveType(Particle::ParticleType::CONVERGE).count(10).isTrajectory(false));*/
	}
	//���߂�p�[�e�B�N���Q
	if (shock_wave_time >= shock_wave_second &&
		charge_flag2 == false) {
		charge_flag2 = true;
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").setGain(0.2f);
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").setLooping(true);
		Resource::cSoundManager::getInstance()->findSe("Player/aura1.wav").play();
		/*Particle::cParticleManager::getInstance()->create(Particle::ParticleParam().position(weapon_pos)
			.scale(0.3f).
			vanishTime(1.0f).
			speed(1.0f).
			textureType(Particle::ParticleTextureType::SPARK).
			color(ci::ColorA::white()).
			moveType(Particle::ParticleType::CONVERGE).count(1).isTrajectory(false));*/
	}
	
}


Game::Weapon::LightSaber::LightSaber(int player_id)
{
	push = false;
	press = false;
	pull = false;
	attack = 40;
	range = 2;
	player_rotate_x = 0;
	player_rotate_y = 0;
	is_attack = false;
	is_push = false;
	player_pos = ci::vec3(0);
	rotate = ci::vec2(-M_PI / 2, M_PI / 2);
	timer = 0;
	this->player_id = player_id;
	player_buf_pos = ci::vec3(0);
	weapon_pos = ci::vec3(0);
	weapon_vec = ci::vec3(0);
	weapon_draw_pos = ci::vec3(0);
	shock_pos = ci::vec3(0);
	player_vec = ci::vec3(0);
	motion = Motion::attack_2;
	charge_motion = ChargeMotion::charge_attack_1;
	shock_wave_time = 0;
}

void Game::Weapon::LightSaber::setup()
{
	mesh = Resource::cObjectManager::getInstance()->findObject("montamogura/weapon.obj");
	TEX->set("weapon", "OBJ/montamogura/weapon.png");
	//����������Ԃ��v���C���[���Ƃɕێ����邽�߂�
	//�v���C���[�̌����v�b�V���o�b�N
	for (auto it : cPlayerManager::getInstance()->getPlayers()) {
		hits[it->getPlayerId()] = false;
	}
	team = cPlayerManager::getInstance()->getPlayer(player_id)->getWhichTeam();
	root_x = Node::node::create();
	root_x->set_schedule_update();
	root_y = Node::node::create();
	root_y->set_schedule_update();
	root_shock = Node::node::create();
	root_shock->set_schedule_update();
	root_shock->set_position_3d(cPlayerManager::getInstance()->getPlayer(player_id)->getPos());
}

void Game::Weapon::LightSaber::update(const float & delta_time)
{
	timer += delta_time;
	
	if (timer > motion1) {
		is_attack = false;
	}
	if (timer > 1) {
		motion = Motion::attack_2;
	}
	Operation(delta_time);

	if (charge_is_attack) {
		shock_wave_time += delta_time;
		if (shock_wave_time > 2.1f) {
			shock_wave_time = 2.1f;
		}
	}

	if (shock_wave_time <= shock_wave_first) {
		shock_pos = root_shock->get_position_3d();
	}
	cPlayerManager::getInstance()->getPlayer(player_id)->setStan(is_attack);
	root_shock->entry_update(delta_time);
	root_x->entry_update(delta_time);
	root_y->entry_update(delta_time);
	Attack(delta_time);
}

void Game::Weapon::LightSaber::DrawRotate1()
{
	if (motion == Motion::attack_1) {
		ci::gl::translate(weapon_draw_pos);
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 1, 0));
		ci::gl::rotate(player_rotate_x, ci::vec3(0, 1, 0));
		ci::gl::rotate(-M_PI / 2, ci::vec3(0, 0, 1));
		ci::gl::rotate(-M_PI / 4, ci::vec3(0, 1, 0));
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 0, 1));
		ci::gl::rotate(rotate.x, ci::vec3(0, 0, 1));
	}
}

void Game::Weapon::LightSaber::DrawRotate2()
{
	if (motion == Motion::attack_2) {
		ci::gl::translate(weapon_draw_pos);
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 1, 0));
		ci::gl::rotate(player_rotate_x, ci::vec3(0, 1, 0));
		ci::gl::rotate(-M_PI / 2, ci::vec3(0, 0, 1));
		ci::gl::rotate(M_PI / 4, ci::vec3(0, 1, 0));
		ci::gl::rotate(-rotate.x + M_PI / 2, ci::vec3(0, 0, 1));
	}
}

void Game::Weapon::LightSaber::DrawRotate3()
{
	if (motion == Motion::attack_2) {
		ci::gl::translate(weapon_draw_pos);
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 1, 0));
		ci::gl::rotate(player_rotate_x, ci::vec3(0, 1, 0));
		ci::gl::rotate(-M_PI / 2, ci::vec3(0, 0, 1));
		ci::gl::rotate(-M_PI / 4, ci::vec3(0, 1, 0));
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 0, 1));
		ci::gl::rotate(rotate.x, ci::vec3(0, 0, 1));
	}
}
void Game::Weapon::LightSaber::draw()
{
	if (charge_is_attack) {
		ci::gl::pushModelView();
		DrawRotate3();
		ci::gl::scale(ci::vec3(0.02f, 0.02f, 0.02f));
		ci::gl::draw(mesh);
		ci::gl::popModelView();
	}
	if (!is_attack) return;
	if (charge_is_attack_now) {
		ci::gl::drawStrokedCube(aabb);
		ci::gl::pushModelView();
		ci::gl::translate(shock_pos);
		ci::gl::rotate(M_PI / 2, ci::vec3(0, 1, 0));
		ci::gl::rotate(player_rotate_x, ci::vec3(0, 1, 0));
		ci::gl::rotate(-M_PI / 2, ci::vec3(0, 0, 1));
		if (charge_motion == ChargeMotion::charge_attack_1) {
			ci::gl::scale(ci::vec3(0.03f, 0.03f, 0.03f));
		}else if (charge_motion == ChargeMotion::charge_attack_2) {
			ci::gl::scale(ci::vec3(0.05f, 0.05f, 0.05f));
		}
		ci::gl::draw(mesh);
		ci::gl::popModelView();
	}
	//ci::gl::drawVector(ray[0].getOrigin(), ray[0].getDirection());
	//ci::gl::drawVector(ray[1].getOrigin(), ray[1].getDirection());
	//ci::gl::drawVector(ray[2].getOrigin(), ray[2].getDirection());
	ci::gl::ScopedTextureBind tex(TEX->get("weapon"));
	ci::gl::pushModelView();
	DrawRotate1();
	DrawRotate2();
	ci::gl::scale(ci::vec3(0.02f, 0.02f, 0.02f));
	ci::gl::draw(mesh);
	ci::gl::popModelView();
}

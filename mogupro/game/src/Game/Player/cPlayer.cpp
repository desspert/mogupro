#include <Game/Player/cPlayer.h>
#include <Collision/cAABBCollider.h>
#include <Game/cFieldManager.h>
#include <CameraManager/cCameraManager.h>
#include <Resource/cObjectManager.h>
#include <Resource/TextureManager.h>
//void Game::Player::cPlayer::playerRotation()
//{
//	//�v���C���[�̑O����
//	ci::vec3 rotateaxis = ci::vec3(0.0f, 0.0f, 1.0f);
//	//�ړ���̃x�N�g��
//	ci::vec3 targetvec = ci::vec3(velocity.x, 0, velocity.z);
//	//�ړ�������normalize
//	targetvec = ci::normalize(targetvec);
//	//��]��
//	ci::vec3 quataxis = glm::cross(rotateaxis, targetvec);
//	//��]
//	// �����
//	if (atan2f(velocity.x, velocity.z) > 0.0f)
//		ci::gl::rotate(atan2f(velocity.x, velocity.z), quataxis);
//	// �E���
//	else if (atan2f(velocity.x, velocity.z) < 0.0f)
//		ci::gl::rotate(-atan2f(velocity.x, velocity.z), quataxis);
//
//	if (quataxis == ci::vec3(0))
//	{
//		if (velocity.z > 0.0f)
//			ci::gl::rotate(0, ci::vec3(0, 1, 0));
//		if (velocity.z < 0.0f)
//			ci::gl::rotate((float)M_PI, ci::vec3(0, 1, 0));
//	}
//
//}

void Game::Player::cPlayer::playerRotation()
{
	//�v���C���[�̑O����
	ci::vec3 rotateaxis = ci::vec3(0.0f, 0.0f, 1.0f);
	//�ړ���̃x�N�g��
	ci::vec3 targetvec = ci::vec3(velocity.x, 0, velocity.z);
	//�ړ�������normalize
	targetvec = ci::normalize(targetvec);

	//��]��
	ci::vec3 quataxis = glm::cross(rotateaxis, targetvec);

	float rotation = atan2f(velocity.x, velocity.z);

	//��]
	// �����
	if (rotation > 0.1f) {
		ci::gl::rotate(rotation, quataxis);
		save_rotate = rotation;
	}
	// �E���
	else if (rotation < -0.1f) {
		ci::gl::rotate(-rotation, quataxis);
		save_rotate = rotation;
	}

	//�x�N�g�����o�Ȃ����
	if (rotation <= 0.1f &&
		rotation >= -0.1f) {
		if (save_rotate > 0.1f)
			ci::gl::rotate(save_rotate, ci::vec3(0, 1, 0));
		if (save_rotate < -0.1f)
			ci::gl::rotate(save_rotate, ci::vec3(0, 1, 0));
	}

}


//�R���X�g���N�^��
//�ʒu�Ɗp�x�Ɖ�P���Ƃǂꂪ�����̃v���C���[����
//���炤
Game::Player::cPlayer::cPlayer(
	const ci::vec3& pos,
	const ci::vec3& center_angle,
	const int& id,
	const bool& is_active_user)
	: cObjectBase(pos),
	mCollider(mPos, ci::vec3(1.5, 2.3, 1.5)),
	mRigidbody(mCollider)
{
	size = ci::vec3(1);
	color = ci::vec4(1);
	color = ci::ColorA8u(1, 0, 1, 1);
	velocity = ci::vec3(0);
	save_rotate = 0;
	drilling = false;
	speed = DEFAULT_SPEED;
	player_id = id;
	active_user = is_active_user;
}

void Game::Player::cPlayer::move(const ci::vec3 & velocity)
{

	auto speed = mRigidbody.getSpeed() - this->velocity;

	//�v���C���[�̈ړ��x�N�g���ۑ�
	this->velocity = velocity;

	mRigidbody.setSpeed(ci::vec3(0,speed.y,0) + velocity);
	//�v���C���[�̈ړ�
	mPos = mCollider.getPosition();

}

void Game::Player::cPlayer::setup()
{
	mCollider.addWorld();
	mRigidbody.addWorld();
	
	mesh = Resource::cObjectManager::getInstance()->findObject("montamogura/moguraHontai.obj");
	TEX->set("mogura", "OBJ/montamogura/moguraHontai.png");
}

void Game::Player::cPlayer::update(const float & delta_time)
{
	if (drilling) {
		Game::cFieldManager::getInstance()->blockBreak(mPos, 3);
	}
	/*mPos = mCollider.getPosition();
	size = mCollider.getSize();*/
}

void Game::Player::cPlayer::draw()
{
	ci::gl::pushModelView();
	ci::gl::translate(mPos - ci::vec3(0, 1, 0));
	ci::gl::scale(ci::vec3(0.02f) + ci::vec3(0.01f, 0, 0.01f));
	playerRotation();
	ci::gl::color(color);
	TEX->get("mogura")->bind();
	ci::gl::ScopedGlslProg sgp(ci::gl::getStockShader(ci::gl::ShaderDef().texture()));
	ci::gl::draw(mesh);
	Resource::TextureManager::getInstance()->get("mogura")->unbind();
	ci::gl::color(1, 1, 1, 1);
	ci::gl::popModelView();
}

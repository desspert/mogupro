#include <Game/Player/cPlayer.h>
#include <Collision/cAABBCollider.h>
#include <Game/cFieldManager.h>
#include <CameraManager/cCameraManager.h>
#include <Resource/cObjectManager.h>
#include <Resource/TextureManager.h>


void Game::Player::cPlayer::playerRotation()
{
	//�v���C���[�̑O����
	ci::vec3 rotateaxis = ci::vec3(0.0f, 0.0f, 1.0f);
	//�ړ���̃x�N�g��
	ci::vec3 targetvec = ci::vec3(velocity.x, 0, velocity.z);
	//�ړ�������normalize
	targetvec = ci::normalize(targetvec);
	if (velocity.x >= 0.01f ||
		velocity.x <= -0.01f ||
		velocity.z >= 0.01f ||
		velocity.z <= -0.01f )
		installation_position = ci::vec3(velocity.x * 10, 0, velocity.z * 10);

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
	jump_flag = false;

	//�v���C���[�̃X�e�[�^�X
	status.attack = 10;
	status.drill_range = 1;
	status.jump_force = 1;
	status.speed = DEFAULT_SPEED;
	//�ݒu�ʒu
	installation_position = ci::vec3(0,0,2);

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

void Game::Player::cPlayer::jump(bool flag)
{
	if(jump_flag == false)
	jump_flag = flag;

	if (jump_flag == true) {
		if (mRigidbody.isLanding()) {
			velocity.y = -(status.jump_force/6);
			jump_flag = false;
		}
	}
}

void Game::Player::cPlayer::setup()
{
	mCollider.addWorld();
	mRigidbody.addWorld();
	
	mesh = Resource::cObjectManager::getInstance()->findObject("montamogura/moguraHontai.obj");
	TEX->set("mogura", "OBJ/montamogura/moguraHontai.png");
}

#include <Game/cClientAdapter.h>
void Game::Player::cPlayer::update(const float & delta_time)
{
	if (drilling) {
		Game::cFieldManager::getInstance()->blockBreak(mCollider.getPosition() + ci::vec3(0,-2,0), 2);
	}
    cClientAdapter::getInstance( )->sendPlayerFormat( mPos, cinder::quat() );
}

void Game::Player::cPlayer::draw()
{
	ci::gl::pushModelView();
	ci::gl::translate(mPos - ci::vec3(0, 1, 0));
	ci::gl::scale(ci::vec3(0.01f) + ci::vec3(0.01f, 0, 0.01f));
	playerRotation();
	ci::gl::color(color);
	TEX->get("mogura")->bind();
	ci::gl::ScopedGlslProg sgp(ci::gl::getStockShader(ci::gl::ShaderDef().texture()));
	ci::gl::draw(mesh);
	Resource::TextureManager::getInstance()->get("mogura")->unbind();
	ci::gl::color(1, 1, 1, 1);
	ci::gl::popModelView();
}

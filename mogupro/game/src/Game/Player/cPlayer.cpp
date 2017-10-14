#include <Game/Player/cPlayer.h>

//�R���X�g���N�^��
//�ʒu�Ɗp�x�Ɖ�P���Ƃǂꂪ�����̃v���C���[����
//���炤
Game::Player::cPlayer::cPlayer(
	const ci::vec3& pos,
	const ci::vec3& center_angle,
	const int& id,
	const bool& is_active_user)
	: cObjectBase(pos)
{
	size = ci::vec3(1);
	speed = 0.5f;
	this->center_angle = center_angle;
	player_id = id;
	active_user = is_active_user;
}

void Game::Player::cPlayer::setup()
{
}

void Game::Player::cPlayer::update(const float & delta_time)
{

}

void Game::Player::cPlayer::draw()
{
	
	auto lambert = ci::gl::ShaderDef().lambert();
	auto shader = ci::gl::getStockShader(lambert);
	shader->bind();
	ci::gl::drawCube(mPos, size);
	
}

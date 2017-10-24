#pragma once
#include <Utility/cSingletonAble.h>
#include <Game/Player/cPlayer.h>
namespace Game
{
	
class cPlayerManager : public ::Utility::cSingletonAble<cPlayerManager>
{
private:
    //�S�v���C���[���X�g
    std::vector<std::shared_ptr<Player::cPlayer>> players;
    //���������삷��v���C���[
    std::shared_ptr<Player::cPlayer> active_player;

    bool mouse_on = false;
    void playerInstance();
    void playerNormalMove(const float& delta_time);
	void playerDrillMove(const float& delta_time);
	void playerMove(const float& delta_time);
	void padMove(const float & delta_time);
public:
	
	//�v���C���[�N���X���C���N���[�h���ĉ�����
	//#include <Game/Player/cPlayer.h>
	std::vector<std::shared_ptr<Player::cPlayer>> getPlayers() {
		return players;
	}
    void setup();
    void update( const float& delta_time );
    void draw();
};
}

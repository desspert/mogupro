#pragma once
#include<Game/Weapons/SubWeapon/SubWeaponType.h>
#include<vector>
namespace Game
{
namespace Weapons
{
namespace UseSubWeapon
{
class cUseSubWeapon
{
public:
    cUseSubWeapon( );
    ~cUseSubWeapon( );
	void setup();
	///�T�u�E�F�|�����g��(�悩��g��)
	void useWeapon(const int playerid);
	///�T�u�E�F�|����ǉ�
	void addSubWeapon(const Game::Weapons::SubWeapon::SubWeaponType type);
	void setCanUseWeapon(const bool iscanuse);
	int getItemNum();
private:
	//�����Ă���T�u�̎��
	std::vector<Game::Weapons::SubWeapon::SubWeaponType> mSubWeaponTypes;
	//���݃T�u���g���邩�i�� �d�����Ȃǁj
	bool mIsCanUse = true;
};
}
}
}

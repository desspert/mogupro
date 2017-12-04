#include <Game/cSubWeaponManager.h>
#include <Game/Weapons/SubWeapon/cLightBomb.h>
#include <Game/Weapons/UseSubWeapon/cUseLightBomb.h>
#include <Game/Weapons/UseSubWeapon/cUseQuarry.h>

namespace Game
{
cSubWeaponManager::cSubWeaponManager( )
{

}
cSubWeaponManager::~cSubWeaponManager( )
{

}
void cSubWeaponManager::setup()
{
	cPlayerManager::getInstance()->getActivePlayer()->useSubWeapon.addSubWeapon(Game::Weapons::SubWeapon::SubWeaponType::QUARRY);
}
void cSubWeaponManager::draw()
{
	for (auto itr : usesubweapons) {
		itr->draw();
	}
	for (auto itr : subweapons) {
		itr.second->draw();
	}
}
void cSubWeaponManager::update(const float & deltatime)
{
	for (auto& itr : usesubweapons) {
		itr->update(deltatime);
	}
	for (auto& itr : subweapons) {
		itr.second->update(deltatime);
	}
	deleteWeapons();
}
void cSubWeaponManager::updateCollisionAfterUpdate(const float & deltaTime)
{
	for (auto& itr : subweapons) {
		itr.second->updateCollisionAfterUpdate(deltaTime);
	}
}

void cSubWeaponManager::HitDrillToGem(const int _objectid, const int _gemid)
{
	auto quarry = std::static_pointer_cast<Game::Weapons::SubWeapon::cQuarry>(subweapons[_objectid]);

	quarry->HitGem(_gemid);
}

void cSubWeaponManager::drawCube(const ci::vec3 pos, const ci::vec3 size, const ci::vec3 rotate, const ci::ColorA color)
{

}
void cSubWeaponManager::createLightBomb(const ci::vec3 _pos, const ci::vec3 _speed, const ci::vec3 _scale, const int objectid, const int _playerid)
{
	subweapons.insert(std::make_pair(objectid, std::make_shared<Game::Weapons::SubWeapon::cLightBomb>(_pos, _scale, _speed, _playerid)));
	subweapons[objectid]->setup();
	debugidcount++;
}

void cSubWeaponManager::createQuarry(const ci::vec3 _pos, const int _objectid, const int playerid)
{
	subweapons.insert(std::make_pair(_objectid, std::make_shared<Game::Weapons::SubWeapon::cQuarry>(_pos, _objectid, playerid)));
	subweapons[_objectid]->setup();
	debugidcount++;
}

void cSubWeaponManager::createUseSubWeapon(const Game::Weapons::SubWeapon::SubWeaponType type, const int playerid)
{
	switch (type)
	{
	case Game::Weapons::SubWeapon::SubWeaponType::LIGHT_BOMB:
		usesubweapons.push_back(std::make_shared<Game::Weapons::UseSubWeapon::cUseLightBomb>());
		usesubweapons.back()->setup(playerid);
		return;
	case Game::Weapons::SubWeapon::SubWeaponType::QUARRY:
		usesubweapons.push_back(std::make_shared<Game::Weapons::UseSubWeapon::cUseQuarry>());
		usesubweapons.back()->setup(playerid);
		return;
	default:
		return;
	}
}
void cSubWeaponManager::deleteWeapons()
{
	for (auto itr = usesubweapons.begin();
		itr != usesubweapons.end();) {
		if ((*itr)->deleteThis()) {
			itr = usesubweapons.erase(itr);
		}
		else {
			itr++;
		}
	}

	for (auto itr = subweapons.begin();
		itr != subweapons.end();) {
		if (itr->second->deleteThis()) {
			itr = subweapons.erase(itr);
		}
		else {
			itr++;
		}
	}
}
}

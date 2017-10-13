#pragma once
#include "cinder/Rand.h"
#include "cGem.h"
#include "../include/Utility/cSingletonAble.h"
#include <vector>
#include <map>
#define GemManager Game::Gem::cGemManager::getInstance()

using namespace std;

namespace Game
{
	namespace Gem
	{
		
		class cGemManager : public Utility::cSingletonAble<cGemManager>
		{
		public:

			cGemManager() {}
			~cGemManager() {}
			// position           ���S���W(��l)   x,y,z�S��+�����Ƀ}�b�v�`�b�v�Ő������܂��B
			// randomRange        �����_���̐����͈�(�Е��w�n�̃}�b�v�T�C�Y)
			// mapChipSize        �}�b�v�`�b�v��}�X�̑傫��
			// gemMaxNum          gem�̐�����
			// seed               �V�[�h�l(���݂͓��͂��Ă��ϓ��Ȃ�)
			void setUp(vec3 position, vec3 randomRange, float mapChipSize, int gemMaxNum, unsigned long seed);
			void draw();
			void update();

			void create();
			// team     0��first,1��second
			void gemCountUp(int team, int it);
			void gemDelete(int it);

			vector<cGem> getGems() { return mGems; }

		private:

			vector<cGem> mGems;
			map<GemType, int> mTeamGems[2];
			vec3 mPosition;
			vec3 mRandomRange;
			float mMapChipSize;
			int mGemMaxNum;
			unsigned long mSeed;
		};
	}
}
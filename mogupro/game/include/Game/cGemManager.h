#pragma once
#include "Game/Gem/cGem.h"
#include "Utility/cSingletonAble.h"
#include "cinder\/Surface.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Context.h"
#include "cinder/gl/Texture.h"
#include "CameraManager\cCameraManager.h"
#include "Utility\cTimeMeasurement.h"
#include <Utility/cSingletonAble.h>
#include <memory>
#include <cinder/Rand.h>
#include <cinder/gl/Fbo.h>
#include <cinder/gl/GlslProg.h>
#include <cinder/gl/Texture.h>
#include <vector>
#include <map>
#define GemManager Game::cGemManager::getInstance()


namespace Game
{
	class cGemManager : public Utility::cSingletonAble<cGemManager>
	{
	public:

		cGemManager() {}
		~cGemManager() {}
		// position           ���S���W(��l)   x,y,z�S��+�����Ƀ}�b�v�`�b�v�Ő������܂��B
		// randomRange        �����_���̐����͈�(�Е��w�n�̃}�b�v�T�C�Y)
		// mapChipSize        �}�b�v�`�b�v��}�X�̑傫��
		// gemScale           �W�F����̑傫��
		// gemMaxNum          gem�̐�����
		// seed               �V�[�h�l(���݂͓��͂��Ă��ϓ��Ȃ�)
		void setUp(ci::vec3 position, ci::vec3 randomRange, float mapChipSize, float gemScale, int gemMaxNum, unsigned long seed);
		void draw();
		void drawFbo();
		void update();

		void create();
		// team     0��first,1��second
		void gemCountUp(int team, Gem::GemType type);
		void gemDelete(int it);
		std::vector<std::shared_ptr<Gem::cGem>> getGems() { return mGemsptr; }
		std::shared_ptr<Gem::cGem> FindGem(int id);

	private:

		std::vector<std::shared_ptr<Gem::cGem>> mGemsptr;
		std::map<Gem::GemType, int> mTeamGems[2];
		ci::vec3 mPosition;
		ci::vec3 mRandomRange;
		float mMapChipSize;
		float mGemScale;
		int mGemMaxNum;
		ci::gl::FboRef mGemBuffer;
		ci::gl::GlslProgRef mHShader;
		ci::gl::GlslProgRef mVShader;
		ci::gl::BatchRef batch;
		float blurSize;
		float mBloom;
		unsigned long mSeed;
	};
}
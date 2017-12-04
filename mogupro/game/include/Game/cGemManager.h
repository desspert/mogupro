#pragma once
#include "Game/Gem/cGemStone.h"
#include "Utility/cSingletonAble.h"
#include "cinder\/Surface.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Context.h"
#include "cinder/gl/Texture.h"
#include "CameraManager\cCameraManager.h"
#include "Utility\cTimeMeasurement.h"
#include "cPlayerManager.h"
#include "Game/Gem/cFragmentGem.h"
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
		void      setUp(ci::vec3 position, ci::vec3 randomRange, float mapChipSize, float gemScale, int gemMaxNum, unsigned long seed);
		void      draw();
		void      drawFbo();
		void      update(float deltaTime);
		void      lateUpdate(const float& delta_time);

		void      create();
		void      buildMesh();
		void      clearMesh();

		std::vector<std::shared_ptr<Gem::cGemStone>>         getGemStones()          { return mGemStone; }
		std::vector<std::shared_ptr<Gem::cFragmentGem>>      getFragmentGems()       { return mFragmentGems; }
		std::shared_ptr<Gem::cGemStone>                      getGemStone(int id);
		std::shared_ptr<Gem::cGemStone>                      breakeGemStone(int id);
		std::shared_ptr<Gem::cFragmentGem>                   getFragmentGem(int id);
		void  AcquisitionFragmentGem(int id);

	private:


		const int mDrawNum = 100;

		std::vector<std::shared_ptr<Gem::cGemStone>>      mGemStone;
		std::vector<std::shared_ptr<Gem::cFragmentGem>>   mFragmentGems;

		ci::vec3             mPosition;
		ci::vec3             mRandomRange;
		float                mMapChipSize;
		float                mGemScale;
		int                  mGemMaxNum;
		ci::gl::FboRef       mGemBuffer;
		ci::gl::GlslProgRef  mShader;
		ci::gl::GlslProgRef  mVboShader;
		ci::TriMeshRef       mesh;
		ci::gl::VboMeshRef   mGemsVbo;
		unsigned long        mSeed;
		float                mTime;
		float                mLightingSpeed;
		//ci::gl::GlslProgRef mHShader;
		//ci::gl::GlslProgRef mVShader;
	};
}
#include <Game/cGemManager.h>
#include <Game/cPlayerManager.h>
#include <Utility/cTimeMeasurement.h>
#include <CameraManager/cCameraManager.h>
#include <cinder/Rand.h>
#include <Resource\cSoundManager.h>
#include <Game/Field/FieldData.h>
#include <Game/cGameManager.h>
#include <Sound/Stereophonic.h>
namespace Game
{

	void cGemManager::setUp(ci::vec3 position, ci::vec3 randomRange, float mapChipSize, float gemScale, int gemMaxNum, unsigned long seed)
	{
		mPosition       = position;
		mRandomRange    = randomRange;
		mMapChipSize    = mapChipSize;
		mGemScale       = gemScale;
		mGemMaxNum      = gemMaxNum;
		mSeed           = seed;
		mTime           = 0.0f;
		mLightingSpeed  = 0.4f;

		mGemBuffer     = ci::gl::Fbo::create(ci::app::getWindowWidth(), ci::app::getWindowHeight(), true);
		mShader        = ci::gl::GlslProg::create(ci::app::loadAsset("Gem/GemManager.vert"), ci::app::loadAsset("Gem/GemManager.frag"));
		mVboShader     = ci::gl::GlslProg::create(ci::app::loadAsset("Gem/GemVbo.vert"), ci::app::loadAsset("Gem/GemVbo.frag"));
		mFragGemShader = ci::gl::GlslProg::create(ci::app::loadAsset("Gem/FragGem.vert"), ci::app::loadAsset("Gem/FragGem.frag"));

		mesh = ci::TriMesh::create(ci::TriMesh::Format().colors(4).positions().normals().texCoords());

		create();
	}


	void cGemManager::draw()
	{

		auto ctx = ci::gl::context();
		ci::gl::ScopedVao vaoScp(ctx->getDrawTextureVao());
		ci::gl::ScopedBuffer vboScp(ctx->getDrawTextureVbo());

		size_t VisibleRange = 5;

		//原石
		for (size_t i = 0; i < mGemStone.size(); i++)
		{
			mGemStone[i]->draw();
		}

		//欠片
		for (size_t i = 0; i < mFragmentGems.size(); i++)
		{
			mFragmentGems[i]->draw();
		}
		ci::gl::color(ci::Color(1, 1, 1));
	};


	void cGemManager::drawFbo()
	{
		using namespace ci;
		//バインド用のrect
		auto rect = ci::Rectf(-ci::app::getWindowSize() / 2, ci::app::getWindowSize() / 2);

		ci::gl::pushMatrices();

		//GemStoneのFBO描画---------------------------------------------------------------------------
		{
			ci::gl::pushMatrices();
			ci::gl::ScopedFramebuffer fbScp(mGemBuffer);
			ci::gl::ScopedViewport    scpVp2(ci::ivec2(0), mGemBuffer->getSize());
			ci::gl::setMatrices(CAMERA->getCamera());

			ci::gl::ScopedGlslProg    shaderScp(mVboShader);
			mVboShader->uniform("deltaTime", mTime);
			mVboShader->uniform("visibleRange", mVisibleRange);
			mVboShader->uniform("playerPos", Game::cPlayerManager::getInstance()->getActivePlayer()->getPos());
			ci::gl::clear(ci::ColorA(0, 0, 0, 0));

			for (size_t i = 0; i < mGemStone.size(); i++)
			{
				mGemStone[i]->draw();
			}
			ci::gl::color(ci::Color(1, 1, 1));

			auto result = cGameManager::getInstance( )->getResult( );
			auto red = result.first;
			auto blue = result.second;

			float sum = red + blue;

			drawCannonPower( red / sum, blue / sum);

			ci::gl::popMatrices();
		}

		ci::gl::ScopedGlslProg    glsl(mShader);
		ci::gl::ScopedTextureBind tex(mGemBuffer->getColorTexture());

		mShader->uniform("uTex0", 0);
		mShader->uniform("uColor", ci::vec4(1, 1, 1, 1));
		mShader->uniform("uWindowSize", ci::vec2(ci::app::getWindowSize()));
		mShader->uniform("uVisibleRange", mVisibleRange/2);
		mShader->uniform("uPlayerPos", Game::cPlayerManager::getInstance()->getActivePlayer()->getPos());

		ci::gl::drawSolidRect(rect);

		//---------------------------------------------------------------------------------------------------------------

		//FragmentGemのFBO描画-----------------------------------------------------------------------------------------
		{
			ci::gl::pushMatrices();
			ci::gl::ScopedFramebuffer fbScp(mGemBuffer);
			ci::gl::ScopedViewport    scpVp2(ci::ivec2(0), mGemBuffer->getSize());
			ci::gl::setMatrices(CAMERA->getCamera());

			ci::gl::ScopedGlslProg    shaderScp(ci::gl::getStockShader(ci::gl::ShaderDef().color()));

			ci::gl::clear(ci::ColorA(0, 0, 0, 0));
			for (size_t i = 0; i < mFragmentGems.size(); i++)
			{
				mFragmentGems[i]->draw();
			}
			ci::gl::color(ci::Color(1, 1, 1));

			ci::gl::popMatrices();
		}

		ci::gl::ScopedGlslProg    glsl1(mFragGemShader);
		ci::gl::ScopedTextureBind tex2(mGemBuffer->getColorTexture());

		mFragGemShader->uniform("uTex0", 0);
		mFragGemShader->uniform("uColor", ci::vec4(1, 1, 1, 1));
		mFragGemShader->uniform("uWindowSize", ci::vec2(ci::app::getWindowSize()));

		ci::gl::drawSolidRect(rect);
		//----------------------------------------------------------------------------------------------------------------------
		ci::gl::popMatrices();

	}


	void cGemManager::update(float deltaTime)
	{
		DistanceSortGemStone();
		//ジェム点滅用タイム
		mTime += deltaTime * mLightingSpeed;
		
	};


	//---------------------//
	//   重力更新用アプデ  //
	//---------------------//
	void cGemManager::lateUpdate(const float& delta_time)
	{
		for (size_t i = 0; i < mFragmentGems.size(); i++)
		{
			mFragmentGems[i]->lateUpdate(delta_time);
		}
	};


	//---------------------------//
	//    スタート時の原石作成   //
	//---------------------------//
	void cGemManager::create()
	{
		ci::randSeed(uint32_t(mSeed));
		for (int i = 0; i < mGemMaxNum; i += 2)
		{

			int x = ci::randInt(0, int32_t(mRandomRange.x - 1));
			int y = ci::randInt(0, int32_t(mRandomRange.y - 1));
			int z = ci::randInt(0, int32_t(mRandomRange.z - 1));
			Gem::GemType type = Game::Gem::GemType(ci::randInt(0, Game::Gem::GemType::Coal + 1));


			//モデル切り替え
			ci::ColorA color = ci::Color(1, 1, 1);
			switch (type)
			{
			case Game::Gem::GemType::Dia:
				color = ci::ColorA8u(52, 152, 219);
				break;
			case Game::Gem::GemType::Gold:
				color = ci::ColorA8u(241, 196, 15);
				break;
			case Game::Gem::GemType::Coal:
				color = ci::ColorA8u(155, 89, 182);
				break;
			case Game::Gem::GemType::Iron:
				color = ci::ColorA8u(139, 195, 74);
				break;
			default:
				break;
			}

			//点滅のばらつき出す用
			color.a = cinder::randFloat(0, 1);

			mGemStone.push_back(std::make_shared<Gem::cGemStone>(
				                                                 i,
				                                                 (ci::vec3(x, y, z) * mMapChipSize) + mPosition,
				                                                 ci::vec3(mGemScale), 
				                                                 color, type));

			mGemStone.push_back(std::make_shared<Gem::cGemStone>(
				                                                 i + 1,
				                                                 mPosition + ci::vec3(mRandomRange.x - x + mRandomRange.x - 1, y, mRandomRange.z - z - 1) * mMapChipSize,
				                                                 ci::vec3(mGemScale),
				                                                 color, type));
		}

		//生成したGemStoneにindicesに割り振り
		int offset = 0;
		for each (auto& g in mGemStone)
		{
			g->setIndices(offset);
			offset += 24;
		}

		//VBOMesh作成
		buildMesh();
	};


	void cGemManager::buildMesh()
	{
		mesh->clear();
		IdSortGemStone();
		for (size_t i = 0; i < mGemStone.size(); i++)
		{
			auto indices   = mGemStone[i]->getIndices();
			ci::vec3 pos   = mGemStone[i]->getPos();
			ci::vec3 scale = mGemStone[i]->getScale() / 2.0f;

			mesh->appendIndices(&indices[0], indices.size());
			mesh->appendNormals(&mGemStone[i]->getNomals()[0], mGemStone[i]->getNomals().size());
			mesh->appendColors(&mGemStone[i]->getColorAs()[0], mGemStone[i]->getColorAs().size());

			std::vector<cinder::vec2> texCoords;
			for (int i = 0; i < 24; ++i) { texCoords.emplace_back(cinder::vec2(0, 0)); }

			mesh->appendTexCoords0(texCoords.data(), texCoords.size());

			//Vert
			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, -scale.z));

			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, scale.z));

			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, scale.z));

			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, scale.z));

			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, scale.z));

			mesh->appendPosition(pos + ci::vec3(scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, -scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(-scale.x, scale.y, -scale.z));
			mesh->appendPosition(pos + ci::vec3(scale.x, scale.y, -scale.z));

		}
		mGemsVbo = ci::gl::VboMesh::create(*mesh);
	}

	//------------------//
	//   メッシュclear  //
	//------------------//
	void cGemManager::clearMesh()
	{
		if (mesh == nullptr) return;
		mesh->clear();
	}


	std::shared_ptr<Gem::cGemStone> cGemManager::getGemStone(int id)
	{
		for (size_t i = 0; i < mGemStone.size(); i++)
		{
			if (mGemStone[i]->getId() == id)
			{
				return  mGemStone[i];
			}
		}

		ci::app::console() << "This is no GemStone that has that " << id << std::endl;
		return nullptr;
	}


	//-------------------------//
	//     原石を破壊した時    //
	//-------------------------//
	std::vector<std::shared_ptr<Gem::cFragmentGem>> cGemManager::breakGemStone(int id)
	{
		//生成された欠片
		std::vector<std::shared_ptr<Gem::cFragmentGem>> addGems;
		for (size_t i = 0; i < mGemStone.size(); i++)
		{
			if (mGemStone[i]->getId() == id)
			{
				if (!mGemStone[i]->isActive())
				{
					ci::app::console() << "This is no GemStone that has that " << id << std::endl;
					return addGems;
				}

				Sound::StereophonicManager::getInstance()->add("",Sound::Wav(ci::app::getAssetPath("SE/Gem/stonebreak.wav").string()), mGemStone[i]->getCenterPos());


				//生成
				ci::vec3 dir;
				ci::vec3 offset;
				for (int j = 0; j < mCreateFGemNum; j++)
				{
					dir.x     = ci::randInt(-6, 6);
					dir.z     = ci::randInt(-6, 6);
					dir.y     = 10;
					offset.x  = ci::randFloat(-0.8, 0.8);
					offset.y  = ci::randFloat(-0.8, 0.8);
					offset.z  = ci::randFloat(-0.8, 0.8);
					mFragmentGems.push_back(std::make_shared<Gem::cFragmentGem>(
						                                         mFragGemIDCount,
						                                         mGemStone[i]->getPos() + offset,
						                                         mGemStone[i]->getScale() / 2.0f,
						                                         mGemStone[i]->getColor(), mGemStone[i]->getType(),
						                                         glm::normalize(dir)));
					
					mFragmentGems[mFragmentGems.size() - 1]->setup();
					addGems.push_back(mFragmentGems[mFragmentGems.size() - 1]);
					mFragGemIDCount++;
				}
				//Indicesを一回所に
				mGemStone[i]->deleteGem();
				//VBOを作り直し
				buildMesh();
				mGemStone[i]->setIsActive(false);
				return  addGems;
			}
		}

		ci::app::console() << "This is no GemStone that has that " << id << std::endl;
		return addGems;
	}


	std::shared_ptr<Gem::cFragmentGem> cGemManager::getFragmentGem(int id)
	{
		for (size_t i = 0; i < mFragmentGems.size(); i++)
		{
			if (mFragmentGems[i]->getId() == id)
			{
				return  mFragmentGems[i];
			}
		}

		ci::app::console() << "This is no FragmentGem that has that " << id << std::endl;
		return nullptr;
	}


	void  cGemManager::deleteFragmentGem(int id)
	{
		std::vector<std::shared_ptr<Gem::cFragmentGem>>::iterator iterator = mFragmentGems.begin();
		for (size_t i = 0; i < mFragmentGems.size(); i++)
		{
			if (mFragmentGems[i]->getId() == id)
			{
				mFragmentGems.erase(iterator);
				return;
			}
			iterator++;
		}

		ci::app::console() << "This is no FragmentGem that has that " << id << std::endl;
		return;
	};

	void  cGemManager::deleteFragmentGems(std::vector<std::shared_ptr<Gem::cFragmentGem>> gems)
	{
		for (size_t g = 0; g < gems.size(); g++)
		{
			size_t i = 0;
			for (i = 0; i < mFragmentGems.size(); i++)
			{
				if (mFragmentGems[i]->getId() == gems[g]->getId())
				{
					mFragmentGems.erase(mFragmentGems.begin() + i);
					break;
				}
			}
			if (i == mFragmentGems.size())
			{
				ci::app::console() << "This is no FragmentGem that has that " << gems[g]->getId() << std::endl;
				break;
			}
		}
	}

	void cGemManager::DistanceSortGemStone()
	{
			ci::vec3 pPos = Game::cPlayerManager::getInstance()->getActivePlayer()->getPos();
			std::sort(mGemStone.begin(), mGemStone.end(), [&](const std::shared_ptr<Gem::cGemStone> a, const std::shared_ptr<Gem::cGemStone> b) { return glm::distance(pPos, a->getPos()) < glm::distance(pPos, b->getPos()); });

	}

	void cGemManager::IdSortGemStone()
	{
		std::sort(mGemStone.begin(), mGemStone.end(), [&](const std::shared_ptr<Gem::cGemStone> a, const std::shared_ptr<Gem::cGemStone> b) { return a->getId() < b->getId(); });
	}

	void cGemManager::drawCannonPower( float red, float blue )
	{
		using namespace cinder;

		geom::Capsule capsule;
		capsule.radius( 1.0F );

		geom::Torus torus;

		float length = Field::WORLD_SIZE.z - 7 - 7;

		{
			gl::color( Color( 1, 0, 0 ) );

			auto begin = Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 0.0F ) + vec3( 0, 5, 7 );
			capsule.set( begin, begin + vec3( 0, 0, length * red ) );
			gl::draw( capsule );

			torus.radius( 2.2F, 2.0F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 0.0F ) + vec3( 0, 5, 7 ) + vec3( 0, 0, -1 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );

			torus.radius( 2.4F, 2.2F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 0.0F ) + vec3( 0, 5, 7 ) + vec3( 0, 0, 0 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );

			torus.radius( 2.2F, 2.0F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 0.0F ) + vec3( 0, 5, 7 ) + vec3( 0, 0, 1 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );
		}
		
		{
			gl::color( Color( 0, 0, 1 ) );

			auto begin = Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 1.0F ) + vec3( 0, 5, -7 );
			capsule.set( begin, begin + vec3(0, 0, -length * blue) );
			gl::draw( capsule );

			torus.radius( 2.2F, 2.0F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 1.0F ) + vec3( 0, 5, -7 ) + vec3( 0, 0, 1 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );

			torus.radius( 2.4F, 2.2F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 1.0F ) + vec3( 0, 5, -7 ) + vec3( 0, 0, 0 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );

			torus.radius( 2.2F, 2.0F );
			gl::pushModelView( );
			gl::translate( Field::WORLD_SIZE * vec3( 0.5F, 1.0F, 1.0F ) + vec3( 0, 5, -7 ) + vec3( 0, 0, -1 ) );
			gl::rotate( M_PI * 0.5F, vec3( 1, 0, 0 ) );
			gl::draw( torus );
			gl::popModelView( );
		}

		gl::color( Color( 1, 1, 1 ) );
	}
}
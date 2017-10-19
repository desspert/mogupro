#include "Game/cGemManager.h"

namespace Game
{
	void cGemManager::setUp(ci::vec3 position, ci::vec3 randomRange, float mapChipSize, float gemScale, int gemMaxNum, unsigned long seed)
	{
		mPosition = position;
		mRandomRange = randomRange;
		mMapChipSize = mapChipSize;
		mGemScale = gemScale;
		mGemMaxNum = gemMaxNum;
		for (int i = 0; i < 2; i++)
		{
			mTeamGems[i].insert(std::map<Gem::GemType, int>::value_type(Gem::GemType::Dia, 0));
			mTeamGems[i].insert(std::map<Gem::GemType, int>::value_type(Gem::GemType::Gold, 0));
			mTeamGems[i].insert(std::map<Gem::GemType, int>::value_type(Gem::GemType::Iron, 0));
			mTeamGems[i].insert(std::map<Gem::GemType, int>::value_type(Gem::GemType::Coal, 0));
		}
		create();

		auto con = ci::gl::context();
	    //cinder::ColorAf coloraf = con->getCurrentColor();
		ci::gl::Fbo::Format format;
		mGemBuffer = ci::gl::Fbo::create(ci::app::getWindowWidth(), ci::app::getWindowHeight(), true);
		ci::gl::enableDepthWrite();
		ci::gl::enableDepthRead();
		ci::gl::enableAlphaBlending();
		//ci::gl::enable(GL_CULL_FACE);
	}

	void cGemManager::draw()
	{

		for each (auto g in mGemsptr)
		{
			g->draw();
		}
		ci::gl::color(ci::Color(1, 1, 1));
		
		auto rect = ci::Rectf(0, 0, 20, 20);
		ci::gl::Texture2dRef tex;
		mGemBuffer->bindTexture();
		tex = mGemBuffer->getTexture2d(GL_COLOR_ATTACHMENT0);
		
		ci::gl::GlslProgRef glsl = ci::gl::getStockShader(ci::gl::ShaderDef().uniformBasedPosAndTexCoord().texture());
		ci::gl::ScopedGlslProg shaderScp(glsl);

		ci::gl::draw(mGemBuffer->getColorTexture(), rect);
		ci::gl::draw(mGemBuffer->getDepthTexture(), ci::Rectf(20, 0, 40, 20));
		mGemBuffer->unbindTexture();
	
	};

	void cGemManager::update()
	{
		ci::gl::ScopedFramebuffer fbScp(mGemBuffer);
		ci::gl::clear(ci::ColorA(1,1,1,0));
		ci::gl::ScopedViewport scpVp2(ci::ivec2(0), mGemBuffer->getSize());


		ci::gl::setMatrices(CAMERA->getCamera());
		ci::gl::ScopedGlslProg shaderScp(ci::gl::getStockShader(ci::gl::ShaderDef().color()));

		for each (auto g in mGemsptr)
		{
			g->draw();
		}
		ci::gl::color(ci::Color(1, 1, 1));
	};

	void cGemManager::create()
	{

		for (int i = 0; i < mGemMaxNum; i += 2)
		{
			//DeBug:�{���̓T�[�o�[���������Ă���
			std::random_device seed_gen;
			std::mt19937 engine(seed_gen());
			unsigned long seed = engine();
			ci::randSeed(seed);

			int x = ci::randInt(0, mRandomRange.x - 1);
			int y = ci::randInt(0, mRandomRange.y - 1);
			int z = ci::randInt(0, mRandomRange.z - 1);
			Game::Gem::GemType type = Game::Gem::GemType(ci::randInt(0, Game::Gem::GemType::Iron));

			
			//�e�N�X�`���[�̒��ւ�
			//TexManager::geInstance()->loadTexture("~/~/gem"+type);W
			ci::Color color = ci::Color(1, 1, 1);
			switch (type)
			{
			case Game::Gem::GemType::Dia:
				color = ci::Color(0.5f, 0.5f, 0.5f);
				break;
			case Game::Gem::GemType::Gold:
				color = ci::Color(1, 1, 0);
				break;
			case Game::Gem::GemType::Coal:
				color = ci::Color(0, 0, 1);
				break;
			case Game::Gem::GemType::Iron:
				color = ci::Color(0, 1, 0);
				break;
			default:
				break;
			}

			mGemsptr.push_back(std::make_shared<Gem::cGem>(i, (ci::vec3(x, y, z) * mMapChipSize) + mPosition, ci::vec3(mGemScale), color, type));
			mGemsptr.push_back(std::make_shared<Gem::cGem>(i + 1, mPosition + ci::vec3(mRandomRange.x - x + mRandomRange.x - 1, y, mRandomRange.z - z - 1) * mMapChipSize, ci::vec3(mGemScale), color, type));
		}
	};


	void cGemManager::gemCountUp(int team, Gem::GemType type)
	{

		//DeBug:
		ci::app::console() << "�`�[��" << team << "��" << type << "���擾" << std::endl;
		for (int i = 0; i < 2; i++)
		{
			mTeamGems[i].at(mGemsptr.at(type)->getType())++;
			ci::app::console() << "�`�[����" << i << std::endl;
			for each (auto t in mTeamGems[i])
			{
				ci::app::console() << t.first << "��" << t.second << std::endl;
			}
		}
	}

	void cGemManager::gemDelete(int id)
	{
		std::vector<std::shared_ptr<Gem::cGem>>::iterator iterator = mGemsptr.begin();
		bool isNothig = true;
		//�w��̕�΂����邩
		for (int i = 0; i < mGemsptr.size(); i++)
		{
			if (mGemsptr[i]->getId() == id)
			{
				isNothig = false;
				break;
			}
			iterator++;
		}
		if (isNothig) return;

		mGemsptr.erase(iterator);
	}
}

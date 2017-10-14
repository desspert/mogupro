#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

namespace Game
{
	namespace Gem
	{
		enum GemType
		{
			Dia,
			Gold,
			Silver,
			Iron
		};

		class cGem
		{
		public:
			// id          id
			// positin     �ʒu
			// scale       �傫��
			// color       �J���[�i�����͖{��Texture�j
			// type        Gem�̎��(������ꂽ��texture�����ɂ���Ȃ�����)
			cGem(int id,vec3 postion, vec3 scale, Color color, GemType type) : mId(id),mPosition(postion), mScale(scale), mColor(color), mType(type) {};
			~cGem() {};

			void setUp(vec3 postion, vec3 scale, Color color, GemType type);
			void draw();
			void update();

			int getId() { return mId; }
			vec3 getPos() { return mPosition; }
			vec3 getScale() { return mScale; }
			GemType getType() { return mType; }
			Color getColor() { return mColor; }

		private:

			int mId;
			vec3 mPosition;
			vec3 mScale;
			vec3 mRotation;
			Color mColor;
			GemType mType;
			int mMoney;
		};
	}
}
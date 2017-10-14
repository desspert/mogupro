#pragma once
#include <Game/cObjectBase.h>
#include <cinder/gl/gl.h>
namespace Game {
	namespace SkyDome {
		class cSkyDome : public cObjectBase {
		private:
			//�摜
			ci::gl::TextureRef texture;
			//Sphere�̃��b�V���f�[�^
			ci::gl::BatchRef mSphere;
			//�摜��\�邽�߂̃V�F�[�_�[
			ci::gl::GlslProgRef mGlsl;

			ci::vec3 size;
		public:
			
			void setup() override;
			void update(const float& delta_time) override {};
			void draw() override;
		};
	}
}
#pragma once
#include <Game/cObjectBase.h>
#include "cinder/gl/gl.h"
namespace Game {
	namespace Player {
		class cPlayer : public Game::cObjectBase {
		private:
			ci::vec3 size;
			ci::vec3 center_angle;
			float speed;
			int player_id;
			//���삷��v���C���[���ǂ���
			bool active_user;

			//�摜
			ci::gl::TextureRef texture;
			//Sphere�̃��b�V���f�[�^
			ci::gl::BatchRef mSphere;
			//�摜��\�邽�߂̃V�F�[�_�[
			ci::gl::GlslProgRef mGlsl;

		public:
			cPlayer(const ci::vec3& pos, const ci::vec3& center_angle, const int& id, const bool& is_active_user);
			
			float getSpeed() {
				return speed;
			}

			int getPlayerId() {
				return player_id;
			}

			void move(const ci::vec3& pos) {
				mPos += pos;
			}

			void setup() override;
			void update(const float& delta_time) override;
			void draw() override;
		};
	}
}
#pragma once
#include <Game/cObjectBase.h>
#include <cinder/gl/gl.h>
#include <Collision/cAABBCollider.h>
#include <Collision/cRigidBody.h>
namespace Game {
	namespace Player {

		struct PlayerStatus {
			float attack;
			float drill_range;
			float jump_force;
			float speed;
		};

		//��X�s�[�h
		static const float DEFAULT_SPEED = 5.0f;

		class cPlayer : public Game::cObjectBase {
		private:
			ci::vec3 size;
			ci::ColorA8u color;
			//���b�V��
			ci::gl::VboMeshRef mesh;
			//�X�e�[�^�X
			PlayerStatus status;
			//�ݒu�ʒu
			ci::vec3 installation_position;

			//��P��
			int player_id;
			//���삷��v���C���[���ǂ���
			bool active_user;
			//�@�풆
			bool drilling;
			//�W�����v����true
			bool jump_flag;

			//�N�H�[�^�j�I���̗�O�p�̊p�x
			float save_rotate;

			//�v���C���[�̈ړ��x�N�g���ۑ�
			ci::vec3 velocity;

			//�����蔻��o�^
			Collision::cAABBCollider mCollider;
			Collision::cRigidBody mRigidbody;

			//�摜
			ci::gl::TextureRef texture;
			//Sphere�̃��b�V���f�[�^
			ci::gl::BatchRef mSphere;
			//�摜��\�邽�߂̃V�F�[�_�[
			ci::gl::GlslProgRef mGlsl;

			void playerRotation();
		public:
			cPlayer(const ci::vec3& pos, const ci::vec3& center_angle, const int& id, const bool& is_active_user);
			
			ci::vec3 getSize() {
				return size;
			}
			ci::vec3 getInstallationPosition() {
				return installation_position;
			}

			float getSpeed() {
				return status.speed;
			}
			void setSpeed(const float& speed) {
				status.speed = speed;
			}
			
			void setDefaultSpeed() {
				status.speed = DEFAULT_SPEED;
			}

			int getPlayerId() {
				return player_id;
			}
			
			//�@�풆�Ȃ�true������
			void Drilling(const bool& flag) {
				drilling = flag;
			}
			//�@�풆���ǂ�����Ԃ�
			bool isDrilling() {
				return drilling;
			}

			void move(const ci::vec3& velocity);
			void jump(bool flag);

			void setup() override;
			void update(const float& delta_time) override;
			void draw() override;
		};
	}
}
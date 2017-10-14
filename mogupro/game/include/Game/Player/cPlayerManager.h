#pragma once
#include <Utility/cSingletonAble.h>
namespace Game {
	namespace Player {
		class cPlayer;
		class cPlayerManager : public ::Utility::cSingletonAble<cPlayerManager> {
		private:
			//�S�v���C���[���X�g
			std::vector<std::shared_ptr<cPlayer>> player;
			//���������삷��v���C���[
			std::shared_ptr<cPlayer> active_player;

			bool mouse_on = false;
			void playerInstance();
			void playerMove();
		public:
			void setup();
			void update(const float& delta_time);
			void draw();
		};
	}
}
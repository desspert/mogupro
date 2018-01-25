#pragma once
#include <Scene/cSceneBase.h>
#include <Node/node.h>
#include <vector>
#include <Node/action.hpp>
#include <Node/renderer.hpp>
#include <Utility/TriMeshAnimation.h>
#include <cinder/gl/Fbo.h>

namespace Scene
{
namespace Member
{
class cMatching : public cSceneBase
{
public:
	void setup();
	void registerFunc();
	void setAnimation();
	void shutDown();
	void update(float deltaTime);
	void updateBoxFunc();
	void makeRoom();
	void inRoom();
	void addInRoomUI();
	void draw();
	void draw2D();
	void drawInRoom2D();
	void resize();
	inline std::string const getName( ) { return typeid( *this ).name( ); }
private:
	enum class ClassState
	{
		MASTER,
		CLIENT,
		NOT
	};

	ClassState mClassState;
	ClassState mWaitClassState;
	enum class PhaseState
	{
		NOT_IN_ROOM,
		IN_ROOM,
		BEGIN_GAME
	};

	PhaseState mPhaseState;

	bool mCanSend;
	hardptr<Node::node> mRoot;
	hardptr<Node::node> mMemberRoot;
	bool mAddMember;
	int mTeamNum;
	ci::vec3 mCamPos;
	int mSelectTag;
	int mPrevSelectTag;
	std::vector<std::function<void()>> outRoomFunc;
	std::vector<std::function<void()>> inRoomFunc;

	bool mBeginAnimation;
	bool mIsEndAnimation;

	int teamCount[2];

	class DrillUI
	{
	public:

		DrillUI() { }

		DrillUI(ci::vec2 pos, ci::vec2 moveVec, std::string name)
		{
			using namespace Node;
			using namespace Node::Action;
			mRoot = Node::node::create();
			mRoot->set_schedule_update();
			mRoot->set_position(pos);
			mRoot->run_action(ease<ci::EaseOutCirc>::create(
				move_to::create(3.0F, ci::vec3(moveVec.x,moveVec.y,0))));
			auto plate = Node::Renderer::sprite::create(Resource::IMAGE["matching/drillUI2.png"]);
			plate->set_position(ci::vec2(0, 0));
			plate->set_scale(glm::vec2(1.8f, 0.8f));
			mRoot->add_child(plate);

			auto f = Node::Renderer::label::create("sawarabi-gothic-medium.ttf", 32);
			f->set_text(u8"" + name);
			f->set_position(ci::vec2(0, 0));
			f->set_schedule_update();
			f->set_scale(glm::vec2(1, -1));
			mRoot->add_child(f);
		}

		void update(float deltaTime)
		{
			mRoot->entry_update(0.1f);
		}

		void draw()
		{
			mRoot->entry_render(cinder::mat4());
		}
		hardptr<Node::node> mRoot;
	};

	std::vector<DrillUI> drillUI1Ps;
	std::vector<DrillUI> drillUI2Ps;
	Utility::TriMeshAnimation mTrimeshAnimation;
	ci::gl::FboRef mTrimeshAnimationFbo;
	bool sceneChange;
};
}
}
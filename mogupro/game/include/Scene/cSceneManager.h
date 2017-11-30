#pragma once

#include <Utility/cSingletonAble.h>
#include <memory>
#include "cSceneBase.h"
#include <Utility/cInput.h>

//! @file cSceneManager
//! @brief Scene�؂�ւ����܂ߌ��݂�Scene�̂��ׂĂ��Ǘ�����N���X�ł�
//! @note 
//!      Change�ň�����SceneBase���p������Class��n���ăV�[����ς��܂�
//!      �����Ŕ��f���Ă��܂�
//! @date 2017-10-12
//! @author Taka Nomoto

class cSceneManager : public Utility::cSingletonAble<cSceneManager>
{
public:
	cSceneManager() = default;

	template<class scene,class... T>
	void change(T...args)
	{
		mSceneBase = std::make_shared<scene>(args...);
	};

	cSceneBase& now()
	{
		return *mSceneBase;
	};

	template<class scene, class... T>
	void shift(T...args)
	{
		if ( mSceneBase )
		{
			mSceneBase->shutDown( );
			ENV->flashInput( );
		}
		change<scene>(args...);
		mSceneBase->setup();
	}
private:

	std::shared_ptr<cSceneBase> mSceneBase;

};
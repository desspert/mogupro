#pragma once

#include <Utility/cSingletonAble.h>
#include <memory>
#include "cSceneBase.h"

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

	template<class T>
	void change(T* scene)
	{
		mSceneBase = std::make_shared<T>(*scene);
	};

	cSceneBase& now()
	{
		return *mSceneBase;
	};

	template<class T>
	void shift(T* scene)
	{
		mSceneBase->shutDown();
		change(scene);
		mSceneBase->setup();
	}
private:

	std::shared_ptr<cSceneBase> mSceneBase;

};
#pragma once

#include <Utility/cSingletonAble.h>
#include <memory>
#include "cSceneBase.h"

//! @file cSceneManager
//! @brief Scene切り替えを含め現在のSceneのすべてを管理するクラスです
//! @note 
//!      Changeで引数にSceneBaseを継承したClassを渡してシーンを変えます
//!      そこで判断しています
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
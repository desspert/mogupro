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

namespace Scene
{
class cSceneManager : public Utility::cSingletonAble<cSceneManager>
{
public:
	cSceneManager( );
	~cSceneManager( );

	void update( float delta )
	{
		mIsInUpdate = true;

		for ( auto& scene : mSceneBases )
		{
			scene->update( delta );
		}
		mDontDestroyOnLoad->update( delta );

		mIsInUpdate = false;
	}
	void draw( )
	{
		for ( auto& scene : mSceneBases )
		{
			scene->draw( );
		}
		mDontDestroyOnLoad->draw( );
	}
	void draw2D( )
	{
		for ( auto& scene : mSceneBases )
		{
			scene->draw2D( );
		}
		mDontDestroyOnLoad->draw2D( );
	}

	class SceneNotFound : public std::runtime_error
	{
	public:
		SceneNotFound( ) : std::runtime_error( "�V�[����������܂���B" )
		{
		}
	};
	template<class TyScene>
	TyScene& find( )
	{
		for ( auto& scene : mSceneBases )
		{
			if ( scene->getName( ) == typeid(TyScene).name( ) )
			{
				return scene;
			}
		}
		throw SceneNotFound( );
	}

	cSceneBase& getDontDestroyOnLoad( );

	template<class TyScene, class... Args>
	void add( Args... args )
	{
		auto scene = std::make_shared<TyScene>( args... );
		mSceneBases.emplace_back( scene );
		scene->setup( );
	}

	template<class TyScene>
	void erase( )
	{
		auto it = mSceneBases.begin( );
		while ( it != mSceneBases.end( ) )
		{
			if ( ( *it )->getName( ) == typeid( TyScene ).name( ) )
			{
				(*it)->shutDown( );
				it = mSceneBases.erase( it );
			}
			else ++it;
		}
	}

	class SceneDeleted : public std::runtime_error
	{
	public:
		SceneDeleted( ) : std::runtime_error( "�V�[�����폜���܂����B" )
		{
		}
	};

	template<class TyScene, class... Args>
	void shift( Args... args )
	{
		// �S�ẴV�[���̃V���b�g�_�E��
		for ( auto& scene : mSceneBases )
		{
			scene->shutDown( );
		}

		// ���͂��Ւf
		ENV->flashInput( );

		// �S�ẴV�[�����폜
		auto it = mSceneBases.begin( );
		while ( it != mSceneBases.end( ) )
		{
			it = mSceneBases.erase( it );
		}

		// �V�����V�[�����쐬
		mSceneBases.emplace_back( std::make_shared<TyScene>( args... ) );

		// �S�ẴV�[���̃Z�b�g�A�b�v
		for ( auto& scene : mSceneBases )
		{
			scene->setup( );
		}

		if ( mIsInUpdate )
		{
			throw SceneDeleted( );
		}
	}
private:
	std::vector<std::shared_ptr<cSceneBase>> mSceneBases;
	std::shared_ptr<cSceneBase> mDontDestroyOnLoad;
	bool mIsInUpdate = false;
};
}
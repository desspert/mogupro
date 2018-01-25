#pragma once
#include <map>
#include <memory>
#include <Utility/cSingletonAble.h>
#include <cinder/gl/VboMesh.h>
#include <vector>
#include <string>
namespace Resource
{
class cObjectManager : public Utility::cSingletonAble<cObjectManager>
{
public:
    cObjectManager( );
    // ��: Assets/OBJ/player.obj �Ȃ�
    // ��: player.obj �Ɠ��͂���B
    cinder::gl::VboMeshRef& findObject( std::string const& underAssetsUnderSEUnderPath );
	void loadOne( );
	bool isFinished( );
	int maxNum( );
	int currentNum( );
private:
    std::map<std::string, cinder::gl::VboMeshRef> mObjects;
	int mCurrentLoadIndex = 0;
	std::vector<std::string> mFilePaths;
};
struct ObjectSuppoter
{
	class ObjectNotFound : public std::runtime_error
	{
	public:
		ObjectNotFound( ) : std::runtime_error( "obj�t�@�C����������܂���B" )
		{
		}
	};
	cinder::gl::VboMeshRef operator[]( std::string const& underAssetsUnderOBJUnderPath ) const
	{
		try
		{
			return cObjectManager::getInstance( )->findObject( underAssetsUnderOBJUnderPath );
		}
		catch ( ... )
		{
			throw ObjectNotFound( );
		}
	}
};
extern ObjectSuppoter const OBJ;
}

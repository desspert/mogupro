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
    // 例: Assets/OBJ/player.obj なら
    // ＞: player.obj と入力する。
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
}

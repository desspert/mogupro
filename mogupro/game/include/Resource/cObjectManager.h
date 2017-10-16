#pragma once
#include <map>
#include <memory>
#include <Utility/cSingletonAble.h>
#include <cinder/gl/VboMesh.h>
namespace Resource
{
class cObjectManager : public Utility::cSingletonAble<cObjectManager>
{
public:
    cObjectManager( );
    // ��: Assets/OBJ/player.obj �Ȃ�
    // ��: player.obj �Ɠ��͂���B
    cinder::gl::VboMeshRef& findObject( std::string const& underAssetsUnderSEUnderPath );
private:
    std::map<std::string, cinder::gl::VboMeshRef> mObjects;
};
}

#pragma once
#include <map>
#include <memory>
#include <Utility/cSingletonAble.h>
#include <cinder/gl/Texture.h>
#include <boost/optional.hpp>
namespace Resource
{
class cImageManager : public Utility::cSingletonAble<cImageManager>
{
public:
	cImageManager( );
	// ��: Assets/Image/player.png �Ȃ�
	// ��: player.png �Ɠ��͂���B
	cinder::gl::TextureRef find( std::string const& underAssetsUnderImagePath );
	void loadOne( );
	bool isFinished( );
	int maxNum( );
	int currentNum( );
private:
	std::map<std::string, cinder::gl::TextureRef> mImages;
	int mCurrentLoadIndex = 0;
	std::vector<std::string> mFilePaths;
};
struct ImageSuppoter
{
	class ImageNotFound : public std::runtime_error
	{
	public:
		ImageNotFound( ) : std::runtime_error( "image�t�@�C����������܂���B" )
		{
		}
	};
	cinder::gl::TextureRef operator[]( std::string const& underAssetsUnderIMAGEUnderPath ) const
	{
		try
		{
			return cImageManager::getInstance( )->find( underAssetsUnderIMAGEUnderPath );
		}
		catch ( ... )
		{
			throw ImageNotFound( );
		}
	}
};
extern ImageSuppoter const IMAGE;
}

#pragma once
#include <map>
#include <memory>
#include <Utility/cSingletonAble.h>
#include <Sound/cSE.h>
#include <Sound/cBGM.h>
#include <vector>
#include <string>
namespace Resource
{
class cSoundManager : public Utility::cSingletonAble<cSoundManager>
{
public:
    cSoundManager( );
    // ��: Assets/SE/player/attack.wav �Ȃ�
    // ��: player/attack.wav �Ɠ��͂���B
    Sound::cSE& findSe( std::string const& underAssetsUnderSEUnderPath );
    // ��: Assets/BGM/main/buttle1.wav �Ȃ�
    // ��: main/buttle1.wav �Ɠ��͂���B
    Sound::cBGM& findBgm( std::string const& underAssetsUnderBGMUnderPath );
	void loadOne( );
	bool isFinished( );
	int maxNum( );
	int currentNum( );
private:
	void loadOneSe( );
	bool isSeFinished( );
	void loadOneBgm( );
	bool isBgmFinished( );
private:
    std::map<std::string, Sound::cSE> mSes;
    std::map<std::string, Sound::cBGM> mBgms;
	std::vector<std::string> mSeFilePaths;
	std::vector<std::string> mBgmFilePaths;
	int mSeCurrentLoadIndex = 0;
	int mBgmCurrentLoadIndex = 0;
};
struct SeSuppoter
{
	class SeNotFound : public std::runtime_error
	{
	public:
		SeNotFound( ) : std::runtime_error( "se�t�@�C����������܂���B" )
		{
		}
	};
	Sound::cSE& operator[]( std::string const& underAssetsUnderIMAGEUnderPath ) const
	{
		try
		{
			return cSoundManager::getInstance( )->findSe( underAssetsUnderIMAGEUnderPath );
		}
		catch ( ... )
		{
			throw SeNotFound( );
		}
	}
};
extern SeSuppoter const SE;
struct BgmSuppoter
{
	class BgmNotFound : public std::runtime_error
	{
	public:
		BgmNotFound( ) : std::runtime_error( "bgm�t�@�C����������܂���B" )
		{
		}
	};
	Sound::cBGM& operator[]( std::string const& underAssetsUnderIMAGEUnderPath ) const
	{
		try
		{
			return cSoundManager::getInstance( )->findBgm( underAssetsUnderIMAGEUnderPath );
		}
		catch ( ... )
		{
			throw BgmNotFound( );
		}
	}
};
extern BgmSuppoter const BGM;
}

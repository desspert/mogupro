#pragma once
#include <map>
#include <memory>
#include <Utility/cSingletonAble.h>
#include <jsoncpp/json.h>
#include <boost/optional.hpp>
namespace Resource
{
class cJsonManager : public Utility::cSingletonAble<cJsonManager>
{
public:
	cJsonManager( );
    // ��: Assets/JSON/player.json �Ȃ�
    // ��: player.json �Ɠ��͂���B
	boost::optional<Json::Value const&> find( std::string const& underAssetsUnderJSONUnderPath ) const noexcept;
	void reload( );
private:
    std::map<std::string, Json::Value> mJsons;
};
struct JsonSuppoter
{
	class JsonNotFound : public std::runtime_error
	{
	public:
		JsonNotFound( ) : std::runtime_error( "json�t�@�C����������܂���B" )
		{
		}
	};
	Json::Value const& operator[]( std::string const& underAssetsUnderJSONUnderPath ) const
	{
		if ( auto json = cJsonManager::getInstance( )->find( underAssetsUnderJSONUnderPath ) )
		{
			return *json;
		}
		else
		{
			throw JsonNotFound( );
		}
	}
};
extern JsonSuppoter const JSON;
}

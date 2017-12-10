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
	boost::optional<Json::Value const&> find( std::string const& underAssetsUnderSEUnderPath ) const noexcept;
private:
    std::map<std::string, Json::Value> mJsons;
};
}

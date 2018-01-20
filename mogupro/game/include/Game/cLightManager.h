#pragma once
#include <Utility/cSingletonAble.h>
#include <cinder/Vector.h>
#include <map>
#include <set>
#include <vector>
#include <Utility/cUserPointer.hpp>
#include <Game/Light/cPointLightParam.h>
#include <Game/Light/cLineLightParam.h>
#include <Game/Light/cSpotLightParam.h>
#include <boost/optional.hpp>
#include <Utility/cIdentifier.h>
#include <Game/Light/LightDefine.h>
namespace Game
{
class cLightManager : public Utility::cSingletonAble<cLightManager>
{
public:
	cLightManager( );
	~cLightManager( ) = default;
	void setup( );
	void update( );
	#pragma region �|�C���g���C�g
public:
	friend class Light::cPointLightParam;
	std::map<int, Light::cPointLightParam const*>const& getPointLights( ) const;
	boost::optional<std::set<Light::cPointLightParam const*>const&> getPointLights( int chunkId ) const;
	Light::PointLightHandle addPointLight( cinder::vec3 position, cinder::vec3 color, float radius );
private:
	void removePointLight( int id, Light::cPointLightParam const* param );
	void attachChunk( Light::cPointLightParam const* param );
	void detachChunk( Light::cPointLightParam const* param );
private:
	Utility::cIdentifier mPointLightIdGenerator;
	std::map<int, Light::cPointLightParam const*> mPointLights;
	std::map<int, std::set<Light::cPointLightParam const*>> mPointLightsMap;
	#pragma endregion
	#pragma region ���C�����C�g
public:
	friend class Light::cLineLightParam;
	std::map<int, Light::cLineLightParam const*>const& getLineLights( ) const;
	boost::optional<std::set<Light::cLineLightParam const*>const&> getLineLights( int chunkId ) const;
	Light::LineLightHandle addLineLight( cinder::vec3 beginPosition, cinder::vec3 endPosition, cinder::vec3 color, float radius );
private:
	void removeLineLight( int id, Light::cLineLightParam const* param );
	void attachChunk( Light::cLineLightParam const* param );
	void detachChunk( Light::cLineLightParam const* param );
private:
	Utility::cIdentifier mLineLightIdGenerator;
	std::map<int, Light::cLineLightParam const*> mLineLights;
	std::map<int, std::set<Light::cLineLightParam const*>> mLineLightsMap;
	#pragma endregion
	#pragma region �X�|�b�g���C�g
public:
	friend class Light::cSpotLightParam;
	std::map<int, Light::cSpotLightParam const*>const& getSpotLights( ) const;
	boost::optional<std::set<Light::cSpotLightParam const*>const&> getSpotLights( int chunkId ) const;
	Light::SpotLightHandle addSpotLight( cinder::vec3 position, cinder::vec3 direction, cinder::vec3 color, float radius );
private:
	void removeSpotLight( int id, Light::cSpotLightParam const* param );
	void attachChunk( Light::cSpotLightParam const* param );
	void detachChunk( Light::cSpotLightParam const* param );
private:
	Utility::cIdentifier mSpotLightIdGenerator;
	std::map<int, Light::cSpotLightParam const*> mSpotLights;
	std::map<int, std::set<Light::cSpotLightParam const*>> mSpotLightsMap;
	#pragma endregion
};
}

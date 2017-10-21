#pragma once
#include <cinder/gl/Texture.h>           
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <unordered_map>
#include <Utility/cSingletonAble.h>

//Json�ǂݍ��ݗp
//static std::string loadString(std::string const& relative_path) {
//	return std::string(static_cast<char*>(ci::app::loadAsset(relative_path)->getBuffer()->getData()));
//}

#define TEX Resource::TextureManager::getInstance()

namespace Resource {
	class TextureManager : public Utility::cSingletonAble<TextureManager>
	{
	private:
		std::unordered_map<std::string, ci::gl::TextureRef> texture;
		ci::Font font;
	public:
		TextureManager() {

		};
		~TextureManager() {};

		//�^�O��Path������B
		//cinder0.9����getAssetPath�͒��ŌĂ΂�Ă���̂�
		//Asset��������Q�Ƃ����OK
		//��@TEX.set("sky_dome","SkyDome/Skydome151004y.jpg");
		void set(const std::string& name, const std::string& path)
		{
			if (texture.find(name) == texture.end()) {
				auto img = ci::loadImage(ci::app::loadAsset(path));
				texture[name] = ci::gl::Texture::create(img);
			}
		}
		void setup() {
			font = ci::Font(ci::app::loadAsset("CP Font.ttf"), 100);
		}
		ci::gl::TextureRef get(std::string name) {
			return texture[name];
		}
		ci::Font getFont() {
			return font;
		}
	};
}
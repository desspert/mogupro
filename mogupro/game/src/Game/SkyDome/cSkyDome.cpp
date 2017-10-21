#include <Game/SkyDome/cSkyDome.h>
#include <Resource/TextureManager.h>
#include <CameraManager/cCameraManager.h>

void Game::SkyDome::cSkyDome::setup()
{
	//�摜�̃o�C���h
	TEX->set("sky_dome","SkyDome/Skydome151004y.jpg");

	size = ci::vec3(5000, 5000, 5000);
	
	//�摜��\����Ԃɂ���
	//�J�����O���K�p����Ȃ������̂�Lambert�͂Ȃ�
	auto shader = ci::gl::ShaderDef().texture();
	mGlsl = ci::gl::getStockShader(shader);
	//���_���T�O�̃X�t�B�A����
	auto sphere = ci::geom::Sphere().subdivisions(50);
	mSphere = ci::gl::Batch::create(sphere, mGlsl);

}

void Game::SkyDome::cSkyDome::draw()
{
	
	//�摜���o�C���h
	Resource::TextureManager::getInstance()->get("sky_dome")->bind();
	ci::gl::pushModelView();
	ci::gl::translate(CAMERA->getPos());
	ci::gl::scale(size);
	mSphere->draw();
	ci::gl::popModelView();
	Resource::TextureManager::getInstance()->get("sky_dome")->unbind();


}

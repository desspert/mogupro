#include <SkyDome/SkyDome.h>
#include <Utility/TextureManager.h>
#include <ProdactionCamera.h>
void SkyDome::setup()
{
	//�摜�̃o�C���h
	TEX.set("sky_dome","SkyDome/Skydome151004y.jpg");

	size = ci::vec3(5000, 5000, 5000);
	
	//�摜��\����Ԃɂ���
	//�J�����O���K�p����Ȃ������̂�Lambert�͂Ȃ�
	auto shader = ci::gl::ShaderDef().texture();
	mGlsl = ci::gl::getStockShader(shader);
	//���_���T�O�̃X�t�B�A����
	auto sphere = ci::geom::Sphere().subdivisions(50);
	mSphere = ci::gl::Batch::create(sphere, mGlsl);

}

void SkyDome::draw()
{
	
	//�摜���o�C���h
	TEX.get("sky_dome")->bind();
	ci::gl::pushModelView();
	ci::gl::translate(CAMERA.getPos());
	ci::gl::scale(size);
	mSphere->draw();
	ci::gl::popModelView();

	TEX.get("sky_dome")->unbind();


}

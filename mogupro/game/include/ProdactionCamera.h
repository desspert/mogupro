#pragma once
#include "cinder/app/App.h"
#include "cinder/Camera.h"
#include <cinder/imageIo.h>
#include <cinder/gl/Texture.h> 
#include <cinder/gl/gl.h>
#include <random>
#define CAMERA ProductionCamera::get()

namespace camera_ {
	enum WINDOW_SIZE {
		WIDTH = 640,
		HEIGHT = 960,
		TEXTURE_WIDTH = 3000,
		TEXTURE_HEIGHT = 4500
	};
}

class ProductionCamera {
private:
	ci::CameraPersp camera;
	ci::vec3 pos;
	//���炩�ɖړI���W�ɒǏ]���邽�߂�buf
	ci::vec3 buf_pos;
	//�ڕW��pos�̎Q��
	std::shared_ptr<ci::vec3*> reference_pos;

	//�ڕW�ƑΏƓI�ȃJ�����̈ʒu
	ci::vec3 looking_point;
	
	//�J�����̌����Ă���p�x
	ci::vec2 camera_angle;


	ci::vec2 my_scatter;
	//�h��镝
	float scatter;
	//�h���b��
	float seconds;

	//�J�����̑Ώۂ���̉���
	float camera_far;

	//�J������

	//��ʂ��Â������薾�邭�����邷��p�̉摜
	ci::gl::TextureRef fade_tex;

	//�������J�����ړ�
	void MovingCamera();

	//�u���铮��
	void ScatterCamera();
public:
	
	
	//��ʂ̃t�F�[�h�l
	ci::vec4 fade_out;


	ProductionCamera(){
		scatter = 0;
		pos = ci::vec3(0);
		buf_pos = ci::vec3(0);
		fade_out = ci::vec4(0, 0, 0, 0);
		camera_angle = ci::vec2(0);
		looking_point = ci::vec3(0);
		my_scatter = ci::vec2(0);
		camera_far = 5;
	}
	~ProductionCamera() {
		
	}
	static ProductionCamera& get() {
		static ProductionCamera in;
		return in;
	}

	const ci::CameraPersp& getCamera() {
		return camera;
	}

	void setCameraAngle(const ci::vec2& angle) {
		camera_angle += angle;
		camera_angle.y = std::min(float(M_PI / 2) - 0.01f,
			std::max(camera_angle.y, -float(M_PI / 2) + 0.01f));
		camera_angle.x = std::fmod(camera_angle.x, M_PI * 2.0);
	}
	ci::vec3 getPos() {
		return ci::vec3(pos.x,pos.y,pos.z);
	}
	
	void followingCamera(ci::vec3* pos,const float& far) {
		reference_pos = std::make_shared<ci::vec3*>(pos);
		camera_far = far;
	}
	
	//�J������h�炷�֐�
	//scattar =�@�u�����A�@seconds�@���@�b��
	void shakeCamera(const float& scatter, const float& seconds);
	void setup();
	void update(const float& delta_time);
	void draw();
};

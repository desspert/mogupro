#pragma once
#include <cinder/app/App.h>
#include <cinder/Camera.h>
#include <Utility/cSingletonAble.h>
#define CAMERA ::CameraManager::cCameraManager::getInstance()
namespace CameraManager
{
enum WINDOW_SIZE {
    WIDTH = 640,
    HEIGHT = 960,
    TEXTURE_WIDTH = 3000,
    TEXTURE_HEIGHT = 4500
};
enum CAMERA_MODE {
	TPS,
	FPS
};
class cCameraManager : public Utility::cSingletonAble<cCameraManager>
{
public:
    ci::vec3 refPosition;
private:
    ci::CameraPersp camera;
    ci::CameraOrtho camera_2d;
    //滑らかに目的座標に追従するためのbuf
    ci::vec3 buf_pos;

	// eyePos
	ci::vec3 pos;
	// カメラの向いている位置
	// lookPos
	ci::vec3 looking_position;
    //目標と対照的なカメラの位置
    ci::vec3 looking_point;

	ci::vec3 up = ci::vec3( 0, 1, 0 );

    //カメラの向いている角度
    ci::vec2 camera_angle;

	CAMERA_MODE camera_mode;

    ci::vec3 my_scatter;
	ci::vec2 my_scatter2D;
    //揺れる幅
    float scatter;
	float scatter2D=0.0f;
    //揺れる秒数
    float seconds;
	float seconds2D = 0.0f;
    //カメラの対象からの遠さ
    float camera_far;

    //カメラの

    ////画面を暗くしたり明るくしたるする用の画像
    //ci::gl::TextureRef fade_tex;

    //慣性つきカメラ移動
    void MovingCamera( );

    //ブレる動作
    void ScatterCamera( );
	void ScatterCamera2D();
	bool scheduleUpdate = true;
public:
	void setScheduleUpdate(bool value) { scheduleUpdate = value; }
	bool isScheduleUpdate() { return scheduleUpdate; }
	void lookAt(cinder::vec3 eye, cinder::vec3 target, cinder::vec3 up ) 
	{ 
		pos = eye; 
		looking_position = target;
		this->up = up;
	}
    //画面のフェード値
    ci::vec4 fade_out;


    cCameraManager( ) {
        scatter = 0;
        pos = ci::vec3( 0 );
        buf_pos = ci::vec3( 0 );
        fade_out = ci::vec4( 0, 0, 0, 0 );
        camera_angle = ci::vec2( 0 );
        looking_point = ci::vec3( 0 );
        my_scatter = ci::vec3( 0 );
		looking_position = ci::vec3(0);
		camera_mode = CAMERA_MODE::TPS;
        camera_far = 5;
    }
    ~cCameraManager( ) {

    }

    const ci::CameraPersp& getCamera( ) {
        return camera;
    }

	// setとaddに分けました。
	// 11.27以前の関数はaddCameraAngleになりました。
	void setCameraAngle( ci::vec2 const& angle );
    void addCameraAngle( const ci::vec2& angle ) {
        camera_angle += angle;
        camera_angle.y = std::min( float( M_PI / 2 ) - 0.01f,
                                   std::max( camera_angle.y, -float( M_PI / 2 ) + 0.01f ) );
        camera_angle.x = std::fmod( camera_angle.x, M_PI * 2.0 );
    }
    ci::vec3 getPos( ) {
        return ci::vec3( pos.x, pos.y, pos.z );
    }
    ci::vec2 getCameraAngle( ) {
        return camera_angle;
    }

	//カメラの向いている向きを返す
	ci::vec3 getCameraLook() {
		/*if (camera_mode = CAMERA_MODE::FPS) {
			return ci::vec3(looking_point.x, looking_point.y, looking_point.z);
		}*/
		return ci::vec3(looking_point.x / 10, looking_point.y / 10, looking_point.z / 10);
	}
	void setCameraMode(CAMERA_MODE value)
	{
		camera_mode = value;
	}
	CAMERA_MODE getCameraMode() {
		return camera_mode;
	}
	void setCameraFar(float& set_far) {
		camera_far = set_far;
		if (camera_far <= 0.5f) {
			camera_mode = CAMERA_MODE::FPS;
			camera_far = 0.4f;
		}
		else if(camera_far > 0.5f) {
			camera_mode = CAMERA_MODE::TPS;
		}
	}

    //カメラを揺らす関数
    //scattar =　ブレ幅、　seconds　＝　秒数
    void shakeCamera( const float& scatter, const float& seconds );
	void shakeCamera2D(const float& scatter, const float& seconds);
    void setup( );
    void update( const float& delta_time );
    void bind3D( );
    void unBind3D( );
    void bind2D( );
    void unBind2D( );
};
}

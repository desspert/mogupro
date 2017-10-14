#include<Strategy/StrategyObject/cDrill.h>
#include "cinder/gl/gl.h"
#include"Game\Field/cFieldManager.h"
using namespace ci;
using namespace ci::app;
namespace Strategy
{
namespace StrategyObject
{

cDrill::cDrill(const ci::vec3 _pos,const  ci::vec3 _scale)
{
	machinescale = _scale + vec3(2, 2, 2);
	pos = _pos + vec3(0, machinescale.y / 2.f, 0);
	scale = _scale;
	beginpos = pos;
	
	slope = vec3(scale.x, 0, scale.z);

	createDrills();//�e�X�g


}
cDrill::~cDrill( )
{

}
void cDrill::draw()
{
	drawCube(beginpos, machinescale, vec3(0, 0, 0), ColorA(0, 0, 1, 1));
	//drawCube(pos, scale, vec3(0,0, 0), ColorA(1, 0, 0));

	float drawrate = 0.8f;
	drawCube(beginpos + vec3(0, -slope.y / 2.f, 0), vec3(scale.x*drawrate, std::max(slope.y - float(1.f*scale.y), 0.f), scale.z*drawrate), vec3(0, y_rotate, 0), ColorA(1, 0.5, 0.2, 1));
	drawCube(beginpos + vec3(0, -slope.y / 2.f, 0), vec3(scale.x*drawrate, std::max(slope.y - float(1.f*scale.y), 0.f), scale.z*drawrate), vec3(0, -y_rotate, 0), ColorA(0, 0, 0, 1));

	for (int i = 0; i < drillslopes.size(); i++) {
		if (i == 0) {
			float rate = drillslopes[i].scale.y / 5.f;
			drawCube(drillslopes[i].pos - vec3(0, 2, 0)*rate, vec3(rate*1.f, rate*1.f, rate*1.f), vec3(0, drillslopes[i].rotate*5.f, 0), ColorA(1, 1, 1, 1));
			drawCube(drillslopes[i].pos - vec3(0, 1, 0)*rate, vec3(rate*1.f,rate*1.f, rate*1.f), vec3(0, drillslopes[i].rotate, 0), ColorA(0, 0, 0, 1));
			drawCube(drillslopes[i].pos, vec3(rate*3.f, rate*1.f, rate*3.f), vec3(0, drillslopes[i].rotate*3.f, 0), ColorA(1, 0, 0, 1));
			drawCube(drillslopes[i].pos + vec3(0, 1, 0)*rate, vec3(rate*4.f, rate*1.f,rate*4.f), vec3(0, drillslopes[i].rotate*3.f, 0), ColorA(0, 0, 0, 1));
			drawCube(drillslopes[i].pos + vec3(0, 2, 0)*rate, vec3(rate*4.f, rate*1.f,rate*4.f), vec3(0, drillslopes[i].rotate*-3.f, 0), ColorA(1, 1, 0, 1));
		}
		else {
			drawCube(drillslopes[i].pos, drillslopes[i].scale, vec3(0, drillslopes[i].rotate, 0), ColorA(0, 0, 0, 1));
			drawCube(drillslopes[i].pos, drillslopes[i].scale, vec3(0, -drillslopes[i].rotate, 0), ColorA(1, 0.5, 0.2, 1));
		}
		
	}

	gl::color(ColorA(1, 1, 1, 1));
}
void cDrill::update(const float & delta_time)
{
	y_rotate++;
	move();
	Game::Field::cFieldManager::getInstance()->blockBreak(pos, scale.z);

	//if ((beginpos.y - pos.y) >= (float(drillslopes.size())*scale.y)) {
	//	createDrills();
	//}

	slope.y += drillspeed;///////////
	for (int i = 0; i < drillslopes.size(); i++) {
		drillslopes[i].rotate += i % 2 == 0 ? 5 : -5;
	}

	for (int i = 0; i < drillslopes.size(); i++) {
		drillslopes[i].pos -= vec3(0, drillspeed, 0);
	}

}
void cDrill::setup()
{

}
bool cDrill::DeleteThis()
{
	return (beginpos.y-pos.y) >= 60.f;
}

void cDrill::drawCube(const ci::vec3 pos, const ci::vec3 size, const ci::vec3 rotate, const ci::ColorA color)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate.x, vec3(1, 0, 0));
	gl::rotate(rotate.y, vec3(0, 1, 0));
	gl::rotate(rotate.z, vec3(0, 0, 1));
	gl::scale(size);
	gl::color(color);
	gl::drawCube(vec3(0, 0, 0),vec3(1, 1, 1));
	gl::popModelView();
}
void cDrill::createDrills()
{
	
	DrillSlope drill;
	drill.pos = beginpos;
	drill.scale = scale;
	drill.rotate = float(drillslopes.size())*17.f;
	drillslopes.push_back(DrillSlope(drill));

}
void cDrill::move()
{
	pos.y -= drillspeed;
}
;
}
}
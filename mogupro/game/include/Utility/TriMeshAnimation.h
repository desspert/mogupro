#pragma once
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>

namespace Utility
{
	class TriMeshAnimation
	{
	public:
		//windowSize -> ��ʃT�C�Y
		//cutSize -> ������
		void make(ci::vec2 windowSize, ci::vec2 cutSize);
		
		void update(float deltaTime);

		void draw();

	private:
		std::vector<ci::vec3> centers;
		std::vector<ci::vec3> posAs;
		std::vector<ci::vec3> posBs;
		std::vector<ci::vec3> posCs;
		std::vector<ci::vec3> vertices;
		std::vector<ci::vec2> texCoords;
		std::vector<uint32_t> indices;
		std::vector<ci::vec3> vectors;
		float gravityValue = 0.0f;
		float gravityTime = 0.0f;
		std::vector<ci::vec2> rotate;
		int indexCount;
		ci::vec2 windowSize;
	};
}

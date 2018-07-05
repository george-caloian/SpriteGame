#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Droplet
{
	public:
		Droplet(int X, int Y, int Z);
		bool collide(int surfaceY);
		void updateSpeed(float speed);
		void bounceUp();
		void bounceDown();
		const float G = 9.8;
		const int maxBounces = 5;
	private:
		float size;
		float speed;
		int bounces;
		int acceleration;
		int dimX, dimY, dimZ;
		int direction;


};

Mesh* CreatePlane(std::string name);

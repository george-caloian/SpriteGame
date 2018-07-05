#include "Utils.h"
#include <Core/Engine.h>
Droplet::Droplet(int X, int Y, int Z)
{
	this->dimX = X;
	this->dimY = Y;
	this->dimZ = Z;
	bounces = 0;
}


bool Droplet::collide(int surfaceY)
{
	if (this->dimY <= surfaceY)
		return true;
	return false;
}

void Droplet::updateSpeed(float speed)
{
	this->speed = speed;
}

void Droplet::bounceUp()
{
	this->direction = -1;
	this->bounces++;
}

void Droplet::bounceDown()
{
	direction = 1;
}




Mesh* CreatePlane(std::string name )
{
	glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	for (int i = 0; i<100; i++)
		for (int j = 0; j < 100; j++)
		{
			vertices.push_back(VertexFormat(glm::vec3(i*0.1, 0, j*0.1), color));
		}
		Mesh* square = new Mesh(name);
		/*
		for (int row = 0; row<10 - 1; row++) {
			if ((row % 2) == 0) { // even rows
				for (int col = 0; col<10-1; col++) {
					indices.push_back( col + row * 10);
					indices.push_back(col + (row + 1) * 10);
				}
			}
			else { // odd rows
				for (int col = 10 - 1; col>0; col--) {
					indices.push_back(col + (row + 1) * 10);
					indices.push_back(col - 1 + +10 * 10);
				}
			}
		}
		*/
		for (int z = 0; z < 100 - 1; z++) {
			// degenerate index on non-first row
			if (z != 0) indices.push_back(z * 100);

			// main strip
			for (int x = 0; x < 100; x++) {
				indices.push_back(z * 100 + x);
				indices.push_back((z + 1) * 100 + x);
			}

			// degenerate index on non-last row
			if (z != (100 - 2)) 
				indices.push_back((z + 1) * 100 + (100 - 1));
		}
		square->SetDrawMode(GL_TRIANGLE_STRIP);
		square->InitFromData(vertices, indices);
		return square;

}

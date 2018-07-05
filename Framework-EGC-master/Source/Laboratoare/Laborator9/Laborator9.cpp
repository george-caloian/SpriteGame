#include "Laborator9.h"
#pragma comment(lib, "winmm.lib")
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>
#include <windows.h>
#include <mmsystem.h>
#include <include/rapidxml.hpp>
#include <include/rapidxml_iterators.hpp>
#include <include/rapidxml_utils.hpp>
#include <include/rapidxml_print.hpp>

using namespace rapidxml;
using namespace std;

string Laborator9::spriteName = "sprite111";
string Laborator9::xmlName = "sprite11";

Laborator9::Laborator9(){}
Laborator9::~Laborator9(){}


void Laborator9::Init()
{
	
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, backgroundY, 1));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	{
		//texture background
		
		Texture2D* texture2 = new Texture2D();
		Texture2D* texture = new Texture2D();

		string aux2 = RESOURCE_PATH::TEXTURES + "grass-1.jpg";
		texture2->Load2D(aux2.c_str(), GL_CLAMP_TO_EDGE);
		mapTextures["background2"] = texture2;

	
		string aux = RESOURCE_PATH::TEXTURES + "sky.jpg";
		texture->Load2D(aux.c_str(), GL_CLAMP_TO_EDGE);
		mapTextures["background"] = texture;

	

		//mesh background

		Mesh* background2 = new Mesh("background2");
		Mesh* background = new Mesh("background");

		background2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "background2.obj");
		background->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "background2.obj");

		meshes[background2->GetMeshID()] = background2;
		meshes[background->GetMeshID()] = background;

		


		Laborator9::spriteName = "sprite222";


		Fighter = new Cavaler();
		Fighter2 = new Cavaler();

		mapTextures["Fighter"] = Fighter->texture;
		mapTextures["Fighter2"] = Fighter2->texture;

		meshes[Fighter->mesh->GetMeshID()] = Fighter->mesh;
		meshes[Fighter2->mesh->GetMeshID()] = Fighter2->mesh;
		

		Fighter2->direction = -1;
		Fighter2->setX(1.1f);
		
	}


	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		Shader *shader2 = new Shader("Sprites");

		shader2->AddShader("Source/Laboratoare/Laborator9/Shaders/SpriteVertex.glsl", GL_VERTEX_SHADER);
		shader2->AddShader("Source/Laboratoare/Laborator9/Shaders/SpriteFragment.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	
		shader2->CreateAndLink();
		shader->CreateAndLink();

		shaders[shader2->GetName()] = shader2;

		
		shaders[shader->GetName()] = shader;

	
	
	}

	
}

void Laborator9::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Laborator9::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	


	glm::mat4 modelMatrix = glm::mat4(1);

	float bgy = backgroundY + 0.2;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0,bgy , 0.1));
	float nnt = 90.0f;

	modelMatrix = glm::rotate(modelMatrix, RADIANS(nnt), glm::vec3(0, 1, 0));
	RenderSimpleMesh(meshes["background"], shaders["ShaderLab9"], modelMatrix, mapTextures["background"]);
	
	

	modelMatrix = glm::mat4(1);

	float bgy2 = backgroundY - 0.6;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0,bgy2 , 0.2));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(nnt), glm::vec3(0, 1, 0));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(2.5f, 0.5f, 1.0f));
	RenderSimpleMesh(meshes["background2"], shaders["ShaderLab9"], modelMatrix, mapTextures["background2"]);

	modelMatrix = glm::mat4(1);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(Fighter->valueOnX, Fighter->valueOnY, 0.3));
	nnt = 90.0f;
	modelMatrix = glm::rotate(modelMatrix, RADIANS(nnt), glm::vec3(0, 1, 0));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
	

	//updating frames

	float UpdateTime;
	float reset=0.0f;

	Fighter->getCurrentState();

	float nut2= 1.00f / Fighter->fallingSpeed;
	float nut3 = 1.00f / Fighter->animeSpeed;
	if (Fighter->currentState == Fighter->ATTACK)
	{
		float nut = 1.00f / Fighter->animeSpeed;
		if (Fighter->valueOnX + 0.15f >= Fighter2->valueOnX && Fighter->direction == 1 && (Fighter2->vulnerable || Fighter2->direction == 1))
			Fighter2->setCurrentState(Fighter2->DIE);

		UpdateTime = nut;
	}
	else if (Fighter->currentState == Fighter->DIE)
		UpdateTime = nut2;


	else
	{
		if (Fighter->currentState != Fighter->ATTACK)
			Fighter->block = 0;
		UpdateTime = nut3;
	}
	Fighter->LastSwap += deltaTimeSeconds;
	
	if (Fighter->LastSwap > UpdateTime)
	{
		if (Fighter->currentFrame  > Fighter->nrFrames - 1)
		{
			if (Fighter->currentState == Fighter->ATTACK )
			{
				Fighter->setCurrentState(Fighter->IDLE);
				Fighter->block = 0;
		
			}
		
			if (Fighter->currentState == Fighter->DIE)
			{
				Fighter->setCurrentState(Fighter->IDLE);
				Fighter->block = 0;

				Fighter->setX(-0.6f);
				Fighter->direction = 1;
			}
				
			if (Fighter->currentState != Fighter->DIE)
				if(Fighter->currentFrame != 1)
					Fighter->currentFrame = 1;
			
		}
		else Fighter->currentFrame++;
		Fighter->LastSwap = reset;
	}
	
	Fighter->renderCavaler(modelMatrix, shaders["Sprites"], GetSceneCamera()->GetViewMatrix(), GetSceneCamera()->GetProjectionMatrix());

	modelMatrix = glm::mat4(1);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(Fighter2->valueOnX, Fighter2->valueOnY, 0.3));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(nnt), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));




	float UpdateTime2;
	reset = 0.0f;

	Fighter2->getCurrentState();

	if (Fighter2->currentState == Fighter2->ATTACK)
	{
		if (Fighter2->valueOnX <= Fighter->valueOnX + 0.15f && Fighter2->direction == -1 && (Fighter->vulnerable || Fighter->direction == -1))
			Fighter->setCurrentState(Fighter->DIE);
			
		UpdateTime2 = nut3;
	}
	else if ( Fighter2->currentState == Fighter2->DIE)
		UpdateTime2 = nut2;
	
	else
	{
		if (Fighter2->currentState != Fighter2->ATTACK)
			Fighter2->block = 0;
		UpdateTime2 = nut3;
	}
	

	Fighter2->LastSwap += deltaTimeSeconds;

	if (Fighter2->LastSwap > UpdateTime2)
	{
		if (Fighter2->currentFrame> Fighter2->nrFrames -1)
		{
			if (Fighter2->currentState == Fighter2->ATTACK)
			{

				Fighter2->setCurrentState(Fighter2->IDLE);
				Fighter2->block = 0;
			}
			if (Fighter2->currentState == Fighter2->DIE)
			{
				Fighter2->setCurrentState(Fighter2->IDLE);
				Fighter2->block = 0;

				Fighter2->setX(1.1f);
				Fighter2->direction = -1;

			}

			if (Fighter2->currentState != Fighter2->DIE)
				Fighter2->currentFrame = 1;
		}
		else Fighter2->currentFrame++;
		
		Fighter2->LastSwap = reset;
	}
	Fighter2->renderCavaler(modelMatrix, shaders["Sprites"], GetSceneCamera()->GetViewMatrix(), GetSceneCamera()->GetProjectionMatrix());
}

void Laborator9::FrameEnd(){DrawCoordinatSystem();}

void Laborator9::Cavaler::setX(float x)
{
	
	if (this->valueOnX + x < 0.65f && this->valueOnX + x > -0.6f)
		this->valueOnX += x;
	else if (this->valueOnX + x >= 0.65f)
		this->valueOnX = 0.65f;
	else if (this->valueOnX + x <= -0.6f)
		this->valueOnX = -0.6f;
	
}

void Laborator9::Cavaler::setCurrentState(State state)
{
	this->currentState = state;
}
void Laborator9::Cavaler::renderCavaler(const glm::mat4 & modelMatrix, Shader *shader, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())	return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = ViewMatrix;
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = ProjectionMatrix;
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	//change frames
	int ncf = this->currentFrame - 1;


	int sprite = glGetUniformLocation(shader->program, "sprite");
	int direction = glGetUniformLocation(shader->program, "direction");

	glm::vec4 SpriteXYWH = this->CurrSHT.at(ncf);

	glUniform4f(sprite, SpriteXYWH.x, SpriteXYWH.y, SpriteXYWH.z, SpriteXYWH.w);
	glUniform1i(direction, this->direction);


	if (this->texture)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);

		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, this->texture->GetTextureID());

		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}


	// Draw the object
	glBindVertexArray(this->mesh->GetBuffers()->VAO);
	glDrawElements(this->mesh->GetDrawMode(), static_cast<int>(this->mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Laborator9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {}
void Laborator9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}
void Laborator9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}



void Laborator9::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())	return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		
		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Laborator9::OnInputUpdate(float deltaTime, int mods)
{
	
	if (window->KeyHold(GLFW_KEY_D))
	{
		
		if (Fighter->block == 0)
			if(Fighter->currentState != Fighter->RUN)
				Fighter->setCurrentState(Fighter->RUN);
		
		if (Fighter->direction != 1)
			Fighter->direction = 1;

		if ( Fighter->valueOnX < Fighter2->valueOnX - 0.07f)
			Fighter->setX(Fighter->direction*Fighter->runningSpeed*deltaTime);
	}
	else if (window->KeyHold(GLFW_KEY_A))
	{

		if (Fighter->block == 0)
			if(Fighter->currentState != Fighter->RUN)
				Fighter->setCurrentState(Fighter->RUN);
		
		if(Fighter->direction != -1)
			Fighter->direction = -1;

		float sxpd = Fighter->direction*Fighter->runningSpeed;
		Fighter->setX(sxpd*deltaTime);
	}
	
	if (window->KeyHold(GLFW_KEY_RIGHT))
	{
	
		if (Fighter2->block != 1)
			if(Fighter2->currentState != Fighter2->RUN)
				Fighter2->setCurrentState(Fighter->RUN);
		
		Fighter2->direction = 1;

		float sxpd2 = Fighter2->direction*Fighter2->runningSpeed;
		Fighter2->setX(sxpd2*deltaTime);
	}
	else if (window->KeyHold(GLFW_KEY_LEFT))
	{

		if (Fighter2->block != 1)
			if(Fighter2->currentState != Fighter2->RUN)
				Fighter2->setCurrentState(Fighter2->RUN);
		
		Fighter2->direction = -1;
		if (Fighter2->valueOnX > Fighter->valueOnX + 0.07f)
			Fighter2->setX(Fighter2->direction*Fighter2->runningSpeed*deltaTime);
	}

}

void Laborator9::OnKeyPress(int key, int mods)
{
	if (Fighter->block == 0)
	{

		if (key == GLFW_KEY_W)
		{
			Fighter->setCurrentState(Fighter->ATTACK);
			if(Fighter->currentFrame != 1)
				Fighter->currentFrame = 1;
			if(Fighter->block == 0)
				Fighter->block = 1;
		}


		else if (key == GLFW_KEY_U)
		{
			if (Fighter->animeSpeed > 3.00f)
				Fighter->animeSpeed -= 3.00f;
		}

		else if (key == GLFW_KEY_S)
		{
			Fighter->setCurrentState(Fighter->BLOCK);
			Fighter->vulnerable = false;
			Fighter->currentFrame = 1;
			
			if (Fighter->block == 0)
				Fighter->block = 1;
		}

		else if (key == GLFW_KEY_I)
		{
			Fighter->animeSpeed += 3.00f;
		}
	}

	if (Fighter2->block == 0){}
	{
		if (key == GLFW_KEY_P)
		{
			Fighter2->setCurrentState(Fighter2->ATTACK);
			Fighter2->currentFrame = 1;
			if(Fighter2->block == 0)
				Fighter2->block = 1;
		}
		else if (key == GLFW_KEY_DOWN)
		{
			Fighter2->setCurrentState(Fighter2->BLOCK);
			Fighter2->vulnerable = false;
			Fighter2->currentFrame = 1;
			if (Fighter2->block == 0)
				Fighter2->block = 1;
		}
	}
}

void Laborator9::OnKeyRelease(int key, int mods)
{ 
	if (key == GLFW_KEY_D || key == GLFW_KEY_A || key == GLFW_KEY_S)
	{ 
		Fighter->setCurrentState(Fighter->IDLE);
		if(Fighter->vulnerable == false)
			Fighter->vulnerable = true;
		
	}
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT || key == GLFW_KEY_DOWN)
	{
		Fighter2->setCurrentState(Fighter->IDLE);
		if (Fighter->vulnerable == false)
			Fighter2->vulnerable = true;

	}
}


void Laborator9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY){}
void Laborator9::OnWindowResize(int width, int height){}


Laborator9::Cavaler::Cavaler()
{
	
	Texture2D* Fighter = new Texture2D();
	
	Fighter->Load2D((RESOURCE_PATH::TEXTURES + Laborator9::spriteName+".png").c_str(), GL_CLAMP_TO_EDGE);
	
	this->texture = Fighter;

	Mesh* Fighter1 = new Mesh("Fighter");
	Fighter1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "background2.obj");
	this->mesh = Fighter1;

	
	

	std::string file = RESOURCE_PATH::TEXTURES + Laborator9::xmlName + ".xml";
	const char * c = file.c_str();

	xml_document<> doc;
	xml_node<> * pRoot;

	ifstream theFile(c);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	pRoot = doc.first_node();


	
		for (xml_node<> *pNode2 = pRoot->first_node("frame"); pNode2; pNode2 = pNode2->next_sibling())
		{
			int h = atoi(pNode2->first_attribute("h")->value());
			
			int y = atoi(pNode2->first_attribute("y")->value());
			int x = atoi(pNode2->first_attribute("x")->value());
			int w = atoi(pNode2->first_attribute("w")->value());


			if (atoi(pNode2->first_attribute("name")->value()) == 1)
			{
				this->Attack.push_back(glm::vec4(x, y, w, h));
			}
			
			else if (atoi(pNode2->first_attribute("name")->value()) == 2)
			{
				this->Block.push_back(glm::vec4(x, y, w, h));
			}
			else if (atoi(pNode2->first_attribute("name")->value()) == 3)
			{
				this->Die.push_back(glm::vec4(x, y, w, h));
			}
			else if (atoi(pNode2->first_attribute("name")->value()) == 4)
			{
				this->Idle.push_back(glm::vec4(x, y, w, h));
			}
			else if (atoi(pNode2->first_attribute("name")->value()) == 5)
			{
				this->Run.push_back(glm::vec4(x, y, w, h));
			}
		
		
		
	}



	//Idle initially
	this->currentState = IDLE;
	this->valueOnX = -0.60f;
	this->currentFrame = 1;
	
	this->valueOnY = 2.00f;
	this->direction = 1;
	this->getCurrentState();
}


void Laborator9::Cavaler::getCurrentState()
{

	if (this->currentState == IDLE)
	{
		this->nrFrames = IDLE_FRAMES;
		this->CurrSHT = this->Idle;
	}
	else if (this->currentState == ATTACK)
	{
		this->nrFrames = ATTACK_FRAMES;
		this->CurrSHT = this->Attack;
	}
	else if (this->currentState == RUN)
	{
		this->nrFrames = RUN_FRAMES;
		this->CurrSHT = this->Run;
	}

	
	else if (this->currentState == BLOCK)
	{
		this->nrFrames = BLOCK_FRAMES;
		this->CurrSHT = this->Block;
	}
	else if (this->currentState == DIE)
	{
		this->nrFrames = DEAD_FRAMES;
		this->CurrSHT = this->Die;
	}

	

}



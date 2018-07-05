#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <Laboratoare/Laborator3/Object2D.h>
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

class Laborator9 : public SimpleScene
{
	public:
		Laborator9();
		~Laborator9();

		void Init() override;

	private:

		struct Cavaler
		{
		public:
			Mesh* mesh;
			Texture2D* texture;

			int direction;
			int block;
			float valueOnX;
			float valueOnY;
			
			bool vulnerable = true;
			
			int currentFrame;
			int nrFrames;

			enum State{ IDLE , RUN , ATTACK, DIE, BLOCK };
			enum frameNumbers { IDLE_FRAMES = 10 , DEAD_FRAMES = 10, ATTACK_FRAMES = 10, RUN_FRAMES = 10 , BLOCK_FRAMES = 1};
			State currentState;

			std::vector<glm::vec4> Attack;
			std::vector<glm::vec4> Die;
			std::vector<glm::vec4> Block;
			std::vector<glm::vec4> CurrSHT;
			std::vector<glm::vec4> Idle;
			std::vector<glm::vec4> Run;

			

			float runningSpeed = 0.2f;
			float LastSwap = 0.0f;
			float fallingSpeed = 9.00f;
	
			float animeSpeed = 16.0f;

			Cavaler();
			
			void setX(float x);
			void setY(float y);
			void setCurrentState(State state);
			void getCurrentState();

			void renderCavaler(const glm::mat4 & modelMatrix, Shader *shader, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);
			

		};

		static std::string xmlName;
		
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* texture1 = NULL);
		
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		

		Cavaler* Fighter;
		Cavaler* Fighter2;

		static std::string spriteName;
		float backgroundY = 2.00f;
		std::unordered_map<std::string, Texture2D*> mapTextures;
	
		GLuint randomTextureID;
		
	
		
};

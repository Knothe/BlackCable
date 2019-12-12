#include "Menu.h"
#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Menu::Menu()
{

}

Menu::~Menu()
{
	delete plane;
}

void Menu::Init()
{
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::getPtr();
	shaderManager = ShaderManager::getPtr();
	shaderManager->LoadShaders("phong", "Assets/Shaders/Default/phong-shader.vert", "Assets/Shaders/Default/phong-shader.frag");
	shaderManager->LoadShaders("gouraud", "Assets/Shaders/Default/gouraud-shader.vert", "Assets/Shaders/Default/gouraud-shader.frag");
	plane = new PlaneModel();
	plane->Init();
	camera = new Camera(glm::vec3(-1.4f, 10.0f, -1.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);

	//camera = new Camera(glm::vec3(-1.4f, 10.0f, -1.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0, 0);
	shaderManager->initShader(camera);

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/right.jpg");
	skyboxFaces.push_back("Assets/Textures/Skybox/left.jpg");
	skyboxFaces.push_back("Assets/Textures/Skybox/top.jpg");
	skyboxFaces.push_back("Assets/Textures/Skybox/bottom.jpg");
	skyboxFaces.push_back("Assets/Textures/Skybox/front.jpg");
	skyboxFaces.push_back("Assets/Textures/Skybox/back.jpg");
	skybox = Skybox(skyboxFaces);

}

void Menu::Draw()
{
	platform->RenderClear();

	skybox.Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

	shaderManager->Activate("phong");
	shaderManager->draw();
	plane->Draw();


	platform->RenderPresent();
}

bool Menu::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
		camera->mouseControl(x, y);
	return false;
}

bool Menu::Input(std::map<int, bool> keys)
{
	if (keys[GLFW_KEY_ENTER])
		manager->SetState(new Game());
	return false;
}

void Menu::Restart() {
	shaderManager->initShader(camera);
}


void Menu::Update()
{

}

void Menu::Close()
{
	std::cout << " Close Init" << std::endl;
}
#include "Game.h"
#include<iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>



Game::Game()
{
	
}

Game::~Game()
{
	delete player;
}

void Game::Init()
{
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::getPtr();
	shaderManager = ShaderManager::getPtr();
	//shaderManager->LoadShaders("phong", "Assets/Shaders/Default/phong-shader.vert", "Assets/Shaders/Default/phong-shader.frag");
	//shaderManager->LoadShaders("gouraud", "Assets/Shaders/Default/gouraud-shader.vert", "Assets/Shaders/Default/gouraud-shader.frag");
	player = new Player(glm::vec3(0, 0, 0));
	player->Init(&enemyPool);

 	field = new Model();
	field->LoadModel("Assets/Models/Field.obj");
	field->AddTexture("Field.png");
	field->SetTransform(new Transform(glm::vec3( 0, 0, 0), glm::vec3( 0, 0, 0), glm::vec3(200, 100, 200)));

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_rt.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_lf.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_up.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_dn.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_bk.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_ft.tga");

	skybox = Skybox(skyboxFaces);
	level = 1;
	CreateEnemies();
}

void Game::Draw()
{
	platform->RenderClear();
	skybox.Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());
	
	shaderManager->Activate("phong");
	shaderManager->draw();

	player->Draw();
	field->Draw();

	for (auto enemy : enemyPool)
	{
		if(enemy->GetActive())
			enemy->Draw();
	}
	platform->RenderPresent();
}

bool Game::MouseInput(int x, int y, bool leftbutton)
{
	player->MouseInput(x, y, leftbutton);

	return false;
}

bool Game::Input(std::map<int, bool> keys)
{
	player->Input(keys);
	return false;
}

void Game::Update()
{
	bool hasEnemies = false;
	for (auto enemy : enemyPool)
	{
		if (enemy->GetActive()) {
			enemy->Update();
			hasEnemies = true;
		}
	}
	if (player->Update())
		state = false;
	if (!hasEnemies)
		MoveEnemies();
}

void Game::CreateEnemies()
{
	while (enemyPool.size() < 10)
	{
		if (rand() % 100 < 1)
		{
			int dir = -1;
			if (rand() % 100 > 50)
				dir = 1;
			auto enemy = new EnemyT4(glm::vec3(rand() % 100 * dir, 6, rand() % 100 * dir), player);
			enemy->Init();
			enemyPool.push_back(enemy);
		}

		if (rand() % 100 < 1)
		{
			int dir = -1;
			if (rand() % 100 > 50)
				dir = 1;
			auto enemy = new EnemyT5(glm::vec3(rand() % 100 * dir, 10, rand() % 100 * dir), player);
			enemy->Init();
			enemyPool.push_back(enemy);
		}
	}
}

void Game::MoveEnemies() {
	level++;
	for (auto enemy : enemyPool) {
		int dir = -1;
		if (rand() % 100 > 50)
			dir = 1;
		enemy->SetTranslation(glm::vec3(rand() % 100 * dir, 10, rand() % 100 * dir));
		enemy->SetActive(true);
		enemy->SetSpeed(0.002f * level);
	}
}

void Game::Restart() {

}


void Game::Close()
{

	
	std::cout << " Close Init" << std::endl;
}

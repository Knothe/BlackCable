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
	player = new Player(glm::vec3(0, 0, 0));
	player->Init(&enemyPool);

	item = new Item();
	item->UpdatePosition(glm::vec3((rand() % 200) - 100, 7, (rand() % 200) - 100));

 	field = new Model();
	field->LoadModel("Assets/Models/Field.obj");
	field->AddTexture("Field.png");
	field->SetTransform(new Transform(glm::vec3( 0, 0, 0), glm::vec3( 0, 0, 0), glm::vec3(200, 100, 200)));
	gem = new Model();
	gem->LoadModel("Assets/Models/Gem.obj");
	gem->AddTexture("Gem.png");
	gem->SetTransform(new Transform(glm::vec3( 0, 0, 0), glm::vec3( 0, 0, 0), glm::vec3(5, 5, 5)));

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_rt.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_lf.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_up.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_dn.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_bk.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/sorbin_ft.tga");
	enemies = 0;
	skybox = Skybox(skyboxFaces);
	CreateEnemies();
}

void Game::Draw()
{
	platform->RenderClear();
	skybox.Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());
	
	shaderManager->Activate("phong");
	shaderManager->draw();
	gem->Draw();
	player->Draw();
	field->Draw();
	item->Draw();
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
		else
			MoveEnemies(enemy);
	}

	if (item->CheckCollision(player->GetCollider())) {
		item->UpdatePosition(glm::vec3((rand() % 200) - 100, 7, (rand() % 200) - 100));
		player->PlayRecharge();
	}

	if (player->Update())
		state = false;
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

void Game::MoveEnemies(Enemy* e) {
	enemies++;
	int dir1, dir2;
	dir1 = -1;
	dir2 = -1;

	if (rand() % 100 > 50) {
		dir1 = 1;
		if (rand() % 100 > 50) 
			dir2 = 1;
	}
	else {
		if (rand() % 100 > 50) 
			dir2 = 1;
	}
		
	e->SetTranslation(glm::vec3((rand() % 50 + 50) * dir1, 10, (rand() % 50 + 50) * dir2));
	e->SetActive(true);
	e->SetSpeed(0.002f * enemies / 2);
	
}

void Game::Restart() {

}


void Game::Close()
{

	
	std::cout << " Close Init" << std::endl;
}

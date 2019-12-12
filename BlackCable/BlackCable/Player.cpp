#include "Player.h"
#include <stack>

Player::Player(glm::vec3 position)
{
	this->platform = Platform::GetPtr();
	camera = Camera(glm::vec3(-1.4f, 7.0f, -1.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);
	ShaderManager* shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(&camera);
	glm::vec3 offset = glm::vec3(3, -1, 0);
	distanceOffset = glm::length(glm::vec3(offset.x, 0, offset.y));
	offsetY = offset.y;
	shoot = false;
}

void Player::Init(std::list<Enemy*> *enemyPool)
{
	this->enemyPool = enemyPool;
	weapon = new Model();
	weapon->LoadModel("Assets/Models/Weapon.obj");
	weapon->AddTexture("Weapon_UV.png");
	spCollider = new SphereCollider(2, camera.getCameraPosition());
}

void Player::MouseInput(int x, int y, bool leftbutton)
{
	shoot = leftbutton;
	if (x != -1 || y != -1)
		camera.mouseControl(x, y);
}

void Player::Input(const std::map<int, bool>& keys)
{
	camera.keyControl(keys, platform->GetDeltaTime());
}

bool Player::Update()
{
	spCollider->SetTranslation(camera.getCameraPosition());
	if (shoot) {
		Shoot(0, 0);
		shoot = false;
	}
	for (auto ene : *enemyPool)
	{
		if (spCollider->CheckCollision(ene->GetRadius(), ene->GetTranslation()))
		{
			return true;
		}
	}
	return false;
}

void Player::Draw()
{
	glm::vec3 position = camera.getCameraPosition();
	glm::vec3 rotation = camera.getCameraRotation();

	float angleOffset = glm::atan(rotation.x, rotation.z);

	transform.SetScale(1.1f, 1.1f, 1.11f);
	transform.SetRotation(0, angleOffset + 1.57f, 0);
	transform.SetTranslation(position.x + (distanceOffset * rotation.x), position.y + offsetY, position.z + (distanceOffset * rotation.z));
	weapon->SetTransform(&transform);
	weapon->Draw();
}

glm::vec3 Player::GetPosition() {
	return camera.getCameraPosition();
}

void Player::Shoot(int x, int y)
{
	Enemy* closest = NULL;
	int nearest = -1;
	for (auto ene : *enemyPool)
	{
		if (ene->GetActive()) {
			if (ShootCollide(ene, nearest)) 
				closest = ene;
		}
		
	}
	if(closest)
		closest->SetActive(false);
}

bool Player::ShootCollide(Enemy* e, int nearest) {
	glm::vec3 shot;
	glm::vec3 enem; 
	shot = camera.getCameraRotation();
	enem = e->GetTranslation() - camera.getCameraPosition();
	enem.y = 0;
	float n = glm::length(shot);
 	n = (glm::dot(shot, enem) / (n * n));
	if (n < 0)
		return false;
	glm::vec3 res;
	res = n * glm::normalize(shot);
	n = glm::distance(res, enem);
	if (n <= e->GetRadius()) {
		if (nearest == -1)
			return true;
		else if (glm::length(enem) < nearest)
			return true;
	}
	return false;
}
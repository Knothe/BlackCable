#include "EnemyT5.h"

EnemyT5::EnemyT5(glm::vec3 position, Player *player)
{
	this->player = player;
	this->platform = Platform::GetPtr();
	transform.SetTranslation(position.x, position.y, position.z);
}

void EnemyT5::Update()
{
	movement = player->GetPosition() - transform.GetTranslation();
	movement.y = 0;
	movement = glm::normalize(movement);
	rotation = glm::atan(movement.x, movement.z);
	movement = movement * speed;
	spCollider->SetTranslation(transform.GetTranslation());
}

void EnemyT5::Init()
{
	weapon = new Model();
	weapon->LoadModel("Assets/Models/Enemy2.obj");
	weapon->AddTexture("Enemy2.png");
	spCollider = new SphereCollider(3, transform.GetTranslation());
}

void EnemyT5::Draw()
{
	transform.UpdateTranslation(movement.x, 0, movement.z);
	transform.SetScale(2.5f, 2.5f, 2.5f);
	transform.SetRotation(0, rotation - 3.1416f, 0);
	weapon->SetTransform(&transform);
	weapon->Draw();
}
void EnemyT5::Shoot()
{

}
#include "EnemyT4.h"

EnemyT4::EnemyT4(glm::vec3 position, Player *player)
{
	this->player = player;
	this->platform = Platform::GetPtr();
	transform.SetTranslation(position.x, position.y, position.z);
}

void EnemyT4::Update()
{
	movement = player->GetPosition() - transform.GetTranslation();
	movement.y = 0;
	movement = glm::normalize(movement);
	rotation = glm::atan(movement.x, movement.z);
	movement = movement * speed;
	spCollider->SetTranslation(transform.GetTranslation());
}

void EnemyT4::Init()
{
	weapon = new Model();
	weapon->LoadModel("Assets/Models/Enemy1.obj");
	weapon->AddTexture("Enemy1.png");
	spCollider = new SphereCollider(3, transform.GetTranslation());
}

void EnemyT4::Draw()
{
	
	transform.UpdateTranslation(movement.x, 0, movement.z);
	transform.SetScale(2, 2, 2);
	transform.SetRotation(0, rotation, 0);
	weapon->SetTransform(&transform);
	weapon->Draw();
}
void EnemyT4::Shoot()
{

}
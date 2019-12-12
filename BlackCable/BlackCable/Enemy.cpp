#include "Enemy.h"


void Enemy::SetTranslation(glm::vec3 p) {
	glm::vec3 translation = transform.GetTranslation();
	transform.SetTranslation(p.x, translation.y, p.z);
	spCollider->SetTranslation(transform.GetTranslation());
}
glm::vec3 Enemy::GetTranslation()
{
	return spCollider->GetTranslation();
}
float Enemy::GetRadius()
{
	return spCollider->GetRadius();
}
void Enemy::SetActive(bool a) {
	isActive = a;
}
bool Enemy::GetActive() {
	return isActive;
}

void Enemy::SetSpeed(float s) {
	speed = s;
}

#include "Item.h"
Item::Item() {
	model = new Model();
	model->LoadModel("Assets/Models/Box.obj");
	model->AddTexture("Caja.png");
	model->SetTransform(&transform);
	transform.SetScale(2, 2, 2);
	spCollider = new SphereCollider(2, glm::vec3(0,0,0));
	
}

bool Item::CheckCollision(SphereCollider* other) {
	return spCollider->CheckCollision(other->GetRadius(), other->GetTranslation());
}

void Item::UpdatePosition(glm::vec3 pos) {
	transform.SetTranslation(pos.x, pos.y, pos.z);
	spCollider->SetTranslation(pos);

}

void Item::Draw() {
	model->Draw();
}
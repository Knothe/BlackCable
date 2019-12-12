#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <map>
#include "BCE/Graphic/Camera.h"
#include "BCE/Graphic/Model.h"
#include "BCE/Base/Platform.h"
#include "BCE/Base/ShaderManager.h"
#include "BCE/Physics/SphereCollider.h"
#include "Player.h"

class Item
{
private:
	bool isActive;
	Model* model;
	Transform transform;
	SphereCollider * spCollider;
public:
	Item();
	bool CheckCollision(SphereCollider* other);
	void UpdatePosition(glm::vec3 pos);
	void Draw();

};


#ifndef ENEMY_H 
#define ENEMY_H 

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <map>
#include "BCE/Graphic/Camera.h"
#include "BCE/Graphic/Model.h"
#include "BCE/Base/Platform.h"
#include "BCE/Base/ShaderManager.h"
#include "BCE/Physics/SphereCollider.h"


using namespace BCE::Base;
using namespace BCE::Graphics;

class Player;

class Enemy
{
protected:
	int life;
	int ammo;
	bool isActive = true;
	float speed = 0.01f;
	Model *weapon;
	Platform* platform;
	Transform transform;
	Player* player;
	SphereCollider* spCollider;
public:
	glm::vec3 GetTranslation();
	float GetRadius();
	virtual void Init() = 0;
	virtual void Update()=0;
	virtual void Draw() = 0;
	void SetTranslation(glm::vec3 p);
	void SetActive(bool a);
	bool GetActive();
	void SetSpeed(float s);
private:
	virtual void Shoot() = 0;
};

#endif // ! 


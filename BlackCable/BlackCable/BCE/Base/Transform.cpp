#include "Transform.h"
namespace BCE
{
	namespace Base
	{
		Transform::Transform() : _model(1)
		{
			_translation = glm::vec3(0, 0, 0);
			_rotation = glm::vec3(0, 0, 0);
			_scale = glm::vec3(1, 1, 1);
		}

		Transform::Transform(glm::vec3 t, glm::vec3 r, glm::vec3 s){
			_translation = t;
			_rotation = r;
			_scale = s;
		}


		void Transform::SetTranslation(float x, float y, float z)
		{
			_translation.x = x;
			_translation.y = y;
			_translation.z = z;
		}
			
		void Transform::UpdateTranslation(float x, float y, float z)
		{
 			_translation.x += x;
			_translation.y += y;
			_translation.z += z;
		}

		void Transform::SetRotation(float x, float y, float z)
		{
			_rotation.x = x;
			_rotation.y = y;
			_rotation.z = z;
		}

		void Transform::SetScale(float x, float y, float z)
		{
			_scale.x = x;
			_scale.y = y;
			_scale.z = z;
		}

		glm::vec3 Transform::GetTranslation()
		{
			return _translation;
		}

		glm::mat4 Transform::GetTransform()
		{
			_model = glm::mat4(1.0);
			_model = glm::translate(_model, _translation);
			_model = glm::scale(_model, _scale);
			_model = glm::rotate(_model, _rotation.x, glm::vec3(1, 0, 0));
			_model = glm::rotate(_model, _rotation.y, glm::vec3(0, 1, 0));
			_model = glm::rotate(_model, _rotation.z, glm::vec3(0, 0, 1));
			return _model;
		}
	}
}
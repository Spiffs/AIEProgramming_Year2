#pragma once
#include <glm/glm.hpp>
#include "RenderTarget.h"

class Camera;
class Scene;

namespace aie
{
	class OBJMesh;
	class ShaderProgram;
}

class Instance
{
public:
	Instance(glm::mat4 a_transform, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);
	Instance(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);
	Instance(glm::vec3 a_position, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);

	void Draw(Scene* a_scene, aie::RenderTarget* a_renderTarget);
	
	static glm::mat4 MakeTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale);
	// set transform of the object and must return a mat4 to set the GraphicsProjectApp transform of the instance
	glm::mat4 SetTransform(glm::mat4 a_transform) { return m_transform = a_transform; }

protected:
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

};


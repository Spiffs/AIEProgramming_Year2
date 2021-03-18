#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "OBJMesh.h"
#include "Scene.h"
#include "Instance.h"

#include <glm/mat4x4.hpp>

class GraphicsProjectApp : public aie::Application {
public:

	GraphicsProjectApp();
	virtual ~GraphicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void SolarSystem(float dt);

protected:
	Camera m_camera;

	// Camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;
	aie::Texture m_soulspearTexture;

	// --- SHADER ---
	aie::ShaderProgram m_simpleShader;	
	aie::ShaderProgram m_bunnyShader;
	aie::ShaderProgram m_dragonShader;
	aie::ShaderProgram m_buddhaShader;
	aie::ShaderProgram m_lucyShader;
	aie::ShaderProgram m_soulspearShader;
	aie::ShaderProgram m_grenadeShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_textureShader;
	aie::ShaderProgram m_normalMapShader;
	// --------------
	// Basic Plane
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	// Create a Bunny with a flat color
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	// Create a Dragon with a flat color
	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;
	// Create a Buddha with a flat color
	aie::OBJMesh m_buddhaMesh;
	glm::mat4 m_buddhaTransform;
	// Create a Lucy with a flat color
	aie::OBJMesh m_lucyMesh;
	glm::mat4 m_lucyTransform;
	// Create a Soulspear with a flat color
	aie::OBJMesh m_soulspearMesh;
	glm::mat4 m_soulspearTransform;
	// Create a dingding with a flat color
	aie::OBJMesh m_grenadeMesh;
	glm::mat4 m_grenadeTransform;

	Scene* m_scene;

	/*struct Light
	{
		glm::vec3 direciton;
		glm::vec3 color; 
	};

	Light m_light;
	glm::vec3 m_ambientLight;*/

public:
	bool LoadShaderAndMeshLogic(Light a_light);
	//void DrawShaderAndMeshes(glm::mat4, glm::mat4);
	void IMGUI_Logic();
};
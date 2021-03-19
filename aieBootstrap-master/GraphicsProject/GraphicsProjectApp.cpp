#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include "Input.h"

#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <imgui.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsProjectApp::GraphicsProjectApp()
{

}

GraphicsProjectApp::~GraphicsProjectApp()
{

}

bool GraphicsProjectApp::startup()
{
	setBackgroundColor(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);


	Light light;
	light.m_color = { 1, 1, 1 };
	light.m_direction = { 1, -1, 1 };

	return LoadShaderAndMeshLogic(light);
}

void GraphicsProjectApp::shutdown()
{
	Gizmos::destroy();
	delete m_scene;
}

void GraphicsProjectApp::update(float deltaTime)
{
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	IMGUI_Logic();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	m_camera.Update(deltaTime);

	float time = getTime();

	m_scene->SetLightDirection(glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0)));


	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsProjectApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	glm::mat4 projectionMatrix = m_camera.GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_camera.GetViewMatrix();

	// update perspective based on screen size
	// m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	//DrawShaderAndMeshes(projectionMatrix, viewMatrix);

	m_scene->Draw();

	Gizmos::draw(projectionMatrix * viewMatrix);
}

void GraphicsProjectApp::SolarSystem(float dt)
{
	// Sun
	Gizmos::addSphere(glm::vec3(0, 0, 0), 1.0f, 16, 16, glm::vec4(1, 0.8, 0, 1));

	//Mercury
	/*glm::vec3 mercuryPos = glm::rotate(10.0f, glm::vec3(2, 0, 0));*/
	Gizmos::addSphere(glm::vec3(2, 0, 0), 0.15f, 16, 16, glm::vec4(1, 0.8, 0, 1));
}

bool GraphicsProjectApp::LoadShaderAndMeshLogic(Light a_light)
{
#pragma region Quad
	// Load the vertex shader from a file
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	// Load the fragment shader from a file
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (!m_simpleShader.link())
	{
		printf("Simple Shader had an error: %s\n", m_simpleShader.getLastError());
		return false;
	}

	// Define the 6 vertices for the 2 triangles that make the quad
	//Mesh::Vertex verticesNoIndex[6];
	//verticesNoIndex[0].position = { -0.5f, 0.0f,  0.5f, 1.0f };
	//verticesNoIndex[1].position = { 0.5f, 0.0f,  0.5f, 1.0f };
	//verticesNoIndex[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };

	//verticesNoIndex[3].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	//verticesNoIndex[4].position = { 0.5f, 0.0f,  0.5f, 1.0f };
	//verticesNoIndex[5].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0.0f,  0.5f, 1.0f };
	vertices[1].position = { 0.5f, 0.0f,  0.5f, 1.0f };
	vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	vertices[3].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	m_quadMesh.InitialiseQuad();
	//m_quadMesh.Initialise(6, vertices, 6, indices);

	// We will make the quad 10 units by 10 units 
	m_quadTransform = {
		10,  0,  0,  0,
		 0, 10,  0,  0,
		 0,  0, 10,  0,
		 0,  0,  0,  1
	};

	/*m_quadTransform = glm::rotate(m_quadTransform, glm::radians(90.0f), glm::vec3(1, 0, 0));*/

#pragma endregion

#pragma region FlatBunny
	// Load the vertex shader from a file
	//m_bunnyShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	//// Load the fragment shader from a file
	//m_bunnyShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	//if (!m_bunnyShader.link())
	//{
	//	printf("Bunny Shader had an error: %s\n", m_bunnyShader.getLastError());
	//	return false;
	//}

	

#pragma endregion

#pragma region PhongShader

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Phong Shader had an error: %s\n", m_phongShader.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Failed!\n");
		return false;
	}

	m_bunnyTransform = {
		0.5f,     0,     0,  0,
		   0,  0.5f,     0,  0,
		   0,     0,  0.5f,  0,
		  -10,     0,     0,  1
	};

#pragma endregion

#pragma region TextureShader


#pragma endregion

#pragma region NormalMapShader

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalMap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalMap.frag");
	if (m_normalMapShader.link() == false)
	{
		printf("Norma.lMap Shader had an error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

#pragma endregion

#pragma region GridLogic

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load: numbered_grid.tga\n");
		return false;
	}

#pragma endregion

#pragma region SoulSpearLogic

	// object
	if (m_soulspearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Failed!\n");
		return false;
	}

	m_soulspearTransform = {
		0.5f,     0,     0,    0,
		   0,  0.5f,     0,    0,
		   0,     0,  0.5f,    0,
		   0,     0,     0,    1
	};

#pragma endregion

#pragma region GrenadeLogic

	// loading object
	if (m_grenadeMesh.load("./stanford/Grenade/Hand_Grenade.obj", true, true) == false)
	{
		printf("Grenade Mesh Failed!\n");
		return false;
	}

	m_grenadeTransform = {
		25,     0,     0,    0,
		 0,    25,     0,    0,
		 0,     0,    25,    0,
		 0,     0.5f,    -5,    1
	};

#pragma endregion

#pragma region DragonShader
	m_dragonShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");

	// Load the fragment shader from a file
	m_dragonShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (!m_dragonShader.link())
	{
		printf("Dragon Shader had an error: %s\n", m_dragonShader.getLastError());
		return false;
	}

	if (m_dragonMesh.load("./stanford/dragon.obj") == false)
	{
		printf("Dragon Mesh Failed!\n");
		return false;
	}

	m_dragonTransform = {
		0.5f,     0,     0,  0,
		   0,  0.5f,     0,  0,
		   0,     0,  0.5f,  0,
		   0,     0,     7,  1
	};


#pragma endregion

#pragma region BuddhShader
	m_buddhaShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");

	// Load the fragment shader from a file
	m_buddhaShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (!m_buddhaShader.link())
	{
		printf("Buddha Shader had an error: %s\n", m_buddhaShader.getLastError());
		return false;
	}

	if (m_buddhaMesh.load("./stanford/buddha.obj") == false)
	{
		printf("Buddha Mesh Failed!\n");
		return false;
	}

	m_buddhaTransform = {
		0.5f,     0,     0,  0,
		   0,  0.5f,     0,  0,
		   0,     0,  0.5f,  0,
		   0,     0,     -7,  1
	};
#pragma endregion

#pragma region LucyShader
	m_lucyShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");

	// Load the fragment shader from a file
	m_lucyShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (!m_lucyShader.link())
	{
		printf("Lucy Shader had an error: %s\n", m_lucyShader.getLastError());
		return false;
	}

	if (m_lucyMesh.load("./stanford/lucy.obj") == false)
	{
		printf("Lucy Mesh Failed!\n");
		return false;
	}

	m_lucyTransform = {
		0.5f,     0,     0,  0,
		   0,  0.5f,     0,  0,
		   0,     0,  0.5f,  0,
		  7,     0,     0,  1
	};
#pragma endregion


	// creating SoulSpears
	m_scene = new Scene(&m_camera, glm::vec2(getWindowWidth(), getWindowHeight()), a_light, glm::vec3(0.25f));

	m_scene->AddInstance(new Instance(m_soulspearTransform, &m_soulspearMesh, &m_normalMapShader));

	// creating a granade
	m_scene->AddInstance(new Instance(m_grenadeTransform, &m_grenadeMesh, &m_normalMapShader));

	m_scene->AddInstance(new Instance(m_bunnyTransform, &m_bunnyMesh, &m_phongShader));

	// creating lights
	// creating a red light
	m_scene->GetPointLights().push_back(Light(vec3(5, 3, 0), vec3(1, 0, 0), 50));
	// creating a green light
	m_scene->GetPointLights().push_back(Light(vec3(-5, 3, 0), vec3(0, 1, 0), 50));

	return true;
}

void GraphicsProjectApp::IMGUI_Logic()
{
	ImGui::Begin("Scene Light Settings");
	ImGui::DragFloat3("Sunlight Direction", &m_scene->GetLight().m_direction[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Sunlight Color", &m_scene->GetLight().m_color[0], 0.1f, 0.0f, 2.0f);
	ImGui::End();
}

#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <iostream>

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
	//delete m_renderTarget;
	delete m_Renderer2D;
	delete m_fontSize12;
	delete m_fontSize30;
}

bool GraphicsProjectApp::startup()
{
	setBackgroundColor(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	m_renderTarget = new aie::RenderTarget();
	m_Renderer2D = new aie::Renderer2D();
	m_fontSize12 = new aie::Font("../bin/font/SuperLegendBoy.ttf", 12);
	m_fontSize30 = new aie::Font("../bin/font/SuperLegendBoy.ttf", 30);

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

	// get input instance
	aie::Input* input = aie::Input::getInstance();

	// quit if we press escape
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// debuging
	if (input->isKeyUp(aie::INPUT_KEY_V))
		m_debugTimer = true;

	if (input->isKeyDown(aie::INPUT_KEY_V) && m_debugTimer)
	{
		m_debugTimer = false;
		if (m_debug)
			m_debug = false;
		else
			m_debug = true;
	}

	// post processing :)
	if (input->isKeyUp(aie::INPUT_KEY_B))
		m_postProcessingTimer = true;

	if (input->isKeyDown(aie::INPUT_KEY_B) && m_postProcessingTimer)
	{
		m_postProcessingTimer = false;
		if (m_postProcessingEnabled)
			m_postProcessingEnabled = false;
		else
			m_postProcessingEnabled = true;
	}
}

void GraphicsProjectApp::draw()
{
	// bind the render target
	m_renderTarget->bind();

	// wipe the screen to the background colour
	clearScreen();

	glm::mat4 projectionMatrix = m_camera.GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_camera.GetViewMatrix();

	// Text GUI
	m_Renderer2D->begin();

	m_Renderer2D->drawText(m_fontSize12, "Press V For Debug", 5, 5);

	std::string s = std::to_string(m_camera.GetSelectedCamera() + 1);
	const char* cameranum = s.c_str();
	m_Renderer2D->drawText(m_fontSize30, "Camera: ", 5, 25);
	m_Renderer2D->drawText(m_fontSize30, cameranum, 170, 25);

	m_Renderer2D->end();

	// rest of draw
	m_scene->Draw();

	if (m_postProcessingEnabled)
	{
		// clear the back buffer
		clearScreen();

		// bindpost shader and textures
		m_postProcessingShader.bind();
		m_postProcessingShader.bindUniform("colourTarget", 0);
		m_renderTarget->getTarget(0).bind(0);

		// draw fullscreen quad
		m_postProcessingQuad.Draw();
	}

	// unbind the render target and return to backbuffer 
	m_renderTarget->unbind();

	// clear screen once more
	clearScreen();

	Gizmos::draw(projectionMatrix * viewMatrix);


}

bool GraphicsProjectApp::LoadShaderAndMeshLogic(Light a_light)
{
#pragma region RenderTarget

	if (m_renderTarget->initialise(1, getWindowWidth(), getWindowHeight()) == false)
	{ 
		printf("Render Target Error!\n"); 
		return false; 
	}

#pragma endregion


#pragma region PostProcessing

	m_postProcessingQuad.initialiseFullscreenQuad();

	// loading the post process vertex shader
	m_postProcessingShader.loadShader(aie::eShaderStage::VERTEX, "../bin/shaders/post.vert");
	
	// loading the post process fragment shader
	m_postProcessingShader.loadShader(aie::eShaderStage::FRAGMENT, "../bin/shaders/post.frag");

	if (!m_postProcessingShader.link())
	{
		printf("Post Process shader had an error : %s\n", m_postProcessingShader.getLastError());
		return false;
	}

#pragma endregion

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

	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0.0f,  0.5f, 1.0f };
	vertices[1].position = { 0.5f, 0.0f,  0.5f, 1.0f };
	vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	vertices[3].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	m_quadMesh.InitialiseQuad();

#pragma endregion

#pragma region PhongShader

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Phong Shader had an error: %s\n", m_phongShader.getLastError());
		return false;
	}

#pragma endregion

#pragma region BunnyLogic

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Failed!\n");
		return false;
	}

	// bunny 
	m_bunnyTransform = {
	0.5f,     0,     0,  0,
	   0,  0.5f,     0,  0,
	   0,     0,  0.5f,  0,
	  -10,     0,     0,  1
	};

#pragma endregion

#pragma region NormalMapShader

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalMap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalMap.frag");
	if (m_normalMapShader.link() == false)
	{
		printf("NormalMap Shader had an error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

#pragma endregion

#pragma region GridLogic

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load: numbered_grid.tga\n");
		return false;
	}

	// We will make the quad 10 units by 10 units 
	m_quadTransform = {
		10,  0,  0,  0,
		 0, 10,  0,  0,
		 0,  0, 10,  0,
		 0,  0,  0,  1
	};

#pragma endregion

#pragma region SoulSpearLogic

	// object
	if (m_soulspearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Failed!\n");
		return false;
	}

	// soulspear
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

	// grenade
	m_grenadeTransform = {
	25,     0,     0,    0,
	 0,    25,     0,    0,
	 0,     0,    25,    0,
	 0,     0.5f,    -5,    1
	};

#pragma endregion

	m_scene = new Scene(&m_camera, glm::vec2(getWindowWidth(), getWindowHeight()), a_light, glm::vec3(0.25f), m_renderTarget);

	// creating soulspear
	m_scene->AddInstance(new Instance(m_soulspearTransform, &m_soulspearMesh, &m_normalMapShader));

	// creating a granade
	m_scene->AddInstance(new Instance(m_grenadeTransform, &m_grenadeMesh, &m_normalMapShader));

	// creating bunny
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
#pragma region ImGui Lights

	ImGui::Begin("Scene Light Settings", 0);

	ImGui::Text("Sun Light");
	// sunlight direciton
	static glm::vec3 sunlightDirection(1, 1, 1);
	ImGui::SliderFloat3("Sunlight Direction", &sunlightDirection.x, -1.0f, 1.0f);
	m_scene->SetLightDirection(sunlightDirection);

	// sunlight color
	static glm::vec3 sunlightColor(1, 1, 1);
	ImGui::SliderFloat3("Sunlight Color", &sunlightColor.x, 0.0f, 2.0f);
	m_scene->SetLightColor(sunlightColor);

	// point lights
	ImGui::Separator();
	ImGui::Text("");
	ImGui::Text("Point Light 1");

	// point light one
	static glm::vec3 pointOnePosition(5, 3, 0);
	ImGui::DragFloat3("Point Light One Position", &pointOnePosition.x);

	static glm::vec3 pointOneColor(2, 0, 0);
	ImGui::SliderFloat3("Point Light One Color", &pointOneColor.x, 0.0f, 2.0f);

	m_scene->SetPointLightVariables(0, pointOnePosition, pointOneColor);

	ImGui::Text("");
	ImGui::Text("Point Light 2");

	// point light two
	static glm::vec3 pointTwoPosition(-5, 3, 0);
	ImGui::DragFloat3("Point Light Two Position", &pointTwoPosition.x, -1.0f, 1.0f);

	static glm::vec3 pointTwoColor(0, 2, 0);

	ImGui::SliderFloat3("Point Light Two Color", &pointTwoColor.x, 0.0f, 2.0f);

	m_scene->SetPointLightVariables(1, pointTwoPosition, pointTwoColor);

	ImGui::End();

#pragma endregion

#pragma region ImGui Objects

	ImGui::Begin("Objects");

	if (ImGui::CollapsingHeader("Bunny"))
	{
		// vec3 for each position, rotation and scale
		static glm::vec3 bunny_Position;
		static glm::quat bunny_RotationQ;
		static glm::vec3 bunny_Scale;
		
		// things we don't use...
		glm::vec3 skew; glm::vec4 perspective;
		
		// decomposing the current transform for the bunny
		glm::decompose(m_bunnyTransform, bunny_Scale, bunny_RotationQ, bunny_Position, skew, perspective);

		// convert quaternion to euler for rotation
		static glm::vec3 bunny_RotationE = glm::eulerAngles(bunny_RotationQ) * 3.14159f / 180.f;

		// ImGui
		ImGui::DragFloat3("Bunny Position", &bunny_Position.x, 0, 1);
		ImGui::DragFloat3("Bunny Rotation", &bunny_RotationE.x, 0, 1);
		ImGui::DragFloat3("Bunny Scale", &bunny_Scale.x, 0, 1);

		m_bunnyTransform = m_scene->SetObjectTransform(2, bunny_Position, bunny_RotationE * 8, bunny_Scale);
	}

	if (ImGui::CollapsingHeader("Soulspear"))
	{
		// vec3 for each position, rotation and scale
		static glm::vec3 soulspear_Position;
		static glm::quat soulspear_RotationQ;
		static glm::vec3 soulspear_Scale;

		// things we don't use...
		glm::vec3 skew; glm::vec4 perspective;

		// decomposing the current transform for the soulspear
		glm::decompose(m_soulspearTransform, soulspear_Scale, soulspear_RotationQ, soulspear_Position, skew, perspective);

		// convert quaternion to euler for rotation
		static glm::vec3 soulspear_RotationE = glm::eulerAngles(soulspear_RotationQ) * 3.14159f / 180.f;

		// ImGui
		ImGui::DragFloat3("Soulspear Position", &soulspear_Position.x, 0, 1);
		ImGui::DragFloat3("Soulspear Rotation", &soulspear_RotationE.x, 0, 1);
		ImGui::DragFloat3("Soulspear Scale", &soulspear_Scale.x, 0, 1);

		m_soulspearTransform = m_scene->SetObjectTransform(0, soulspear_Position, soulspear_RotationE * 8, soulspear_Scale);
	}

	if (ImGui::CollapsingHeader("Grenade"))
	{
		// vec3 for each position, rotation and scale
		static glm::vec3 grenade_Position;
		static glm::quat grenade_RotationQ;
		static glm::vec3 grenade_Scale;

		// things we don't use...
		glm::vec3 skew; glm::vec4 perspective;

		// decomposing the current transform for the grenade
		glm::decompose(m_grenadeTransform, grenade_Scale, grenade_RotationQ, grenade_Position, skew, perspective);

		// convert quaternion to euler for rotation
		static glm::vec3 grenade_RotationE = glm::eulerAngles(grenade_RotationQ) * 3.14159f / 180.f;

		// ImGui
		ImGui::DragFloat3("Grenade Position", &grenade_Position.x, 0, 1);
		ImGui::DragFloat3("Grenade Rotation", &grenade_RotationE.x, 0, 1);
		ImGui::DragFloat3("Grenade Scale", &grenade_Scale.x, 0, 1);

		m_grenadeTransform = m_scene->SetObjectTransform(1, grenade_Position, grenade_RotationE * 8, grenade_Scale);
	}

	ImGui::End();

#pragma endregion

#pragma region Debug

	// debug logic 
	if (m_debug)
	{
		// for each point light 
		for (auto light : m_scene->GetPointLights())
		{
			glm::mat4 pointOneSphere = {
			1,		0,     0,     0,
			0,		1,     0,     0,
			0,		0,	   1,     0,
			light.m_direction.x, light.m_direction.y, light.m_direction.z, 1
			};

			Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 10, 10, glm::vec4(light.m_color.x / 180, light.m_color.y / 180, light.m_color.z / 180, .4f), &pointOneSphere);
		}
	}

#pragma endregion

}
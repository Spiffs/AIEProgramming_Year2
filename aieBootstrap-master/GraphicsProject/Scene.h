#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>

const static int MAX_LIGHTS = 4;

class Camera;
class Instance;

struct Light
{
	Light() 
	{
		m_direction = glm::vec3(1);
		m_color = glm::vec3(1);
	}
	Light(glm::vec3 a_pos, glm::vec3 a_color, float a_intensity)
	{
		m_direction = a_pos;
		m_color = a_color * a_intensity;
	}
	glm::vec3 m_direction;
	glm::vec3 m_color;
};

class Scene
{
public:
	Scene(Camera* a_camera, glm::vec2 a_windowSize, Light& a_light, glm::vec3 a_ambientLight);
	~Scene();

	void AddInstance(Instance* a_instance);

	void Draw();

	Camera* GetCamera() { return m_camera; }
	void SetCamera(Camera* a_camera) { m_camera = a_camera; }

	glm::vec2 GetWindowSize() { return m_windowSize; }
	void SetWindowSize(glm::vec2 a_windowSize) { m_windowSize = a_windowSize; }

	Light GetLight() { return m_light; }
	void SetLight(Light a_light) { m_light = a_light; }
	void SetLightDirection(glm::vec3 a_direction) { m_light.m_direction = a_direction; }
	void SetLightColor(glm::vec3 a_color) { m_light.m_color = a_color; }

	glm::vec3 GetAmbientLight() { return m_ambientLight; }
	void SetAmbientLight(glm::vec3 a_ambientLight) { m_ambientLight = a_ambientLight; }

	int GetNumLights() { return (int)m_pointLights.size(); }
	glm::vec3* GetPointLightPositions() { return &m_pointLightPositions[0]; }
	glm::vec3* GetPointLightColor() { return &m_pointLightColors[0]; }
	void SetPointLightVariables(int lightNum, glm::vec3 a_pos, glm::vec3 a_color) { m_pointLights[lightNum].m_direction = a_pos; m_pointLights[lightNum].m_color = a_color * 50.0f; }

	std::vector<Light>& GetPointLights() { return m_pointLights; }

protected:
	Camera* m_camera;
	glm::vec2 m_windowSize;
	Light m_light;
	Light m_sunLight;
	std::vector<Light> m_pointLights;
	glm::vec3 m_ambientLight;
	std::list<Instance*> m_instances;

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColors[MAX_LIGHTS];
};


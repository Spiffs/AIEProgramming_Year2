#pragma once
#include <glm/glm.hpp>
#include <vector>

struct CameraPosition
{
	float m_theta = 0;	// In degrees
	float m_phi = 0;	// In degrees
	glm::vec3 m_position = glm::vec3(0);
};

class Camera
{
public:
	Camera();
	~Camera() {};

	void Update(float a_deltaTime);
	glm::vec3 GetPosition() { return m_Cameras.at(m_cameraSelected).m_position; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float a_width, float a_height);

private:
	std::vector<CameraPosition> m_Cameras;

	int m_cameraSelected = 0;
	float m_lastMouseX, m_lastMouseY;
};


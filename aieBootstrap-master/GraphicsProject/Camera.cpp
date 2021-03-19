#include "Camera.h"
#include <glm/ext.hpp>
#include <Input.h>

Camera::Camera()
{
	// main camera
	CameraPosition FlybyCamera;
	FlybyCamera.m_position = glm::vec3(-10, 2, 0);
	m_Cameras.push_back(FlybyCamera);

	CameraPosition CameraView1;
	CameraView1.m_position = glm::vec3(5, 2, 0);
	CameraView1.m_theta = 180;
	CameraView1.m_phi = -10;
	m_Cameras.push_back(CameraView1);
	
	CameraPosition CameraView2;
	CameraView2.m_position = glm::vec3(0, 2, 5);
	CameraView2.m_theta = -90;
	CameraView2.m_phi = -10;
	m_Cameras.push_back(CameraView2);

	CameraPosition CameraView3;
	CameraView3.m_position = glm::vec3(0, 2, -5);
	CameraView3.m_theta = 90;
	CameraView3.m_phi = -10;
	m_Cameras.push_back(CameraView3);
}

void Camera::Update(float a_deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_Cameras[0].m_theta);
	float phiR = glm::radians(m_Cameras[0].m_phi);

	// Calculate the forwards and right axes and the up axis for the camera
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));
	glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
	glm::vec3 up(0, 1, 0);

	float speed = 2;
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
		speed *= 2;

#pragma region InputSettings

	if (m_cameraSelected == 0)
	{
		if (input->isKeyDown(aie::INPUT_KEY_X))
			m_Cameras[0].m_position += up * a_deltaTime * speed;
		if (input->isKeyDown(aie::INPUT_KEY_Z))
			m_Cameras[0].m_position -= up * a_deltaTime * speed;
		if (input->isKeyDown(aie::INPUT_KEY_A))
			m_Cameras[0].m_position -= right * a_deltaTime * speed;
		if (input->isKeyDown(aie::INPUT_KEY_D))
			m_Cameras[0].m_position += right * a_deltaTime * speed;
		if (input->isKeyDown(aie::INPUT_KEY_W))
			m_Cameras[0].m_position += forward * a_deltaTime * speed;
		if (input->isKeyDown(aie::INPUT_KEY_S))
			m_Cameras[0].m_position -= forward * a_deltaTime * speed;
	}


#pragma endregion

	// Get the current position of the mouse coordinates
	float mX = input->getMouseX();
	float mY = input->getMouseY();
	const float turnSpeed = glm::radians(180.0f);

	// If the right button is down. increment the theta and phi
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_Cameras[0].m_theta += turnSpeed * (mX - m_lastMouseX) * a_deltaTime;
		m_Cameras[0].m_phi += turnSpeed * (mY - m_lastMouseY) * a_deltaTime;
	}

	// If the left button is down. switch the camera
	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		m_cameraSelected++;
		if (m_cameraSelected >= 4)
			m_cameraSelected = 0;
	}

	// Now store the frames last values for the next
	m_lastMouseX = mX;
	m_lastMouseY = mY;
}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_Cameras[m_cameraSelected].m_theta);
	float phiR = glm::radians(m_Cameras[m_cameraSelected].m_phi);
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));

	return glm::lookAt(m_Cameras[m_cameraSelected].m_position, m_Cameras[m_cameraSelected].m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float a_width, float a_height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, a_width / a_height, 0.1f, 1000.0f);
}
#include "Camera.h"
#include <glm/ext.hpp>
#include <Input.h>
#include <iostream>

Camera::Camera()
{
	// main camera
	CameraPosition FlybyCamera;
	FlybyCamera.m_position = glm::vec3(-10, 5, 0);
	m_Cameras.push_back(FlybyCamera);

	CameraPosition CameraView2;
	CameraView2.m_position = glm::vec3(20, 5, 20);
	CameraView2.m_theta = 225;
	CameraView2.m_phi = -15;
	m_Cameras.push_back(CameraView2);

	CameraPosition CameraView3;										//BROKEN
	CameraView3.m_position = glm::vec3(20, 5, -20);
	CameraView3.m_theta = 135;
	CameraView3.m_phi = -15;
	m_Cameras.push_back(CameraView3);

	CameraPosition CameraView4;
	CameraView4.m_position = glm::vec3(-20, 5, -20);
	CameraView4.m_theta = 45;
	CameraView4.m_phi = -15;
	m_Cameras.push_back(CameraView4);

	CameraPosition CameraView5;										//BROKEN
	CameraView5.m_position = glm::vec3(-20, 5, 20);
	CameraView5.m_theta = 315;
	CameraView5.m_phi = -15;
	m_Cameras.push_back(CameraView5);
}

void Camera::Update(float a_deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (m_cameraSelected == 0)
	{
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
		const float speedAddition = 4;
		const float turnSpeed = glm::radians(180.0f) * speedAddition;

		// If the right button is down. increment the theta and phi
		if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
		{
			m_Cameras[0].m_theta += turnSpeed * (mX - m_lastMouseX) * a_deltaTime;
			m_Cameras[0].m_phi += turnSpeed * (mY - m_lastMouseY) * a_deltaTime;
		}

		// Now store the frames last values for the next
		m_lastMouseX = mX;
		m_lastMouseY = mY;
	}

	// If the left button is down. switch the camera
	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		m_cameraSelected++;
		if (m_cameraSelected >= m_Cameras.size())
			m_cameraSelected = 0;
	}
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
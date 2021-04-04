#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsScene.h"
#include "Billiards.h"

class PhysicsProjectApp : public aie::Application {
public:

	PhysicsProjectApp();
	virtual ~PhysicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);
	glm::vec2 WorldToScreen(glm::vec2 a_worldPos);

	aie::Renderer2D* GetRenderer() { return m_2dRenderer; }
	const float GetExtents() { return m_extents; }
	const float GetAspectRatio() { return m_aspectRatio; }

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_escapeFont;
	aie::Font*			m_fpsFont;

	//PhysicsScene* m_physicsScene;
	Billiards* m_billiards;

	const float m_aspectRatio = 16.f / 9.f;
	const float m_extents = 100;

};
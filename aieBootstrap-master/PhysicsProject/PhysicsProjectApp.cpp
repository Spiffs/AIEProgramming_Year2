#include "PhysicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include "Sphere.h"
#include "Plane.h"
#include <Gizmos.h>


PhysicsProjectApp::PhysicsProjectApp() {

}

PhysicsProjectApp::~PhysicsProjectApp() {

}

bool PhysicsProjectApp::startup() {

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, -10));

	m_physicsScene->SetTimeStep(0.01);

	Sphere* ball1;
	ball1 = new Sphere(glm::vec2(-40, 40), glm::vec2(0, 0), 3.f, 3, glm::vec4(1, 0, 0, 1));
	
	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(40, 40), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	
	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);

	ball1->ApplyForce(glm::vec2(100, 0));
	ball2->ApplyForce(glm::vec2(-20, 0));

	Plane* plane = new Plane();
	m_physicsScene->AddActor(plane);

	return true;
}

void PhysicsProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();


	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>
		(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	// draw your stuff here!

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}
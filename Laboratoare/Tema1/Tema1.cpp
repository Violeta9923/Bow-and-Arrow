#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "TransformD.h"
#include "Object.h"
#include <Math.h>

using namespace std;

struct balloonStruct {
	float balloon_translateX;
	float balloon_translateY;
	float balloon_scaleX;
	float balloon_scaleY; 
	int type;
	bool col;
} balloon[6];

struct shurikenStruct {
	float shuriken_translateX;
	float shuriken_translateY;
	float shuriken_scaleX;
	bool col;
}shuriken[5];


Tema1:: Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	// initializare variabile folosite

	radius = 80.0f;
	score = 3;
	lives = 3;
	score_count = 1;
	arrow_size = 20;
	shuriken_size = 40;
	arrow_height = 60;
	balloon_radius = 40;
	balloon_scale_X = 1;
	balloon_scale_Y = 1.5;
	delta = 5;
	arch_translateX = 50;
	arch_translateY = 50;
	balloon_translateX = 250;
	balloon_translateY = -2 * balloon_radius - 10*delta;
	multiply_delta = 200;
	shuriken_scaleX = 1;
	shuriken_translateX = resolution.x;
	shuriken_translateY = 0;
	angularStep = 0;
	arch_angularStep = 0;
	arrow_angularStep = 0;
	square_size = 15;
	square_power = 1;
	mouse_press = false;
	arch_rotate = false;
	arrow_rotate = false;
	arrow_speed = 1;
	arrow_direction = 0;
	arrow_throw = false;
	arrow_translateX = 0;
	arrow_translateY = 0;
	
	distance1 = 0;
	distance2 = 0;
	resolution_x = 0;
	resolution_y = 0;

	balloon[0].type = 0;
	balloon[1].type = 0;
	balloon[2].type = 1;
	balloon[3].type = 0;
	balloon[4].type = 1;
	balloon[5].type = 1;

	for (int i = 0; i < 6; i++) {
		balloon_translateX += 40;
		if (balloon[i].type == 0) {
			balloon_translateX += 20;
			balloon_translateY += 30;
		}
		else {
			balloon_translateY -= 40;
		}
		balloon[i].balloon_translateX = balloon_translateX + i * 100;
		balloon[i].balloon_translateY = balloon_translateY + 30  * i;
		balloon[i].balloon_scaleX = balloon_scale_X;
		balloon[i].balloon_scaleY = balloon_scale_Y;
	}
	
	for (int i = 0; i < 5; i++) {
		shuriken[i].shuriken_translateX = shuriken_translateX - 20 * i;
		shuriken[i].shuriken_translateY = shuriken_translateY;
		shuriken[i].shuriken_scaleX = shuriken_scaleX;
		shuriken[i].col = false;
	}

	//initializare arc
	Mesh* arch = Object::CreatArch("arch", corner, radius, glm::vec3(1, 0, 0));
	AddMeshToList(arch);

	// initializare sageata
	Mesh* arrow = Object::CreatArrow("arrow", corner, arrow_size, arrow_height, glm::vec3(1, 0, 0));
	AddMeshToList(arrow);

	//initializare balloon

	Mesh* balloonY = Object::CreatBalloon("balloonY", corner, balloon_radius, delta, glm::vec3(1, 1, 0));
	AddMeshToList(balloonY);
	Mesh* balloonR = Object::CreatBalloon("balloonR", corner, balloon_radius, delta, glm::vec3(1, 0, 0));
	AddMeshToList(balloonR);
	Mesh* balloon_line = Object::CreatLine("balloon_line", corner, balloon_radius, delta, glm::vec3(1, 1, 0));
	AddMeshToList(balloon_line);
	//initializare shuriken
	Mesh* shuriken = Object::CreatShuriken("shuriken", corner, shuriken_size, delta, glm::vec3(1, 1, 0));
	AddMeshToList(shuriken);

	// initializare nivel putere
	Mesh* square = Object::CreateSquare("square", corner, square_size, glm::vec3(1, 1, 0));
	AddMeshToList(square);

}
void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	resolution_x = resolution.x;
	resolution_y = resolution.y;
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);


}

void Tema1::Update(float deltaTimeSeconds)
{

	// desenare arc
	modelMatrix = glm::mat3(1);
	modelMatrix *= TransformD::Translate(arch_translateX, arch_translateY);
	modelMatrix *= TransformD::Translate(radius / 2.f, radius / 2.f);
	modelMatrix *= TransformD::Rotate(-1.5708);
	modelMatrix *= TransformD::Translate(-radius / 2.f, -radius / 2.f);

	if (arch_rotate && arrow_throw == false) {
		if (arch_angularStep > 3 * 1.5708 / 4)
			arch_angularStep = 3 * 1.5708 / 4;
		if (arch_angularStep < -3 * 1.5708 / 4)
			arch_angularStep = -3 * 1.5708 / 4;
		modelMatrix *= TransformD::Rotate(-arch_angularStep);
	}
	for (int i = 0; i < 5; i++) {
		// coliziune shuriken arc
		float dx3 = shuriken[i].shuriken_translateX + shuriken_size + delta / 2 - arch_translateX;
		float dy3 = shuriken[i].shuriken_translateY + shuriken_size + delta / 2 - arch_translateY - radius;
		float distance = sqrt(dx3 * dx3 + dy3 * dy3);
		if (distance <= 2 * shuriken_size + delta / 2 + radius / 2) {
			lives--;
			arch_translateX = 0;
			arch_translateY = 0;
			modelMatrix *= TransformD::Translate(0, 0);
			shuriken[i].col = true;
			arrow_throw = false;
			
		}
		
	}
	
	RenderMesh2D(meshes["arch"], shaders["VertexColor"], modelMatrix);
	// desenare sageata
	modelMatrix = glm::mat3(1);
	for (int i = 0; i < 6; i++) {
		// coliziune sageata balon
		float dx = balloon[i].balloon_translateX - arrow_translateX - 5 * arrow_size;
		float dy = balloon[i].balloon_translateY - arrow_translateY - 0.5 * balloon_radius;
		distance1 = sqrt(dx * dx + dy * dy);
		float dx1 = balloon[i].balloon_translateX - arrow_translateX - 5 * arrow_size;
		float dy1 = balloon[i].balloon_translateY - arrow_translateY - 2 * balloon_radius;
		distance2 = sqrt(dx1 * dx1 + dy1 * dy1);
		if (distance1 <= balloon_radius || distance2 <= balloon_radius) {
			arrow_translateX = arch_translateX;
			arrow_translateY = -arrow_height / 2 + radius + arch_translateY;
			arrow_speed = 1;
			arrow_throw = false;
			modelMatrix *= TransformD::Translate(0, 0);
			balloon[i].col = true;
			if (balloon[i].type == 0 && score > 0)
				score -= score_count;
			else
				score += score_count;
		}
		if (i < 5) {
			// coliziune sageata shuriken
			float dx = shuriken[i].shuriken_translateX + shuriken_size + delta / 2 - arrow_translateX - 5 * arrow_size;
			float dy = shuriken[i].shuriken_translateY - arrow_translateY;
			distance1 = sqrt(dx * dx + dy * dy);
			if (distance1 <= 2 * shuriken_size + delta) {
				arrow_translateX = arch_translateX;
				arrow_translateY = -arrow_height / 2 + radius + arch_translateY;
				shuriken[i].col = true;
				arrow_speed = 1;
				arrow_throw = false;
			}
		}
	}
	if (arrow_throw && balloon[0].col == false && balloon[1].col == false && balloon[2].col == false && balloon[3].col == false && balloon[4].col == false &&
		shuriken[0].col == false && shuriken[1].col == false && shuriken[2].col == false && shuriken[3].col == false && shuriken[4].col == false) {
		// aruncare sageata fara tinte doborate
		arrow_rotate = false;
		arrow_translateX += arrow_speed;
		arrow_translateY += tan(-arrow_direction) * arrow_speed;
		modelMatrix *= TransformD::Translate(arrow_translateX, arrow_translateY);
		modelMatrix *= TransformD::Translate(0, arrow_height / 2);
		modelMatrix *= TransformD::Rotate(-arrow_direction);
		modelMatrix *= TransformD::Translate(0, -arrow_height / 2);
		if (arrow_translateX > resolution_x || arch_translateY > resolution_y) {
			arrow_throw = false;
			arrow_speed = 1;
			arrow_translateX = 50 + arch_translateX;
			arrow_translateY = 50 - arrow_height / 2 + radius + arch_translateY;
		}
	}
	else {
		// sageata inainte de aruncare
		arrow_translateX = arch_translateX;
		arrow_translateY = -arrow_height / 2 + radius + arch_translateY;
		modelMatrix *= TransformD::Translate(arrow_translateX, arrow_translateY);
		if (arrow_rotate) {
			if (arrow_angularStep > 3 * 1.5708 / 4)
				arrow_angularStep = 3 * 1.5708 / 4;
			if (arrow_angularStep < -3 * 1.5708 / 4)
				arrow_angularStep = -3 * 1.5708 / 4;
			modelMatrix *= TransformD::Translate(0, arrow_height / 2);
			modelMatrix *= TransformD::Rotate(-arrow_angularStep);
			modelMatrix *= TransformD::Translate(0, -arrow_height / 2);
		}

	}
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	// desenare balon
	modelMatrix = glm::mat3(1);
	int numberTriangle = 30;
	GLfloat doublePi = 2.0f * 3.141592;
	float length = 10 * delta;
	for (int i = 0; i < 6; i++) {
		modelMatrix = glm::mat3(1);
		// tintire balon
		if (balloon[i].col == true) {
			balloon_translateX = 350;
			if (balloon[i].balloon_scaleX > 0) {
				// animatie balon spart
				balloon[i].balloon_scaleX -= deltaTimeSeconds;
				balloon[i].balloon_scaleY -= deltaTimeSeconds * 2;
			}
			else {
				balloon[i].balloon_scaleX = 1;
				balloon[i].balloon_scaleY = 1.5;
				balloon[i].balloon_translateY = 0 - balloon_radius / 2;
				balloon_translateX += 50;
				if (balloon[i].type == 0) {
					balloon_translateX += 20;
					balloon_translateY = 0;
				}
				else {
					balloon_translateY -= 50;
				}
				balloon[i].balloon_translateX = balloon_translateX + i * 100;
				balloon[i].col = false;
			}
		}
		// animatie balon pe Oy
		if (balloon[i].balloon_translateY + deltaTimeSeconds * multiply_delta / 5 < resolution_y + 2 * balloon_radius + length)
			balloon[i].balloon_translateY += deltaTimeSeconds * multiply_delta / 5;
		else
			balloon[i].balloon_translateY = 0 - 2 * balloon_radius;

		modelMatrix *= TransformD::Translate(balloon[i].balloon_translateX, balloon[i].balloon_translateY);
		modelMatrix *= TransformD::Scale(balloon[i].balloon_scaleX, balloon[i].balloon_scaleY);
		if (balloon[i].type == 0) {
			RenderMesh2D(meshes["balloonY"], shaders["VertexColor"], modelMatrix);
		}
		else {
			RenderMesh2D(meshes["balloonR"], shaders["VertexColor"], modelMatrix);
		}
		RenderMesh2D(meshes["balloon_line"], shaders["VertexColor"], modelMatrix);
	}

	//desenez shuriken
	for (int i = 0; i < 5; i++) {
		modelMatrix = glm::mat3(1);
		// animatie shuriken pe Ox
		if (shuriken[i].shuriken_translateX - deltaTimeSeconds * multiply_delta / 2 > 0 - shuriken_size) {
			if (shuriken[i].col == false)
				shuriken[i].shuriken_translateX -= deltaTimeSeconds * multiply_delta / 2 * (i + 1);
		}
		else {
			shuriken[i].shuriken_translateX = resolution_x - shuriken_size - 30 * i;
		}
		// pozitionare shuriken pe pozitii diferite pe Oy
		if (shuriken[0].col == false && shuriken[1].col == false && shuriken[2].col == false && shuriken[3].col == false && shuriken[4].col == false) {
			shuriken_translateY = 150;
			if (balloon[i].type == 0) {
				shuriken[i].shuriken_translateY = shuriken_translateY * i + 20;
			}
			else {
				shuriken[i].shuriken_translateY = shuriken_translateY * i;
			}
		}
		else {
			// animatie shuriken lovit de sageata
			if (shuriken[i].col == true) {
				if (shuriken[i].shuriken_scaleX > 0) {
					shuriken[i].shuriken_scaleX -= deltaTimeSeconds;
				}
				else {
					shuriken[i].col = false;
					shuriken[i].shuriken_scaleX = 1;
					shuriken[i].shuriken_translateX = resolution_x - shuriken_size;
				}
			}
		}
		// animatie shuriken(rotirea)
		angularStep += deltaTimeSeconds * 3;
		modelMatrix *= TransformD::Translate(shuriken[i].shuriken_translateX, shuriken[i].shuriken_translateY);
		modelMatrix *= TransformD::Translate(shuriken_size + 5 / 2.f, shuriken_size + 5 / 2.f);
		modelMatrix *= TransformD::Scale(shuriken[i].shuriken_scaleX, 1);
		modelMatrix *= TransformD::Translate(-shuriken_size - 5 / 2.f, -shuriken_size - 5 / 2.f);
		modelMatrix *= TransformD::Translate(shuriken_size + 5 / 2.f, shuriken_size + 5 / 2.f);
		modelMatrix *= TransformD::Rotate(angularStep);
		modelMatrix *= TransformD::Translate(-shuriken_size - 5 / 2.f, -shuriken_size - 5 / 2.f);
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
	}
	// desenare nivel putere
	modelMatrix = glm::mat3(1);
	if (mouse_press) {
		if (square_power <= resolution_x / 20) {
			square_power += deltaTimeSeconds * multiply_delta;
			if (!arrow_throw)
				// crestrea vitezei sagetii
				arrow_speed += deltaTimeSeconds * multiply_delta / 2;
		}
	}
	else {
		square_power = 0;
	}
	modelMatrix *= TransformD::Translate(square_size / 2.f, square_size / 2.f);
	modelMatrix *= TransformD::Scale(square_power, 1);
	modelMatrix *= TransformD::Translate(-square_size / 2.f, -square_size / 2.f);
	modelMatrix *= TransformD::Translate(5, 5);
	RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

	// desenare scor
	modelMatrix = glm::mat3(1);
	modelMatrix *= TransformD::Scale(2, score);
	RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

	// iesire joc
	if (lives == 0) {
		exit(0);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_W)) {
		if (2 * radius + arch_translateY + (deltaTime * multiply_delta) < resolution_y - 8 * delta)
			arch_translateY += deltaTime * multiply_delta;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		if (arch_translateY - (deltaTime * multiply_delta) > 0)
			arch_translateY -= deltaTime * multiply_delta;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event 
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (arch_rotate == true && arrow_throw == false) {
			arch_angularStep += atan(deltaY / (arrow_size * 5));
			arrow_angularStep += atan(deltaY / (arrow_size * 5));
		}
	}


}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT))
	{
		mouse_press = true;
		arch_rotate = true;
		arrow_rotate = true;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT))
	{
		mouse_press = false;
		arch_rotate = false;
		arrow_rotate = false;
		arrow_direction = arrow_angularStep;
		arrow_throw = true;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

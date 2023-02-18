#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 modelMatrixB;
	float score;
	float score_count;
	int lives;
	float resolution_x;
	float resolution_y;
	int delta;
	int multiply_delta;
	

	float radius;
	float arch_translateX, arch_translateY;
	float arch_angularStep;
	bool arch_rotate;

	float balloon_radius;
	float balloon_scale_X;
	float balloon_scale_Y;
	float balloon_translateX, balloon_translateY;


	float arrow_size;
	float arrow_height;
	float arrow_translateX, arrow_translateY;
	float arrow_angularStep;
	bool arrow_rotate;
	float arrow_direction;
	bool arrow_throw;
	float arrow_speed;


	float shuriken_size;
	float shuriken_scaleX;
	float angularStep;
	float shuriken_translateX, shuriken_translateY;
	
	
	
	int square_size;
	float square_power;

	bool mouse_press;
	float distance1;
	float distance2;
};

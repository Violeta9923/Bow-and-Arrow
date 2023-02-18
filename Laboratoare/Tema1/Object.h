#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object
{

	Mesh* CreatArch(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color);
	Mesh* CreatArrow(std::string name, glm::vec3 leftBottomCorner, float arrow_size, float arrow_height, glm::vec3 color);
	Mesh* CreatBalloon(std::string name, glm::vec3 leftBottomCorner, float radius, float delta, glm::vec3 color);
	Mesh* CreatLine(std::string name, glm::vec3 leftBottomCorner, float radius, float delta, glm::vec3 color);
	Mesh* CreatShuriken(std::string name, glm::vec3 leftBottomCorner, float size, int delta, glm::vec3 color);
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);

}
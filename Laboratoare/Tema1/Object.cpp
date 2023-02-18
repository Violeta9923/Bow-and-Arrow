#include "Object.h"

#include <Core/Engine.h>


Mesh* Object::CreatArch(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	int numberTriangle = 20;

	GLfloat doublePi = 2.0f * 3.141592;

	std::vector<VertexFormat> vertices{};
	std::vector<unsigned short> indices{};

	vertices.push_back(VertexFormat(corner, color));
	indices.push_back(0);
	for (int i = 0; i <= numberTriangle / 2; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3((radius * cos(i * doublePi / numberTriangle)),
			(radius * sin(i * doublePi / numberTriangle)), 0), color));
		indices.push_back(i + 1);

	}

	Mesh* semicerc = new Mesh(name);
	semicerc->SetDrawMode(GL_LINE_LOOP);
	semicerc->InitFromData(vertices, indices);

	return semicerc;

}

Mesh* Object::CreatArrow(std::string name, glm::vec3 leftBottomCorner, float arrow_size, float arrow_height, glm::vec3 color) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices{
		VertexFormat(corner + glm::vec3(0, arrow_height / 2,  0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(arrow_size, arrow_height / 2,  0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(2 * arrow_size, arrow_height / 2,  0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(3 * arrow_size, arrow_height / 2,  0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(4 * arrow_size, arrow_height / 2,  0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(4 * arrow_size, arrow_height, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(5 * arrow_size, arrow_height / 2, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(4 * arrow_size, 0, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(4 * arrow_size, arrow_height / 2, 0), glm::vec3(0, 1, 1)),

	};

	std::vector<unsigned short> indices{
		0, 1, 2, 3, 4, 5, 6, 7, 8,
	};


	Mesh* arrow = new Mesh(name);
	arrow->SetDrawMode(GL_LINE_STRIP);
	arrow->InitFromData(vertices, indices);
	glLineWidth(5);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return arrow;


}

Mesh* Object::CreatBalloon(std::string name, glm::vec3 leftBottomCorner, float radius, float delta, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	int numberTriangle = 30;

	GLfloat doublePi = 2.0f * 3.141592;

	std::vector<VertexFormat> vertices{};
	std::vector<unsigned short> indices{};

	vertices.push_back(VertexFormat(corner, color));
	indices.push_back(0);
	for (int i = 0; i <= numberTriangle; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3((radius * cos(i * doublePi / numberTriangle)),
			(radius * sin(i * doublePi / numberTriangle)), 0), color));
		indices.push_back(i + 1);

	}

	Mesh* balloon = new Mesh(name);
	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	balloon->InitFromData(vertices, indices);

	return balloon;

}

Mesh* Object::CreatLine(std::string name, glm::vec3 leftBottomCorner, float radius, float delta, glm::vec3 color) {
	glm::vec3 corner = leftBottomCorner;
	int numberTriangle = 30;
	GLfloat doublePi = 2.0f * 3.141592;

	std::vector<VertexFormat> vertices{
		VertexFormat(corner + glm::vec3(0, -radius, 0)),
		VertexFormat(corner + glm::vec3(-delta, -radius - delta, 0)),
		VertexFormat(corner + glm::vec3(delta, -radius -  delta, 0)),
		VertexFormat(corner + glm::vec3(0, -radius, 0)),
		VertexFormat(corner + glm::vec3(0, -radius - delta, 0)),
		
		VertexFormat(corner + glm::vec3(- 4 * delta, -radius - 2 * delta, 0)),
		VertexFormat(corner + glm::vec3(3 * delta, -radius - 4 * delta, 0)),
		VertexFormat(corner + glm::vec3(-3 * delta, -radius - 6 * delta, 0)),
		VertexFormat(corner + glm::vec3(4 * delta, -radius - 8 * delta, 0)),
		VertexFormat(corner + glm::vec3(0, -radius - 10 * delta, 0)),
	};
	
	std::vector<unsigned short> indices{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	};

	Mesh* line = new Mesh(name);
	line->SetDrawMode(GL_LINE_STRIP);
	line->InitFromData(vertices, indices);

	return line;
}

Mesh* Object::CreatShuriken(std::string name, glm::vec3 leftBottomCorner, float shuriken_size, int delta, glm::vec3 color) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(2 * delta, 0, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_size, shuriken_size, 0), color),
		VertexFormat(corner + glm::vec3(0, shuriken_size - delta, 0), color),

		VertexFormat(corner + glm::vec3(shuriken_size + delta, delta, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_size, shuriken_size, 0), color),
		VertexFormat(corner + glm::vec3(2 * shuriken_size + delta, 2 * delta, 0), color),

		VertexFormat(corner + glm::vec3(2 * shuriken_size, shuriken_size + delta, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_size, shuriken_size, 0), color),
		VertexFormat(corner + glm::vec3(2 * shuriken_size - delta, 2 * shuriken_size + delta, 0), color),

		VertexFormat(corner + glm::vec3(shuriken_size - delta, 2 * shuriken_size - delta, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_size, shuriken_size, 0), color),
		VertexFormat(corner + glm::vec3(0, 2 * shuriken_size - delta, 0), color),
	};


	std::vector<unsigned short> indices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
	};

	Mesh* shuriken = new Mesh(name);
	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);

	return shuriken;
}

Mesh* Object::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };

	square->InitFromData(vertices, indices);
	return square;
}


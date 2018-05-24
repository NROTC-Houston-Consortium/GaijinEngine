#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include<iostream>
#include<windows.h>



int main()
{
	using namespace gaijin;
	using namespace graphics;
	using namespace maths;

	Window window("Hello World", 960, 540);





/*std::string test = read_file("src/shaders/basic.vert");
	std::cout << test << std::endl;

	test = read_file("src/shaders/basic.frag");
	std::cout << test << std::endl;
	system("pause");
	*/

	int test = 0;
	int test2 = 0;

	double x, y;


	std::cout <<"Window width and height: " << window.w_getWidth() << " , " << window.w_getHeight() << std::endl;
	std::cout << std::endl;

	float positions[] = {
		0,0,0,
		8,0,0,
		0,3,0,
		0,3,0,
		8,3,0,
		8,0,0
	};

	GLuint buffer;
	glGenVertexArrays(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	Shader shader("src/shaders/shader.txt");
	shader.s_setUniformMat4("pr_matrix", ortho);
	shader.s_setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
//	shader.s_setUniformMat4("ml_matrix", mat4::rotation(45.0f,vec3(0,0,1)));
	shader.s_setUniform4f("colour", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	shader.s_setUniform2f("light_pos", vec2(8.0f, 4.5f));


	while (!window.w_closed())
	{
		window.clear();

		//glClear(GL_COLOR_BUFFER_BIT);

		
		//glDrawArrays(GL_TRIANGLES, 0,3);
		if (window.w_isKeyPressed(GLFW_KEY_A))
		{
			shader.s_setUniform4f("colour", vec4(0.0f, 0.0f, 1.0f, 1.0f));
			std::cout << "Color changed to blue!" << std::endl;
		}
		
		if (window.w_isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			shader.s_setUniform4f("colour", vec4(1.0f, 0.0f, 0.0f, 1.0f));
			std::cout << "Color changed to red!" << std::endl;

		}

		

		//std::cout << (a != b) << std::endl;
		//Sleep(500);

		/*window.w_getMousePosition(x, y);

		std::cout << x << ", " << y << std::endl;*/

		glDrawArrays(GL_TRIANGLES, 0, 6);
		/*glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);*/

		window.w_update();
	}


	//system("pause"); 
	return 0;
}
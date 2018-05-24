#pragma once


#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>


namespace gaijin 
{
	namespace graphics
	{

#define MAX_KEYS 1024
#define MAX_MOUSEKEYS 32

		class Window
		{
			friend struct GLFWwindow;
		public:
			Window(const char* wName, int width, int height);
			~Window();

			void w_update();
			bool w_closed() const;
			void clear() const;
			int w_getWidth() const;
			int w_getHeight() const;


			bool w_isKeyPressed(unsigned int keycode) const;
			bool w_isMouseButtonPressed(unsigned int buttoncode) const;
			void w_getMousePosition(double &x, double &y) const;


		private:
			int w_pr_Width, w_pr_Height;
			const char *w_pr_WindowName;
			GLFWwindow *w_pr_Window;
			bool w_pr_Closed;

			//input
			bool w_i_pr_Keys[MAX_KEYS];
			bool w_i_pr_MouseButtonKeys[MAX_MOUSEKEYS];
			double w_i_pr_MouseX;
			double w_i_pr_MouseY; 


			bool w_pr_Init();

			friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
			friend static void cursor_poistion_callback(GLFWwindow* window, double xpos, double ypos);
			

		};
	}





}

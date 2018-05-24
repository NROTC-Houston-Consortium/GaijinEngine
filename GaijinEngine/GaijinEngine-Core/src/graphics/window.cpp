#include "window.h"
#include<iostream>

namespace gaijin
{
	namespace graphics
	{
		void window_Resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
		void cursor_poistion_callback(GLFWwindow* window, double xpos, double ypos);


		Window::Window(const char * wName, int width, int height)
		{
			w_pr_WindowName = wName;
			w_pr_Width = width;
			w_pr_Height = height;

			if (!w_pr_Init())
			{
				glfwTerminate();
			}


			for (int i = 0; i < MAX_KEYS; i++)
			{
				w_i_pr_Keys[i] = false;
			}

			for (int i = 0; i < MAX_MOUSEKEYS; i++)
			{
				w_i_pr_Keys[i] = false;
			}

		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::w_update()
		{
			glfwPollEvents();
			//glfwGetFramebufferSize(w_pr_Window, &w_pr_Width, &w_pr_Height);
			glfwSwapBuffers(w_pr_Window);
		}

		bool Window::w_closed() const
		{
			return glfwWindowShouldClose(w_pr_Window) == 1;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		}

		int Window::w_getWidth() const
		{
			return w_pr_Width;
		}

		int Window::w_getHeight() const
		{
			return w_pr_Height;
		}

		bool Window::w_isKeyPressed(unsigned int keycode) const
		{
			//TODO: Log this!!
			if (keycode >= MAX_KEYS)
				return false;
			
			return w_i_pr_Keys[keycode];
		}

		bool Window::w_isMouseButtonPressed(unsigned int buttoncode) const
		{
			//TODO: Log this!!
			if (buttoncode >= MAX_MOUSEKEYS)
				return false;

			return w_i_pr_MouseButtonKeys[buttoncode];
		}

		void Window::w_getMousePosition(double & x, double & y) const
		{
			x = w_i_pr_MouseX;
			y = w_i_pr_MouseY;

		}


		bool Window::w_pr_Init()
		{
			if (!glfwInit())
			{
				std::cout << "Error! Failed to initialize GLFW!" << std::endl;
				return false;
			}

			w_pr_Window = glfwCreateWindow(w_pr_Width, w_pr_Height,w_pr_WindowName, NULL, NULL);
			if (!w_pr_Window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(w_pr_Window);
			glfwSetWindowUserPointer(w_pr_Window, this);

			glfwSetWindowSizeCallback(w_pr_Window, window_Resize);
			glfwSetKeyCallback(w_pr_Window, key_callback);
			glfwSetMouseButtonCallback(w_pr_Window, mouse_button_callback);
			glfwSetCursorPosCallback(w_pr_Window, cursor_poistion_callback);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

			return true; 
		}


		void window_Resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}



		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window* win  = (Window*)glfwGetWindowUserPointer(window);
			
			win->w_i_pr_Keys[key] = action != GLFW_RELEASE;

		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window * win = (Window*)glfwGetWindowUserPointer(window);

			win->w_i_pr_MouseButtonKeys[button] = action != GLFW_RELEASE;
		}

		void cursor_poistion_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window * win = (Window*)glfwGetWindowUserPointer(window);

			win->w_i_pr_MouseX = xpos;
			win->w_i_pr_MouseY = ypos;
		}

	}
}



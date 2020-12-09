#include "window.h"

Window::Window(int width, int height, const char* name, int* version)
{

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version[0]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version[1]);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
}

Window::~Window()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();// for keys
}


int Window::Check_Env() {
	if (Window::window == NULL) {
		std::cout << "couldn't create openGL context" << '\n' << std::endl;
		glfwTerminate();
		return -1;
	}
	else {
		glfwMakeContextCurrent(window);
		return 1;
	}
}

void Window::Background_Color(const float* color)
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

int Window::Get_Key(int key)
{
	return(glfwGetKey(window, key));
}







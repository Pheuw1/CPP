#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
	Made to solve problem of app not closing itself

	gl get error running in loop
	would not stop because of VertexBuffer class needing to go out of scope to destruct
	destructor would raise error because of need to glfwterminate before end of scope
	widh would end the opengl context

*/
class Window {
public:


	GLFWwindow* window;


	Window(int width, int heigth,const char* name, int *version);

	~Window();

	void SwapBuffers();

	int Check_Env();

	void Background_Color(const float color[4]);

	int Get_Key(int key);

};
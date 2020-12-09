#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GL_Object_abstractions/vertexbuffer.h"
#include "GL_Object_abstractions/vertexarray.h"


#include "My_Objects/Class.h"
#include "renderer.h"
#include "My_Objects/window.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static struct ShaderProgramSource ParseShader(const std::string& filepath)//takes file , converts it into a string
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);// look this up
    std::string line;// fill up with line of file
    std::stringstream ss[2];// two string containg vertex and shader resepctively
    ShaderType type = ShaderType::NONE;// smart way to assign an index of ss to type of shader

    while (getline(stream, line))//go through file. assign getline to line
    {
        if (line.find("#shader") != std::string::npos)//then set type
        {
            if (line.find("vertex") != std::string::npos)//type 0
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)//type 1
                type = ShaderType::FRAGMENT;
        }
        else if ((int)type != -1)//if type has not been found
        {
            ss[(int)type] << line << '\n';//if type has been found: append line to ss[type=0/1]
        }
    }

    return { ss[0].str(), ss[1].str() };// return vertex file and fragment file
}

static unsigned int CompileShader(unsigned int type, const std::string& source)//takes string returns buffer filled with shader
{
    unsigned int id = glCreateShader(type);//place to store shader 
    const char* src = source.c_str();// std::string that represents file in into char[]
    
    glShaderSource(id, 1, &src, nullptr);//look this up
    glCompileShader(id);//look this up

    
                        
    // Error handling
    int result;//place to store a flag that reports succes of compiling shader
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//assigns flag to result also look this up
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile status: " << result << std::endl;// print compile status
    if ( result == GL_FALSE )//print problem
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) _malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout 
            << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader"
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;//return buffer where shader is stored
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();//look this up
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);    //place where shader is stored
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);//place where shader is stored

    GLCall(glAttachShader(program, vs));//attache bind???? look this up
    GLCall(glAttachShader(program, fs));//attache bind???? look this up

    GLCall(glLinkProgram(program));


    //Error handling
    GLint program_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    GLCall(glValidateProgram(program));//look this up

    glDeleteShader(vs);//get rid of data in buffer and free
    glDeleteShader(fs);//get rid of data in buffer and free

    return program;//return buffer id'\
    ]
    \
}


int main()
{



    //object
    //(float X, float Y, float l1, float a1, float r_l1, float K1, float M1, float l2, float a2,float r_l2, float K2, float M2)
    DEP dep(0.0f, 0.5f,    0.4f,     0.0f,      0.2f,      0.5f,     0.1f,     0.4f, -0.0f,     0.2f,      0.5f,     0.1f);

    std::cout << "DOUBLE SPRING PENDULUM in OpenGL" << '\n' << std::endl;




	// Initialise GLFW

    if (!glfwInit())
    {
        std::cout << "couldn't init glfw" << '\n' << std::endl;

        return -1;
    }
    
    
    int version[] = { 4, 6 };
    Window window(1024, 1024, "DEP", version );
    //check window
    if (window.Check_Env() == -1)
    {
        return -1;
    }





	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
        std::cout << "couldn't init GLEW" << '\n' << std::endl;

		glfwTerminate();
		return -1;
	}

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	

	// Dark blue background





    //made it work for one ask yourself if you want to do the abstraction before drawing all four




   
    

    VertexArray vaC1;
    VertexArray vaC2;
    VertexArray vaL1;
    VertexArray vaL2;

    VertexBuffer VBC1(dep.circle1.point_array, dep.circle1.n_of_points * 2 * sizeof(float));
    VertexBuffer VBL1(dep.line1.pos, 2 * 2 * sizeof(float));
    VertexBuffer VBC2(dep.circle2.point_array, dep.circle2.n_of_points * 2 * sizeof(float));
    VertexBuffer VBL2(dep.line2.pos, 2 * 2 * sizeof(float));

    vaC1.AddBuffer(VBC1,2);
    vaL1.AddBuffer(VBL1,2);
    vaC2.AddBuffer(VBC2,2);
    vaL2.AddBuffer(VBL2,2);


    // Create buffer and copy data
    
    //the number of buffer object names to be generated,an array in which the generated buffer object names are stored.
    //GLuint bufferC1;
    
    

    //// define vertex layout

    
    //GLuint VertexArrayIDC2;
    //glGenVertexArrays(1, &VertexArrayIDC2);
    //glBindVertexArray(VertexArrayIDC2);

    //GLuint bufferC2;
    //glGenBuffers(1, &bufferC2);

    //GLCall(glBindVertexArray(VertexArrayID));

    //GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffers[1]));
    //GLCall(glBufferData(GL_ARRAY_BUFFER, dep.circle2.n_of_points * 2 * sizeof(float), dep.circle2.point_array, GL_DYNAMIC_DRAW));

    //// define vertex layout


    //glVertexAttribPointer is alredy attaching bound buffer to VAO void glVertexArrayVertexBuffers(GLuint vaobj,GLuint first,GLsizei count,const GLuint * buffers,const GLintptr * offsets,const GLsizei * strides);— attach multiple buffer objects to a vertex array object


    ShaderProgramSource source = ParseShader("src/Shaders/Simple.shader");

    std::cout << "VERTEX" << std::endl << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl << source.FragmentSource << std::endl;

    unsigned int shader = (CreateShader(source.VertexSource, source.FragmentSource));
    GLCall(glUseProgram(shader));
    const float color[4] = { 0.5f,0.5f,0.5f,1.0f };
    window.Background_Color(color);

    while ( window.Get_Key(GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window.window) == 0) {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );


        
        vaC1.Bind();
        GLCall(glDrawArrays(GL_LINE_LOOP, 0, dep.circle1.n_of_points)); 
        vaL1.Bind();
        GLCall(glDrawArrays(GL_LINES, 0, 2));
        vaC2.Bind();
        GLCall(glDrawArrays(GL_LINE_LOOP, 0, dep.circle2.n_of_points));
        vaL2.Bind();
        GLCall(glDrawArrays(GL_LINES, 0, 2));

        // Swap buffers
        window.SwapBuffers();
		

        //physics stuff
        dep.update();


        VBC1.SubData(dep.circle1.point_array);

        VBC2.SubData(dep.circle2.point_array);

	} // Check if the ESC key was pressed or the window was closed


	// Cleanup VBO
	GLCall(glDeleteProgram(shader));

	return 0;
 }

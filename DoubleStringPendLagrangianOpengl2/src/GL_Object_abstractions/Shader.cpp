#include <GL_Object_abstractions/Shader.h>


Shader::Shader(const std::string& filepath)
{
    std::ifstream stream(filepath);// look this up
    std::string line;

    while (getline(stream, line))//go through file. assign getline to line
    {
        source << line << '\n';
    }


}

Program::Program(Shader& vs, Shader& fs)
{
}



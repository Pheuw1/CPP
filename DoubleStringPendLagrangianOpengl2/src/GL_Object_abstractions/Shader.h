#pragma once
#include <fstream>
#include <string>
#include <sstream>

class Shader {

	std::string source;
	unsigned int m_ID;

public:

	Shader(const std::string& filepath);

};


class Program{
	unsigned int m_ID;
	unsigned int m_VS;
	unsigned int m_FS;

public:

	Program(Shader& vs, Shader& fs);

};
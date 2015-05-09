#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

struct Shader
{
    GLuint prog;

    Shader (const GLchar *vPath, const GLchar *fPath)
	{
		std::string vString;
		std::string fString;

		try
		{
			std::ifstream vFile (vPath);
			std::ifstream fFile (fPath);
			std::stringstream vStream, fStream;
			vStream << vFile.rdbuf ();
			fStream << fFile.rdbuf ();
			vFile.close ();
			fFile.close ();

			vString = vStream.str ();
			fString = fStream.str ();
		}
		catch (std::exception e)
		{
			std::cerr << "ERROR: Shader file can't successfully read" << std::endl;
		}
		const GLchar *vsString = vString.c_str ();
		const GLchar *fsString = fString.c_str ();

		GLuint vs, fs;
		GLint success;
		GLchar infoLog[512];

		// vertex shader
		vs = glCreateShader (GL_VERTEX_SHADER);
		glShaderSource (vs, 1, &vsString, nullptr);
		glCompileShader (vs);

		glGetShaderiv (vs, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog (vs, 512, NULL, infoLog);
			std::cerr << "ERROR: vertex shader compilation failed.\n" << infoLog << std::endl;
		}

		// fragment shader
		fs = glCreateShader (GL_FRAGMENT_SHADER);
		glShaderSource (fs, 1, &fsString, nullptr);
		glCompileShader (fs);

		glGetShaderiv (fs, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog (fs, 512, NULL, infoLog);
			std::cerr << "ERROR: fragment shader compilation failed.\n" << infoLog << std::endl;
		}

		this->prog = glCreateProgram ();
		glAttachShader (this->prog, vs);
		glAttachShader (this->prog, fs);
		glLinkProgram (this->prog);

		glGetProgramiv (this->prog, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog (this->prog, 512, NULL, infoLog);
			std::cerr << "ERROR: shader program link failed.\n" << infoLog << std::endl;
		}
		glDeleteShader (vs);
		glDeleteShader (fs);
	}

	void use ()
	{
		glUseProgram (this->prog);
	}
};

#endif

#include "shader.h"

namespace gaijin
{
	namespace graphics
	{
		Shader::Shader(const char * filePath) 
			: s_pr_filePath(filePath)
		{
			s_pr_ShaderID = s_pr_load();
			s_enable();
		}

		Shader::~Shader()
		{
			glDeleteShader(s_pr_ShaderID);
		}

		void Shader::s_enable() const
		{
			glUseProgram(s_pr_ShaderID);
		}

		void Shader::s_disable() const
		{
			glUseProgram(0);
		}

		void Shader::s_pr_print()
		{
			std::cout << s_pr_FilePaths.VertexSource << std::endl;
			std::cout << s_pr_FilePaths.FragmentSource << std::endl;
		}

		GLuint Shader::s_pr_load()
		{
			s_pr_FilePaths = s_pr_read_file(s_pr_filePath);
			//print();
			GLuint id = s_pr_createShader(s_pr_FilePaths.VertexSource, s_pr_FilePaths.FragmentSource);
			
			return id;
		}

		GLuint Shader::s_pr_compileShader(unsigned int type, const std::string & source)
		{
			unsigned int id = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(id, length, &length, message);
				std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex: " : "fragement: ") << std::endl;
				std::cout << message << std::endl;
				glDeleteShader(id);
				return 0;
			}

			return id;
		}

		GLuint Shader::s_pr_createShader(const std::string & vertexShader, const std::string & fragmentShader)
		{
			GLuint program = glCreateProgram();
			GLuint vs = s_pr_compileShader(GL_VERTEX_SHADER, vertexShader);
			GLuint fs = s_pr_compileShader(GL_FRAGMENT_SHADER, fragmentShader);

			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}

		ShaderProgramSource Shader::s_pr_read_file(const std::string & filepath)
		{
			std::ifstream stream(filepath);

			enum class ShaderType
			{
				NONE = -1, VERTEX = 0, FRAGMENT = 1
			};


			std::string line;
			std::stringstream ss[2];
			ShaderType type = ShaderType::NONE;
			while (getline(stream, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAGMENT;
					}
				}
				else
				{
					ss[(int)type] << line << '\n';
				}

			}

			return { ss[0].str(),ss[1].str() };
		}

		GLint Shader::s_pr_getUniformLocation(const GLchar * name)
		{
			return glGetUniformLocation(s_pr_ShaderID, name);
		}

		void Shader::s_setUniform1f(const GLchar * name, float value)
		{
			glUniform1f(s_pr_getUniformLocation(name), value);
		}

		void Shader::s_setUniform1i(const GLchar * name, int value)
		{
			glUniform1i(s_pr_getUniformLocation(name), value);

		}

		void Shader::s_setUniform2f(const GLchar * name, const maths::vec2 & vector)
		{
			glUniform2f(s_pr_getUniformLocation(name), vector.x,vector.y);

		}

		void Shader::s_setUniform3f(const GLchar * name, const maths::vec3 & vector)
		{
			glUniform3f(s_pr_getUniformLocation(name), vector.x,vector.y,vector.z);

		}

		void Shader::s_setUniform4f(const GLchar * name, const maths::vec4 & vector)
		{
			glUniform4f(s_pr_getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);

		}

		void Shader::s_setUniformMat4(const GLchar * name, const maths::mat4 & matrix)
		{
			glUniformMatrix4fv(s_pr_getUniformLocation(name), 1, GL_FALSE, matrix.elements);

		}

	}
}


#pragma once

#include<GL/glew.h>
#include "../maths/maths.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

namespace gaijin
{
	namespace graphics
	{
		struct ShaderProgramSource
		{
			std::string VertexSource;
			std::string FragmentSource;
		};

		class Shader
		{
		public:
			Shader(const char* filePath);
			~Shader();

			void s_enable() const;
			void s_disable() const;



			void s_setUniform1f(const GLchar* name, float value);
			void s_setUniform1i(const GLchar* name, int value);
				 
			void s_setUniform2f(const GLchar* name, const maths::vec2& vector);
			void s_setUniform3f(const GLchar* name, const maths::vec3& vector);
			void s_setUniform4f(const GLchar* name, const maths::vec4& vector);
				 
				 
			void s_setUniformMat4(const GLchar* name, const maths::mat4& matrix);


		private:
			GLuint s_pr_ShaderID;
			const char* s_pr_filePath;
			ShaderProgramSource s_pr_FilePaths;

			void s_pr_print();

			GLuint s_pr_load();

			GLuint s_pr_compileShader(unsigned int type, const std::string& source);
			GLuint s_pr_createShader(const std::string& vertexShader, const std::string & fragmentShader);

			ShaderProgramSource s_pr_read_file(const std::string & filepath);
			
			GLint s_pr_getUniformLocation(const GLchar* name);
		};





	}
}
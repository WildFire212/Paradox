#pragma once
#include<GL/glew.h>
#include"../utils/fileutils.h"
#include"../maths/maths.h"
#include"../Components/Transform.h"
#include"../Components/Material.h"
#include"../graphics/Resource/ShaderResource.h"	
#include<map>
#include<memory>
#include<string>
#include<utility>

namespace Paradox {
	namespace graphics {

		class RenderingEngine; 
		class Shader {
		protected: 
			static std::map<std::string, std::shared_ptr<ShaderResource>> m_LoadedShaders; 
			std::shared_ptr<ShaderResource> m_ShaderResource;
			std::string m_FileNameKey;
								//StructName	StructContent Type
			std::map<std::pair<std::string, std::string>,std::string> m_StructContentNames;
			//uniforms 
			
		
		public: 
			Shader(const char* vertLoc, const char* fragLoc);
			~Shader();
			
			auto loadShaders(const char* vertShader, const char* fragShader) -> ShaderResource;
			
			void bind() const; 
			void unbind() const; 

			//getters 
			auto getShaderResource() const -> const ShaderResource&;
			//setters 
			void SetUniform1i(const char* name, int value); 
			void SetUniform1f(const char* name,float value); 
			void SetUniformMat4(const char* name,maths::mat4 value );
			void SetUniform2f(const char* name, maths::vec2 value);
			void SEtmat4(const char* name, glm::mat4 vluae) {
				glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,glm::value_ptr(vluae));
			}
			void SetUniform3f(const char* name, maths::vec3 value);
			void SetUniform4f(const char* name, maths::vec4 value);
			virtual void updateAllUniforms(Transform* transform, const RenderingEngine* engine, const Material* material);
		protected: 
			void addShader(const GLuint& ShaderProgram, const char* shaderSrc, GLenum shaderType);
			auto getUniformLocation(const char* name) -> GLuint;
			void addUniforms(const char* ShaderCode, ShaderResource* shaderResource);
			void checkStructs(std::string shaderCode); 
			auto findInStruct(std::string name) -> std::map<std::pair<std::string, std::string>, std::string>::iterator;
		};

} }
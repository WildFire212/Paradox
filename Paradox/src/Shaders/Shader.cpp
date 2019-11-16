
#include "Shader.h"
#include"../core/RenderingEngine.h"
#include"../Lights/Light.h"
#include"../maths/maths.h"
namespace Paradox {
	namespace graphics {
		std::map<std::string, std::shared_ptr<ShaderResource>> Shader::m_LoadedShaders;
		Shader::Shader(const char* vertLoc, const char* fragLoc) {

			FileUtils file;

			std::string vertShaderFile = file.readFile(vertLoc);
			std::string fragShaderFile = file.readFile(fragLoc);

			std::string fileLocation = vertShaderFile + fragShaderFile; 
			m_FileNameKey = std::string(fileLocation);
			auto find = m_LoadedShaders.find(m_FileNameKey);
			if (find != m_LoadedShaders.end())
			{
				m_ShaderResource = std::shared_ptr<ShaderResource>(find->second);
			}
			else {

				const char* vertShader = vertShaderFile.c_str(); 
				const char* fragShader= fragShaderFile.c_str(); 

				m_ShaderResource = std::make_shared<ShaderResource>(loadShaders(vertShader,fragShader));
				m_LoadedShaders[m_FileNameKey] = m_ShaderResource;
			}
			
		}
		Shader::~Shader()
		{
			m_ShaderResource.reset();
			auto search = m_LoadedShaders.find(m_FileNameKey);
			if (search->second.use_count() == 0)
			{
				m_LoadedShaders.erase(m_FileNameKey);
			}
		}
		ShaderResource Shader::loadShaders(const char* vertShader, const char* fragShader)
		{
			GLuint ShaderProgram;
			ShaderResource  shaderResource; 
			ShaderProgram = glCreateProgram();

			if (!ShaderProgram)
			{
				std::cout << "Failed to Create Shader" << std::endl;
			}

			addShader(ShaderProgram, vertShader, GL_VERTEX_SHADER);
			addShader(ShaderProgram, fragShader, GL_FRAGMENT_SHADER);

			GLint result = 0;
			GLchar eLog[1024] = { 0 };

			glLinkProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &result);
			if (!result)
			{
				glGetProgramInfoLog(ShaderProgram, sizeof(eLog), NULL, eLog);
				printf("Error linking program: '%s'\n", eLog);
				return shaderResource;
			}
			
			glValidateProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &result);
			if (!result)
			{
				glGetProgramInfoLog(ShaderProgram, sizeof(eLog), NULL, eLog);
				printf("Error linking program: '%s'\n", eLog);
				return shaderResource;
			}
			shaderResource.setShaderProgram(ShaderProgram);
			checkStructs(vertShader); 
			checkStructs(fragShader); 
			addUniforms(vertShader,&shaderResource);
			addUniforms(fragShader,&shaderResource);
			
			//shaderResource.printContent(); 

			return shaderResource; 

		}

		void Shader::addShader(const GLuint& ShaderProgram, const char* shaderSrc, GLenum shaderType) {
			GLuint shader = glCreateShader(shaderType);

			const GLchar* code[1];
			code[0] = shaderSrc;

			GLint codeLength[1];
			codeLength[0] = strlen(shaderSrc);
			
			glShaderSource(shader, 1, code, codeLength);

			glCompileShader(shader);

			GLint result; 
			GLchar eLog[1024] = { 0 };
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

			if (!result)
			{
				glGetShaderInfoLog(shader, 1024, NULL, eLog);
				fprintf(stderr, "Error compiling the %d Shader: '%s'\n", shaderType, eLog);
				return;
			}

			glAttachShader(ShaderProgram, shader);
		}
		void Shader::bind() const {
			glUseProgram(m_ShaderResource->getShaderProgram());
		}
		void Shader::unbind() const {
			glUseProgram(0);
		}
		GLuint Shader::getUniformLocation(const char* name) {
			GLuint loc = glGetUniformLocation(m_ShaderResource->getShaderProgram(), name);
			return loc;
		}
		void Shader::addUniforms(const char * ShaderCode,ShaderResource* shaderResource)
		{
			std::string shaderCode(ShaderCode); 
			const std::string UNIFORM_KEYWORD = "uniform"; 
			size_t uniformPos = shaderCode.find(UNIFORM_KEYWORD, 0);
			
			while (uniformPos != -1)
			{
				size_t nextSemicolonPos = shaderCode.find(";", uniformPos);
				std::string Uniform = shaderCode.substr(uniformPos + UNIFORM_KEYWORD.length() ,nextSemicolonPos   - (uniformPos + UNIFORM_KEYWORD.length()));
				Uniform = FileUtils::trim(Uniform); 
				size_t spaceBWtype = Uniform.find(" ");
				
				//type and content
				std::string UniformType = Uniform.substr(0, spaceBWtype );
				std::string UniformContent = Uniform.substr(spaceBWtype + 1,Uniform.size()- spaceBWtype );
				//std::cout << "uniform name is -"<< UniformContent<< "-"<<UniformType << "-" << std::endl;
				
				auto it = findInStruct(UniformType); 
				if (it!= m_StructContentNames.end()) {
					//type found as struct 

					for (std::map<std::pair<std::string, std::string>, std::string>::iterator it = m_StructContentNames.begin();
						it != m_StructContentNames.end(); ++it)
					{
						if (it->first.first == UniformType) {

							auto find= findInStruct(it->second);	//found light in struct it->second = Light
							//struct in struct 
							if(find!= m_StructContentNames.end())
							{
								for (std::map<std::pair<std::string, std::string>, std::string>::iterator itr = m_StructContentNames.begin();
									itr != m_StructContentNames.end(); ++itr)
								{
									if (itr->first.first ==  it->second) {
										shaderResource->addUniformType(itr->second);
										shaderResource->addUniformName(UniformContent + "." + it->first.second + "."+itr->first.second);
									}
								}


							}
							//no struct in struct
							else {
								shaderResource->addUniformType(it->second);
								shaderResource->addUniformName(UniformContent + "." + it->first.second);
							}





						
						}
					}
					
				}
				else {
					//no struct involved
					shaderResource->addUniformType(UniformType);
					shaderResource->addUniformName(UniformContent);
				}

				uniformPos = shaderCode.find(UNIFORM_KEYWORD, nextSemicolonPos);
			}
			

		}
		void Shader::checkStructs(std::string shaderCode)
		{
			const std::string WHITESPACE = " \n\r\t\f\v";
			const std::string STRUCT_KEYWORD = "struct";		
			size_t structPos = shaderCode.find(STRUCT_KEYWORD, 0);

			while (structPos != -1)
			{
				size_t nextBracketPos = shaderCode.find("{", structPos);
				
				std::string StructName = shaderCode.substr(structPos + STRUCT_KEYWORD.length() , nextBracketPos - (structPos + STRUCT_KEYWORD.length() ));
				StructName = FileUtils::trim(StructName);
				size_t structContentTypePos = shaderCode.find_first_not_of(WHITESPACE, nextBracketPos + 1); 
				size_t nextsemicolon = shaderCode.find(";", nextBracketPos);
				size_t endBracketPos = shaderCode.find("}", structPos); 
				while (nextsemicolon != -1 && nextsemicolon < endBracketPos)
				{
					size_t spacePos = shaderCode.find_last_of(" ",nextsemicolon);
					//type of content 
					std::string structContentType = shaderCode.substr(structContentTypePos, spacePos - structContentTypePos);
					structContentType = FileUtils::trim(structContentType);

					//content name 
					std::string structContent = shaderCode.substr(spacePos, nextsemicolon - spacePos); 
					structContent = FileUtils::trim(structContent);
					//found content and the struct name what to do now if the content is a part of another struct"
					m_StructContentNames[std::make_pair(StructName,structContent)] = structContentType;
					//m_StructContentTypes.push_back(structContentType);
					structContentTypePos = shaderCode.find_first_not_of(WHITESPACE, nextsemicolon + 1 );
					nextsemicolon = shaderCode.find(";", nextsemicolon + 1);
				}
				
				//std::cout << "struct name is " << StructName << std::endl;
				//structs.push_back(StructName);
				structPos = shaderCode.find(STRUCT_KEYWORD, endBracketPos);
			}
			
		}
		std::map<std::pair<std::string, std::string>, std::string>::iterator Shader::findInStruct(std::string name)
		{
			std::map<std::pair<std::string, std::string>, std::string>::iterator it;

			for (it = m_StructContentNames.begin();
				it != m_StructContentNames.end(); ++it)
			{
				if (it->first.first == name) {

					break;
				}
			}

			return it; 

		}
		const ShaderResource & Shader::getShaderResource() const
		{
			// TODO: insert return statement here
			return *m_ShaderResource.get(); 
		}
		void Shader::SetUniform1i(const char* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}
		void Shader::SetUniform1f(const char* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}
		void Shader::SetUniformMat4(const char* name, maths::mat4 value) {
			glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE, value.elements);
		}
		void Shader::SetUniform2f(const char* name, Paradox::maths::vec2 value) {
			glUniform2f(getUniformLocation(name), value.x, value.y);
		}
		void Shader::SetUniform3f(const char* name, Paradox::maths::vec3 value) {
			glUniform3f(getUniformLocation(name), value.x, value.y,value.z);

		}
		void Shader::SetUniform4f(const char* name, Paradox::maths::vec4 value) {
			glUniform4f(getUniformLocation(name), value.x, value.y,value.z, value.w);

		}
		void Shader::updateAllUniforms(Transform * transform, const RenderingEngine * engine, const Material * material)
		{
			this->SetUniform3f("eyePosition", engine->getMainCamera().getPosition());
			//lighting 
			this->SetUniform1i("gPosition", 0);
			this->SetUniform1i("gNormal", 1);
			this->SetUniform1i("gAlbedoSpec", 2);
			unsigned int textureSamplersCount = 0; 
			for (int i = 0; i < m_ShaderResource->getUniformNames().size(); i++) {
			
				std::string uniformName = m_ShaderResource->getUniformNames()[i];
				//transform uniforms 
				if (uniformName.find("T_") == 0)
				{
					glm::mat4 proj = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);
					std::string unprefixedName = uniformName.substr(2, uniformName.size() - 2);
					if (unprefixedName == "projection")
						this->SEtmat4(uniformName.c_str(), proj);
						//this->SetUniformMat4(uniformName.c_str(), engine->getMainCamera().getProjection());
					else if(unprefixedName == "view")
					this->SetUniformMat4(uniformName.c_str(), engine->getMainCamera().calculateViewMatrix());
					else if(unprefixedName == "model")
					this->SetUniformMat4(uniformName.c_str(), transform->getTransformation());
				}
				//material uniforms 
				if (uniformName.find("M_") == 0)//zero for pos = 0
				{
					
					std::string unprefixedName = uniformName.substr(11, uniformName.size() - 11);
					
					if (m_ShaderResource->getUniformTypes()[i] == "float")
					{
						SetUniform1f(uniformName.c_str(), material->getFloat(unprefixedName));
					}
					else if (m_ShaderResource->getUniformTypes()[i] == "sampler2D")
					{
						textureSamplersCount++;
						SetUniform1i(uniformName.c_str(), textureSamplersCount);
						glActiveTexture(GL_TEXTURE0 + textureSamplersCount);
						glBindTexture(GL_TEXTURE_2D, material->getTexture(unprefixedName));
					}

						
				}
			
			
				//lights
				if (uniformName.find("L_") == 0)
				{
					size_t pos = uniformName.find_last_of(".");

					std::string unprefixedName = uniformName.substr(pos + 1, uniformName.size() - pos + 1);
			
					if (m_ShaderResource->getUniformTypes()[i] == "float")
					{
						SetUniform1f(uniformName.c_str(), engine->getActiveLight()->getValueMap()->getFloat(unprefixedName));//->getFloat(unprefixedName));
					}
					else if (m_ShaderResource->getUniformTypes()[i] == "vec3")
					{
						
						SetUniform3f(uniformName.c_str(), engine->getActiveLight()->getValueMap()->getVector3(unprefixedName));
					}
			
				}
			
			}
		}
} }

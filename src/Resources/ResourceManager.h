//#pragma once
//
//#include <iostream>
//#include <string>
//#include <memory>
//#include <map>
//
//namespace Renderer
//{
//	class ShaderProgram;
//}
//
//
//class ResourceManager{
//public:
//	ResourceManager(const std::string& executablePath);
//
//	ResourceManager(const ResourceManager&) = delete;
//	ResourceManager(ResourceManager&&) = delete;
//
//	ResourceManager& operator=(const ResourceManager) = delete;
//	ResourceManager& operator=(ResourceManager&&) = delete;
//	
//	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
//	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName);
//
//	~ResourceManager() = default;
//
//private:
//	std::string& getFileString(const std::string& relativeFilePath);
//
//
//	typedef std::map < const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
//	ShaderProgramMap m_shaderPrograms;
//
//	std::string m_path;
//
//};
//#include "ResourceManager.h"
//#include "../Renderer/ShaderProgram.h"
//
//#include <sstream>
//#include <fstream>
//#include <iostream>
//
//ResourceManager::ResourceManager(const std::string& executablePath)
//{
//	size_t found = executablePath.find_last_of("/\\");
//	m_path = executablePath.substr(0, found);	
//}
//
//std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
//{
//	std::string vertexString = getFileString(vertexPath);
//	if(vertexString.empty())
//	{
//		std::cerr << "No vertex shader!" << std::endl;
//		return nullptr;
//	}
//
//	std::string fragmentString = getFileString(vertexPath);
//	if (fragmentString.empty())
//	{
//		std::cerr << "No vertex shader!" << std::endl;
//		return nullptr;
//	}
//
//	m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString));
//}
//
//std::string& ResourceManager::getFileString(const std::string& relativeFilePath)
//{
//	std::ifstream f;
//	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
//	if (!f.is_open()) {
//		std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
//		return std::string();
//
//	}
//	
//	std::stringstream buffer;
//	buffer << f.rdbuf();
//	return buffer.str();
//}

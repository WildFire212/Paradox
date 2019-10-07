#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
namespace Paradox {
	class FileUtils
	{
	public:

		

		
		std::string readFile(const char* fileloc) {
			std::string file;
			std::fstream FILE(fileloc, std::ios::in);

			if (!FILE.is_open())
			{
				std::cout << "Failed to Read from file" << fileloc << std::endl;
			}
			std::string line;
			while (!FILE.eof())
			{
				std::getline(FILE, line);

				if (line.rfind("#include", 0) == 0)
				{
					std::string filename = line.substr(9, (line.length() - 10));
					std::string fileadd = "src/Shaders/GLSLShaders/ShaderDependencies/";
					fileadd = fileadd + filename;
					file.append(readFile(fileadd.c_str()));
				}
				else {
					file.append(line + "\n");
				}
			}
			FILE.close();
			return file;
		}

	private:
		static std::string ltrim(const std::string& s)
		{
			const std::string WHITESPACE = " \n\r\t\f\v";
			size_t  start = s.find_first_not_of(WHITESPACE);
			if (start == std::string::npos)
			{
				return "";
			}
			else if (start != std::string::npos)
			{
				return s.substr(start);
			}

		}
		static std::string rtrim(const std::string& s)
		{
			const std::string WHITESPACE = " \n\r\t\f\v";
			size_t  end = s.find_last_not_of(WHITESPACE);
			if (end == std::string::npos)
			{
				return "";
			}
			else if (end != std::string::npos)
			{
				return s.substr(0, end + 1);
			}

		}
	public:
		static std::string trim(const std::string& s)
		{
			return rtrim(ltrim(s));
		}

		template <class T>
		static T* convertToArray(std::vector<T> vecArray)
		{
			T* arr = new T[vecArray.size()];
			for (size_t i = 0; i < vecArray.size(); i++)
			{
				arr[i] = vecArray[i];
			}
			return arr;
		}
		template <class T> 
		static std::vector<T> convertToVectorArray(T* array) {
			std::vector<T> vecArray; 
		}

		

	};
}
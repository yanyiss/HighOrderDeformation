#pragma once
#include <string>
#include <vector>
#include <io.h>
void getFiles(std::string path, std::vector<std::string>& files)
{
	//文件句柄
	intptr_t  hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

#include <qstring.h>
void truncateFilePath(std::string &file)
{
	QString fileName = QString::fromStdString(file);
	int id = fileName.lastIndexOf("/");
	if (id == -1)
	{
		id = fileName.lastIndexOf("\\");
		if (id == -1)
			return;
	}
	file = fileName.right(fileName.length() - id - 1).toLatin1().data();
}

void truncateFileExtension(std::string &file)
{
	QString fileName = QString::fromStdString(file);
	int id = fileName.lastIndexOf(".");
	if (id == -1)
		return;
	fileName.truncate(id);
	file = fileName.toLatin1().data();
}

//std::string append_para(std::string file_name, std::string dlc) {
//	size_t dot_pos = file_name.find_last_of('.');
//	if (dot_pos != std::string::npos) {
//		// 在文件名与扩展名之间插入下划线和变量 a
//		return file_name.substr(0, dot_pos) + "_" + dlc + file_name.substr(dot_pos);
//	}
//	else {
//		// 如果没有找到扩展名，就直接在末尾拼接
//		return file_name + "_" + dlc;
//	}
//}

#include <direct.h>
void create_para_subfile(std::string &file_name, std::string para_name) 
{
	// 1. 提取文件所在的目录路径
	size_t pos = file_name.find_last_of("\\/");
	std::string parent_dir = (pos != std::string::npos) ? file_name.substr(0, pos) : "";

	// 2. 创建新文件夹，命名为a的值
	std::string new_dir = parent_dir + "\\" + para_name;  // 拼接新文件夹路径
	if (_mkdir(new_dir.c_str()) == 0) {
		std::cout << "Directory created: " << new_dir << std::endl;
	}
	else {
		std::cerr << "Failed to create directory or directory already exists: " << new_dir << std::endl;
	}

	// 3. 在新创建的文件夹中创建data.txt文件
	std::string file = file_name;
	truncateFilePath(file);
	file_name = new_dir + "\\" + file;  // 拼接新文件路径
}
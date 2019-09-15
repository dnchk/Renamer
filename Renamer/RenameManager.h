#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>

namespace fs = std::filesystem;

class RenameManager {
private:
	std::string directory;
	std::vector<fs::path> paths;
	std::vector<int> fileNumberNames;
	std::vector<std::tuple<fs::path, int>> pathsNFilesNumberNames;

	void extractFileNames(size_t fNum);
	void orderPathsNamesTuple(size_t fNum);
	void sortPathsNFilesNames();
public:
	RenameManager(std::string dir)
		: directory(dir) {}
	
	void readDirectory();
	void numerateFiles(size_t firstNum = 1, bool reverse = false);
};

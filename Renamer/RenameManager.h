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
	std::vector<std::string> paths;
	std::vector<int> fileNumberNames;
	std::vector<std::tuple<std::string, int>> pathsNFilesNumberNames;

	void extractFileNames();
	void orderPathsNamesTuple();
	void sortPathsNFilesNames();
public:
	RenameManager(std::string dir)
		: directory(dir) {}
	
	void readDirectory();
	void renameFilesNumeric(size_t firstNum);
	void printPathsNFilesNumberNames();
	void printPaths();
};

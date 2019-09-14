#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdio>

#include "RenameManager.h"

// TO DO: 
// solve issue when renaming occurs not first time, but with different first image name
// implement other types of functionality (renaming cases, other file formats), create ui

int main() {
	std::string path = "D:/University/current/DO/2";
	int firstNum = 1;

	RenameManager * rm = new RenameManager(path);
	rm->readDirectory();
	rm->renameFilesNumeric(firstNum);
	delete rm;
}

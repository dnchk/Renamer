#include "RenameManager.h"

// TO DO: 
// reverse after straight order issue
// solve issue when renaming occurs not first time, but with different first image name
// change atoi to stoi and resolve renaming issue when image names aren't numbers
// implement other types of functionality (renaming cases, other file formats), create ui

int main() {
	std::string path = "D:/University/current/DO/1";
	int firstNum = 1;
	bool reverse = true;

	RenameManager * rm = new RenameManager(path);
	rm->readDirectory();
	rm->numerateFiles(firstNum, reverse);
	delete rm;
}

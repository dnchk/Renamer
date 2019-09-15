#include "RenameManager.h"

void RenameManager::readDirectory() {
	try {
		if (!paths.empty()) {
			paths.clear();
		}
		for (const auto & entry : fs::directory_iterator(directory)) {
			auto path = entry.path();
			paths.push_back(path);
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
}

void RenameManager::numerateFiles(size_t firstNum, bool reverse) {
	orderPathsNamesTuple(firstNum);
	sortPathsNFilesNames();

	fs::path path = "";
	size_t i = reverse ? (firstNum + pathsNFilesNumberNames.size() - 1) : firstNum;

	if (reverse) {
		/* NOTE: swap only swaps, not renames files, lol
				 looks like it is necessary to create temp folder,
				 move there second half of the files, rename first part,
				 rename second - and then move second part of files where it belongs
		*/
		/*size_t size = pathsNFilesNumberNames.size();
		fs::path swapPath = "";
		// NOTE: decrease, so paths.at(i) would not be out of range
		i--;
		for (size_t k = 0; k < size / 2; ++k) {
			path = std::get<0>(pathsNFilesNumberNames.at(k));
			swapPath = paths.at(i--);
			fs::swap(path, swapPath);
		}*/
	}
	else {
		std::string nameNum = "";
		std::string newPath = "";

		for (auto pathNFileNumberName : pathsNFilesNumberNames) {
			path = std::get<0>(pathNFileNumberName);
			nameNum = std::to_string(i++);
			newPath = directory + "/" + nameNum + ".jpg";
			fs::rename(path, newPath);
		}
	}
}

void RenameManager::extractFileNames(size_t fNum) {
	if (!fileNumberNames.empty()) {
		fileNumberNames.clear();
	}
	std::string fileNumberName = "";
	size_t numName = 0;
	for (auto path : paths) {
		fileNumberName = path.stem().string();
		numName = std::atoi(fileNumberName.c_str());
		/* NOTE: if files in directory aren't numerated already, assign startingNum,
				 else get current number-name from the pic's data */
		if (!numName) {
			numName = fNum;
		}
		fileNumberNames.push_back(numName);
	}
}

void RenameManager::orderPathsNamesTuple(size_t fNum) {
	if (!pathsNFilesNumberNames.empty()) {
		pathsNFilesNumberNames.clear();
	}
	extractFileNames(fNum);
	if (paths.size() == fileNumberNames.size()) {
		for (size_t i = 0; i < paths.size(); ++i) {
			pathsNFilesNumberNames.push_back(std::make_tuple(paths.at(i), fileNumberNames.at(i)));
		}
	}
	else {
		std::cout << "\npaths number is differenet with number of file names\n";
	}
}

void RenameManager::sortPathsNFilesNames() {
	std::sort(pathsNFilesNumberNames.begin(), pathsNFilesNumberNames.end(),
		[](const std::tuple<fs::path, int>& a, const std::tuple<fs::path, int>& b) -> bool {
			return std::get<1>(a) < std::get<1>(b);
	});
}

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
	size_t i = firstNum;

	std::string nameNum = "";
	std::string newPath = "";

	if (reverse) {
		size_t size = pathsNFilesNumberNames.size();
		size_t halfSize = size / 2;
		size_t o = size;
		
		fs::path storagePath = fs::path(directory) / "storageFolder";
		fs::path target;

		try {
			fs::create_directory(storagePath);

			// move first half of files to storage directory
			for (size_t k = 0; k < halfSize; ++k) {
				path = std::get<0>(pathsNFilesNumberNames.at(k));
				target = storagePath / path.filename();
				fs::copy_file(path, target);
				fs::remove(path);
				// and rename there
				nameNum = std::to_string(o--);
				newPath = storagePath.string() + "/" + nameNum + ".jpg";
				fs::rename(target, newPath);
			}
			// rename second half
			for (size_t p = size - 1; p >= halfSize; --p) {
				path = std::get<0>(pathsNFilesNumberNames.at(p));
				nameNum = std::to_string(i++);
				newPath = directory + "/" + nameNum + ".jpg";
				fs::rename(path, newPath);
			}
			// return renamed first half to base folder
			for (const auto & entry : fs::directory_iterator(storagePath)) {
				path = entry.path();
				target = directory / path.filename();
				fs::copy_file(path, target);
			}
			// then delete storage dir
			fs::remove_all(storagePath);
		}
		catch (std::exception ex) {
			std::cout << ex.what() << "\n";
		}

	}
	else {
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

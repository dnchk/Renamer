#include "RenameManager.h"

void RenameManager::readDirectory() {
	try {
		if (!paths.empty()) {
			paths.clear();
		}
		for (const auto & entry : fs::directory_iterator(directory)) {
			auto path = entry.path();
			paths.push_back(path.string());
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
}

void RenameManager::numerateFiles(size_t firstNum, bool reverse) {
	orderPathsNamesTuple();
	sortPathsNFilesNames();

	std::string path = "";
	std::string nameNum = "";
	size_t i = reverse ? (firstNum + pathsNFilesNumberNames.size() - 1) : firstNum;

	for (auto pathNFileNumberName : pathsNFilesNumberNames) {
		path = std::get<0>(pathNFileNumberName);
		nameNum = reverse ? (std::to_string(i--)) : (std::to_string(i++));
		fs::rename(path, directory + "/" + nameNum + ".jpg");
	}
}

void RenameManager::extractFileNames() {
	if (!fileNumberNames.empty()) {
		fileNumberNames.clear();
	}
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif
	char dotSep = '.';
	size_t i = 0;
	size_t k = 0;
	for (auto path : paths) {
		i = path.rfind(sep, path.length());
		if (i != std::string::npos) {
			auto str = path.substr(i + 1, path.length() - 1);
			k = str.rfind(dotSep, str.length());
			auto s = str.substr(0, k);
			fileNumberNames.push_back(std::atoi(s.c_str()));
		}
	}
}

void RenameManager::orderPathsNamesTuple() {
	if (!pathsNFilesNumberNames.empty()) {
		pathsNFilesNumberNames.clear();
	}
	extractFileNames();
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
		[](const std::tuple<std::string, int>& a, const std::tuple<std::string, int>& b) -> bool {
			return std::get<1>(a) < std::get<1>(b);
	});
}

void RenameManager::printPathsNFilesNumberNames() {
	std::cout << "\n";
	for (auto v : pathsNFilesNumberNames) {
		std::cout << std::get<0>(v) << " " << std::get<1>(v) << "\n";
	}
}

void RenameManager::printPaths() {
	std::cout << "\n";
	for (auto path : paths) {
		std::cout << path << "\n";
	}
}

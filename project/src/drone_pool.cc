#include "src/drone_pool.h"

std::vector<csci3081::droneSpecs> csci3081::createDroneModelList(std::string filename) {
	std::vector<droneSpecs> drone_model_list;

	std::fstream fin;
	std::string line, word;
	std::unordered_map<std::string,int> header;
	std::vector<std::string> row;
	int header_count = 0;
	
	fin.open(filename, std::fstream::in);
	
	if (fin.is_open()) {
		std::getline(fin, line);
		std::stringstream s(line);
		while (std::getline(s, word, ',')) {
			header[word] = header_count++;
		}

		//std::cout << "\nLines:\n";
		while (std::getline(fin, line)) {
			row.clear();

			//std::cout << line << std::endl;
			std::stringstream s(line);
			while (std::getline(s, word, ',')) {
				row.push_back(word);
			}

			drone_model_list.push_back(droneSpecs(row[header["Model #"]],
							stof(row[header["Mass (kg)"]]),
							stof(row[header["Max Speed (km/h)"]]),
							stof(row[header["Base Acceleration (m/s^2)"]]),
							stof(row[header["WeightCapacity (kg)"]]),
							stoi(row[header["Base Battery Capacity (seconds)"]])));
			
		}
		

		fin.close();

	}
	else {
		std::cout << "Error, failed to open file" << std::endl;
	}
	return drone_model_list;
}
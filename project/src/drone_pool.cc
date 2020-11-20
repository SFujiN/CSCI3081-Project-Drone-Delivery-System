#include "src/drone_pool.h"

std::unordered_map<std::string,csci3081::droneSpecs> csci3081::createDroneModelList(std::string filename) {
	std::unordered_map<std::string,droneSpecs> drone_model_list;

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

			if (drone_model_list.find(row[header["Model #"]]) == drone_model_list.end()) {
				drone_model_list[row[header["Model #"]]] =
								droneSpecs(row[header["Model #"]],
								stof(row[header["Mass (kg)"]]),
								stof(row[header["Max Speed (km/h)"]]),
								stof(row[header["Base Acceleration (m/s^2)"]]),
								stof(row[header["WeightCapacity (kg)"]]),
								stof(row[header["Base Battery Capacity (seconds)"]]));
			}
		}
		fin.close();
	}
	else {
		std::cout << "Error, failed to open file" << std::endl;
	}
	return drone_model_list;
}

void csci3081::updateDroneModelList(std::unordered_map<std::string,csci3081::droneSpecs> &list, std::string filename) {
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

		while (std::getline(fin, line)) {
			row.clear();

			std::stringstream s(line);
			while (std::getline(s, word, ',')) {
				row.push_back(word);
			}

			if (list.find(row[header["Model #"]]) == list.end()) {
				list[row[header["Model #"]]] =
								(droneSpecs(row[header["Model #"]],
								stof(row[header["Mass (kg)"]]),
								stof(row[header["Max Speed (km/h)"]]),
								stof(row[header["Base Acceleration (m/s^2)"]]),
								stof(row[header["WeightCapacity (kg)"]]),
								stof(row[header["Base Battery Capacity (seconds)"]])));
			}
		}
		fin.close();
	}
	else {
		std::cout << "Error, failed to open file" << std::endl;
	}
}


bool csci3081::isModelListed(std::unordered_map<std::string,csci3081::droneSpecs> list, std::string model) {
	return (list.find(model) != list.end());
}

std::ostream& csci3081::operator<<(std::ostream& out, const csci3081::droneSpecs& d) {
	return out << "Model#: " << d.model_ << "\n"
		   << "Mass (kg): " << d.mass_ << "\n"
		   << "Max Speed (km/h): " << d.max_speed_ << "\n"
		   << "Base Acceleration (m/s^2): " << d.base_acc_ << "\n"
		   << "WeightCapacity (kg): " << d.weight_cap_ << "\n"
		   << "Base Battery Capacity (seconds): " << d.base_bat_cap_ << "\n";
}

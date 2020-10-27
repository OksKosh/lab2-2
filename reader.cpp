#include <iostream>
#include <limits>

int get_option() {
	std::cout << "\nEnter option:\n";
	std::cout << "1 - Open mapping file\n";
	std::cout << "2 - Map file\n";
	std::cout << "3 - Read data\n";
	std::cout << "0 - Exit\n";
	
	int option = 0;
	std::cin >> option;
	
	while (std::cin.fail() || option > 3 || option < 0) {
		std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
		std::cout << "Incorrect option. Please, try again\n";		
		std::cin >> option;
	}
	
	return option;
}

void open_file() {
	
}

void map_file() {
	
}

void read_data() {
	
}

void (*function_pointers[4])() = {
	nullptr,
	open_file,
	map_file,
	read_data,
};

int main() {
	int option = 0;
	
	while ((option = get_option()) != 0) {
		(*function_pointers[option])();
	}
	
	return 0;
}

#include <iostream>
#include <limits>
#include <windows.h>

HANDLE map_file_handle;
PVOID map_view_addr;

int get_option() {
	std::cout << "\nEnter option:\n";
	std::cout << "1 - Open mapping file\n";
	std::cout << "2 - Map view of file\n";
	std::cout << "3 - Read data\n";
	std::cout << "4 - Unmap view of file\n";
	std::cout << "0 - Exit\n";
	
	int option = 0;
	std::cin >> option;
	
	while (std::cin.fail() || option > 4 || option < 0) {
		std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
		std::cout << "Incorrect option. Please, try again\n";		
		std::cin >> option;
	}
	
	return option;
}

void open_file() {
	map_file_handle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "mapping_file");
	if (map_file_handle != INVALID_HANDLE_VALUE) {
        std::cout << "Mapping file opened\n";
    } else {
    	std::cout << "Can not open mapping file\n";
	}
}

void map_file() {
	map_view_addr = MapViewOfFile(map_file_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (map_view_addr == 0){
        std::cout << "Can not map view of file\n";
	} else {
		std::cout << "View of file mapped\n";
	}
}

void read_data() {
	char data[1024];	
	memcpy(data, (char*)map_view_addr, 1024);
    std::cout << "At "<< map_view_addr << " written " << data << "\n";
}

void unmap_file() {
	if (UnmapViewOfFile(map_view_addr)) {
		std::cout << "View of file unmapped\n";
	} else {
		std::cout << "Can not unmap view of file\n";
	}
}

void (*function_pointers[5])() = {
	nullptr,
	open_file,
	map_file,
	read_data,
	unmap_file,
};

int main() {
	int option = 0;
	
	while ((option = get_option()) != 0) {
		(*function_pointers[option])();
	}
	
	CloseHandle(map_file_handle);
	
	return 0;
}

#include <iostream>
#include <limits>
#include <windows.h>

HANDLE file_handle, map_file_handle;
LPVOID map_view_addr;

int get_option() {
	std::cout << "\nEnter option:\n";
	std::cout << "1 - Create mapping file\n";
	std::cout << "2 - Map view of file\n";
	std::cout << "3 - Write data\n";
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

void create_file() {
	file_handle = CreateFile(
        "file.txt", 
        GENERIC_ALL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
        nullptr, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        nullptr
    );
    
    if (file_handle != INVALID_HANDLE_VALUE) {
		std::cout << "File created\n";
    } else {
    	std::cout << "Can not create such file\n";
    	return;
	}
	
	map_file_handle = CreateFileMapping(file_handle, nullptr, PAGE_READWRITE, 0, 1024, "mapping_file");

	if (map_file_handle != INVALID_HANDLE_VALUE) {
		std::cout << "Mapping file created\n";
    } else {
    	std::cout << "Can not create mapping file\n";
	}
}

void map_file() {
	map_view_addr = MapViewOfFile(map_file_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (map_view_addr == 0) {
        std::cout << "Can not map view of file\n";
	} else {
		std::cout << "View of file mapped\n";
	}
}

void write_data() {
	char data[1024];
	std::cout << "Enter data:\n";
	std::cin >> data;
	
	memcpy(map_view_addr, data, strlen(data));
	std::cout << "Written to map view address " << map_view_addr << "\n";
}

void unmap_file() {
	if(UnmapViewOfFile(map_view_addr)) {
		std::cout << "View of file unmapped\n";
	} else {
		std::cout << "Can not unmap view of file\n";
	}	
}

void (*function_pointers[5])() = {
	nullptr,
	create_file,
	map_file,
	write_data,
	unmap_file,
};

int main() {
	int option = 0;
	
	while ((option = get_option()) != 0) {
		(*function_pointers[option])();
	}
	
	CloseHandle(map_file_handle);
	CloseHandle(file_handle);
	
	return 0;
}

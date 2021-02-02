#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void print_information()
{
	std::cout << "1. If you want to DISPLAY the current directory press 1 \n"
		"2. If you want to DISPLAY DIRECTORY contens press 2 \n"
		"3. If you want to CREATE A DIRECTORY with a preliminary"
		"check for the existence of a directory of the same name press 3 \n"
		"4. If you want to DIPLAY the size of file press 4 \n"
		"5. If you want to COPY FILE press 5 \n"
		"6. If you want to DELETE FILE press 6 \n"
		"7. If you want to DELETE DIRECTORY with files press 7 \n"
		"8. If you want to MOVE THROUGH directories (up and down nesting) press 8 \n"
		"9. If you want to RENAME FILE or directory press 9 \n"
		"10. If you want to MOVE THROUGH files or directories press 10\n"
		"11. If you want to FINISH press 0\n"
		"Enter the command: ";
}

void current_path()
{
	std::cout << "=================================================\n";
	std::cout << "Current path is " << fs::current_path() << std::endl << std::endl;
	std::cout << "=================================================\n";
}

void print_directory()
{
	for (auto& i : fs::directory_iterator(fs::current_path()))
		std::cout << i.path().filename() << std::endl;
	std::cout << std::endl;
}

void create_directory(std::string& dir)
{
	if (fs::exists(fs::current_path() / dir))
	{
		std::cout << "=================================================\n";
		std::cout << "The folder with the same name is already have\n";
		std::cout << "=================================================\n";
	}
	else
	{
		fs::create_directory(dir);
		std::cout << "=================================================\n";
		std::cout << "The folder was created successfully.\n";
		std::cout << "=================================================\n";
	}
}

void file_size(std::string& file)
{
	if (fs::exists(fs::current_path() / file))
	{
		std::cout << "=================================================\n";
		std::cout << "The are " << fs::file_size(fs::current_path() / file) << " bytes.\n";
		std::cout << "=================================================\n";
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "The file with the same name didn'n find.\n";
		std::cout << "=================================================\n";
	}
}

void copy_file(std::string& from_file, std::string& to_file)
{
	if (fs::exists(fs::current_path() / from_file) && fs::exists(fs::current_path() / to_file))
	{
		fs::copy(fs::current_path() / from_file, fs::current_path() / to_file);
		std::cout << "=================================================\n";
		std::cout << "Copying was finished successfully.\n";
		std::cout << "=================================================\n";
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "Incorrect input.\n";
		std::cout << "=================================================\n";
	}
}

void delete_file(std::string& file)
{
	if (fs::exists(fs::current_path() / file))
	{
		fs::remove(fs::current_path() / file);
		std::cout << "=================================================\n";
		std::cout << "Deleting was finished succsessfully.\n";
		std::cout << "=================================================\n";
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "Incorrect input";
		std::cout << "=================================================\n";
	}
}

void delete_folder(std::string& file)
{
	if (fs::exists(fs::current_path() / file))
	{
		fs::remove_all(fs::current_path() / file);
		std::cout << "=================================================\n";
		std::cout << "Deleting was finished succsessfully.\n";
		std::cout << "=================================================\n";
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "Incorrect input\n";
		std::cout << "=================================================\n";
	}
}

void move_through(std::string& go_to_dir_name, int side)
{
	if (fs::exists(fs::current_path() / go_to_dir_name))
	{
		if (side == 1)
		{
			fs::current_path(go_to_dir_name);
			std::cout << "=================================================\n";
			std::cout << "This is " << fs::current_path() << std::endl;
			std::cout << "=================================================\n";
		}
		else if (side == 2)
		{
			fs::current_path(fs::current_path().remove_filename());
			std::cout << "=================================================\n";
			std::cout << fs::current_path() << std::endl;
			std::cout << "=================================================\n";
		}
		else
		{
			std::cout << "=================================================\n";
			std::cout << "Incorrect input.\n";
			std::cout << "=================================================\n";
		}
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "Incorrect input.\n";
		std::cout << "=================================================\n";
	}
}

void rename_file(std::string& from_file, std::string& to_file)
{
	if (fs::exists(fs::current_path() / from_file))
	{
		std::cout << "=================================================\n";
		fs::rename(fs::current_path() / from_file, fs::current_path() / to_file);
		std::cout << "Renaming was finished successfully.\n";
		std::cout << "=================================================\n";
	}
	else
		std::cout << "Incorrect input.\n";
}

void move_to(std::string& file_from, std::string& file_to)
{
	if (fs::exists(fs::current_path() / file_from) && fs::exists(fs::current_path() / file_to))
	{
		fs::rename(fs::current_path() / file_from, fs::current_path() / file_to / file_from); /*фактически перезаписываем адрес папки*/
		std::cout << "=================================================\n";
		std::cout << "File was added in folder successfully.\n";
		std::cout << "=================================================\n";
	}
	else
	{
		std::cout << "=================================================\n";
		std::cout << "Incorrect input.\n";
		std::cout << "=================================================\n";
	}
}

int main()
{
	unsigned int command;

	std::cout << "Hello! \n";
	do
	{
		print_information();

		std::cin >> command;

		/*вывод на экран текущего каталога*/
		if (command == 1)
			current_path();

		/*вывод на экран содержимого каталога*/
		else if (command == 2)
			print_directory();

		/*создание каталога (папки) с предварительной проверкой на существование одноимённого каталога*/
		else if (command == 3)
		{
			std::string dir;

			std::cout << "Enter the name of your directory: ";
			std::cin.ignore();
			std::getline(std::cin, dir);

			create_directory(dir);
		}

		/*вывод на экран размера файла*/
		else if (command == 4)
		{
			std::string file;

			std::cout << "Enter the name of file to see its size: ";
			std::cin.ignore();
			std::getline(std::cin, file);

			file_size(file);
		}

		/*копирование файла*/
		else if (command == 5)
		{
			std::string from_file;
			std::string to_file;

			std::cout << "Enter the name of file to copy its: ";
			std::cin.ignore();
			std::getline(std::cin, from_file);

			std::cout << "Enter where do you want to insert a copied file (file name): ";
			std::getline(std::cin, to_file);

			copy_file(from_file, to_file);
		}

		/*удаление файла*/
		else if (command == 6)
		{
			std::string file;

			std::cout << "Enter the file you want to delete: ";
			std::cin.ignore();
			std::getline(std::cin, file);

			delete_file(file);
		}

		/*удаление каталога с файлами*/
		else if (command == 7)
		{
			std::string file;

			std::cout << "Enter the file you want to delete: ";
			std::cin.ignore();
			std::getline(std::cin, file);

			delete_folder(file);
		}

		/*перемещение по каталогам (вверх и вниз по вложенности)*/
		else if (command == 8)
		{
			int move_command;
			std::string dir;

			std::cout << "Enter where do you want to go (1 - up, 2- down): ";
			std::cin >> move_command;
			std::cin.ignore();
			std::cout << "Enter the name of directory: ";
			std::getline(std::cin, dir);

			move_through(dir, move_command);
		}

		/*переименование файлов и каталогов*/
		else if (command == 9)
		{
			std::string from_file;
			std::string to_file;

			std::cout << "Enter the name of file you want to rename: ";
			std::cin.ignore();
			std::getline(std::cin, from_file);

			std::cout << "Enter the new name for file: ";
			std::getline(std::cin, to_file);

			rename_file(from_file, to_file);
		}

		/*перемещение файлов и каталогов*/
		else if (command == 10)
		{
			std::string file_from;
			std::string file_to;

			std::cout << "Enter the name of file you want to move to: ";
			std::cin.ignore();
			std::getline(std::cin, file_from);

			std::cout << "Enter the name of folder you want to move file: ";
			std::getline(std::cin, file_to);

			move_to(file_from, file_to);
		}

	} while (command != 0);
	std::cout << "Goodbye!";
	return 0;
}
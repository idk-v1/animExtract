#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
	std::string path;
	std::cout << "path to images: ";
	std::cin >> path;

	sf::IntRect rect;
	std::cout << "x y w h: ";
	std::cin >> rect.left >> rect.top >> rect.width >> rect.height;

	sf::Image temp, save;
	save.create(rect.width, rect.height, sf::Color::Black);

	fs::create_directory(path + "/crop");

	size_t count = 0;
	fs::directory_iterator cdir(path);
	for (fs::directory_entry e : cdir)
		if (!e.is_directory())
			count++;

	fs::directory_iterator dir(path);
	for (fs::directory_entry e : dir)
	{
		if (!e.is_directory())
		{
			if (temp.loadFromFile(e.path().string()))
			{
				save.copy(temp, 0, 0, rect);
				save.saveToFile(path + "/crop/" + e.path().filename().string());
				printf("Remaining: %7llu\n", --count);
			}
		}

	}

	return 0;
}
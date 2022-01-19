// Osman Zakir
// 1 / 19 / 2022
// Beginning C++20: From Novice to Professional by Ivor Horton and Peter Van Weert
// Chapter 11 Exercise 4
// Exercise Specs:
/**
 * Start again from the solution of Exercise 11-2 and move swap() and
 * max_word_length() into an internals module implementation partition.
 */

import <iostream>;
import <string>;
import words;

int main()
{
	using namespace std::string_literals;
	words::Words words;
	std::string text;
	const auto separators{ " ,.!?\"\n"s };

	std::cout << "Enter a string terminated by *:\n";
	std::getline(std::cin, text, '*');

	words::extract_words(words, text, separators);
	if (words.empty())
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}

	words::sort(words);
	words::show_words(words);
}
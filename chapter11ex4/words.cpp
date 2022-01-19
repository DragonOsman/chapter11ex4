module words;

import <iostream>;
import <format>;
import :internals;

void sort(words::Words& words, std::size_t start, std::size_t end);

void words::sort(words::Words& words)
{
	if (!words.empty())
	{
		::sort(words, 0, words.size() - 1);
	}
}

void sort(words::Words& words, std::size_t start, std::size_t end)
{
	// start index must be less than end index for 2 or more elements
	if (!(start < end))
	{
		return;
	}

	// Choose middle address to partition set
	// And swap middle address with start
	swap(words, start, (start + end) / 2);

	std::size_t current{ start };
	for (std::size_t i{ start + 1 }; i <= end; i++)
	{
		// Is word word less than chosen word?
		if (*words[i] < *words[start])
		{
			// Yes, so swap to the left
			swap(words, ++current, i);
		}
	}

	// Swap chosen and last swapped words
	swap(words, start, current);

	// Sort left subset if exists
	if (current > start)
	{
		sort(words, start, current - 1);
	}

	// Sort right subset if exists
	if (end > current + 1)
	{
		sort(words, current + 1, end);
	}
}

void words::extract_words(words::Words& words, const std::string& text, 
	const std::string& separators)
{
	std::size_t start{ text.find_first_not_of(separators) };

	while (start != std::string::npos)
	{
		std::size_t end = text.find_first_of(separators, start + 1);
		if (end == std::string::npos)
		{
			end = text.length();
		}
		words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
		start = text.find_first_not_of(separators, end + 1);
	}
}

void words::show_words(const words::Words& words)
{
	const std::size_t field_width{ max_word_length(words) + 1 };
	const std::size_t words_per_line{ 8 };
	std::cout << std::format("{:{}}", *words[0], field_width);

	std::size_t words_in_line{};
	for (std::size_t i{ 1 }; i < words.size(); ++i)
	{ // Output newline when initial letter changes or after 8 per line
		if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
		{
			words_in_line = 0;
			std::cout << std::endl;
		}
		std::cout << std::format("{:{}}", *words[i], field_width);
	}
	std::cout << std::endl;
}
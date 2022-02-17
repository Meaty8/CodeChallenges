#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <format>
#include <numeric>
#include <ranges>

static auto ParseFile_(auto infile)
{
	std::string name;
	std::vector<std::string> names;
	while (std::getline(infile, name, ','))
	{
		auto unquoted = name.substr(1, name.size() - 2);
		names.emplace_back(unquoted);
	}
	return names;
}


static auto Score_(const std::string& name)
{
	struct Score
	{
		void operator()(const wchar_t ch)
		{
			score += ch - 'A' + 1;
		}
		unsigned score = 0;
	};

	auto [it, scoreClass] = std::ranges::for_each(name.begin(), name.end(), Score());
	return scoreClass.score;
}

static auto IndexScore_(const unsigned score)
{
	static auto index = 0; //static so lives forever
	return ++index * score;
}

int main()
{
	_ASSERT(Score_("COLIN") == 53);
	auto names = ParseFile_(std::ifstream("p022_names.txt"));
	std::ranges::sort(names);
	auto scores = names | std::ranges::views::transform(Score_) | std::ranges::views::transform(IndexScore_);
	auto sum = std::accumulate(scores.begin(), scores.end(), 0u);
	std::cout << std::format("Total of all Name Scores {}\n", sum);
}

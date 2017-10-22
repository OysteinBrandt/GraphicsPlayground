#include <gtest/gtest.h>

#include "DebugTools/Profiler.h"
#include <fstream>

using debug::Profiler;

namespace
{
	const std::vector<std::string> categories{ "Category1", "Category2", "Category3" };
	const std::string profilerFileName = "profiling_result.csv";
	const size_t numFames = 5;
}

using namespace std::chrono_literals;

void writeSamples(Profiler &profiler)
{
	std::chrono::seconds sampleTime{ 0s };

	for (size_t frame = 0; frame < numFames; ++frame)
	{
		for (auto &c : categories)
			profiler.addEntry(c, sampleTime++);

		profiler.newFrame();
	}
}

std::string getNextToken(std::ifstream &file)
{
	char c;
	std::string ret;
	file >> std::noskipws;
	while (file >> c)
	{
		if (c == ',' || c == '\n')
			break;
		ret += c;
	}
	return ret;
}

void isAtEndOfFile(std::ifstream &input)
{
	EXPECT_TRUE(input.good());

	char bitBucket;
	input >> bitBucket;

	EXPECT_TRUE(input.eof());
	EXPECT_FALSE(input.good());
}

void checkSamples()
{
	std::ifstream input(profilerFileName);
	EXPECT_TRUE(input.is_open());
	EXPECT_TRUE(input.good());

	EXPECT_EQ("Category1", getNextToken(input));
	EXPECT_EQ("Category2", getNextToken(input));
	EXPECT_EQ("Category3", getNextToken(input));

	for (size_t i = 0; i < numFames * categories.size(); i++)
	{
		auto buf = getNextToken(input);
		EXPECT_EQ(i, std::atoi(buf.c_str()));
	}

	isAtEndOfFile(input);
}

TEST(Profiler, ExcludeIncompleteFrames)
{
	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler);
		profiler.addEntry(categories[0], 15s);
	}
	checkSamples();

	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler);
		profiler.addEntry(categories[0], 15s);
		profiler.addEntry(categories[1], 16s);
	}
	checkSamples();
}

TEST(Profiler, NewFrameBeforeAddEntry)
{
	Profiler profiler(profilerFileName);
	ASSERT_DEATH(profiler.newFrame(), "Assertion failed.*");
}

TEST(Profiler, SmallAmountOfSamplesNonCircular)
{
	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler);
	}
	checkSamples();
}

TEST(Profiler, LargeAmountOfSamplesNonCircular)
{
	GTEST_MESSAGE_("Not implemented", testing::TestPartResult::Type::kNonFatalFailure);
}

TEST(Profiler, BufferBoundaries)
{
	GTEST_MESSAGE_("Not implemented", testing::TestPartResult::Type::kNonFatalFailure);
}

TEST(Profiler, CirculatingOneBufferPlusSome)
{
	GTEST_MESSAGE_("Not implemented", testing::TestPartResult::Type::kNonFatalFailure);
}

TEST(Profiler, CirculatingMultipleBuffers)
{
	GTEST_MESSAGE_("Not implemented", testing::TestPartResult::Type::kNonFatalFailure);
}
#include <gtest/gtest.h>

#include "DebugTools/Profiler.h"
#include <fstream>

using debug::Profiler;

namespace
{
	const std::vector<std::string> categories{ "Category1", "Category2", "Category3" };
	const std::string profilerFileName = "profiling_result.csv";
}

using namespace std::chrono_literals;

void writeSamples(Profiler &profiler, int numFrames)
{
	std::chrono::seconds sampleTime{ 0s };

	for (int frame = 0; frame < numFrames; ++frame)
	{
		profiler.newFrame();

		for (auto &c : categories)
			profiler.addEntry(c, sampleTime++);
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

void verifyResult(int numFrames, bool excludeLastFrame = false)
{
	std::ifstream input(profilerFileName);
	EXPECT_TRUE(input.is_open());
	EXPECT_TRUE(input.good());

	EXPECT_EQ(categories.at(0), getNextToken(input));
	EXPECT_EQ(categories.at(1), getNextToken(input));
	EXPECT_EQ(categories.at(2), getNextToken(input));

	int profileNumber = 0;
	if (numFrames >= Profiler::MAX_FRAME_SAMPLES) // Exceeded one iteration
	{
		profileNumber = (numFrames - Profiler::MAX_FRAME_SAMPLES) * static_cast<int>(categories.size());
		numFrames = Profiler::MAX_FRAME_SAMPLES;
	}

	if (excludeLastFrame)
	{
		profileNumber += static_cast<int>(categories.size());
		numFrames--;
	}

	for (size_t i = 0; i < numFrames * categories.size(); i++)
	{
		auto buf = getNextToken(input);
		EXPECT_EQ(profileNumber++, std::atoi(buf.c_str()));
	}

	isAtEndOfFile(input);
}

void runTestOnFrames(int numFrames)
{
	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler, numFrames);
	}
	verifyResult(numFrames);
}

void writeIncompleteFrames(int numFrames)
{
	bool wrapped = numFrames >= Profiler::MAX_FRAME_SAMPLES;
	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler, numFrames);
		profiler.newFrame();
		profiler.addEntry(categories[0], 15s);
	}
	verifyResult(numFrames, wrapped);

	{
		Profiler profiler(profilerFileName);
		writeSamples(profiler, numFrames);
		profiler.newFrame();
		profiler.addEntry(categories[0], 15s);
		profiler.addEntry(categories[1], 16s);
	}
	verifyResult(numFrames, wrapped);
}

TEST(Profiler, ExcludeIncompleteFrames)
{
	EXPECT_TRUE(Profiler::MAX_FRAME_SAMPLES > 2);
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES - 2); // No wrap
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES); // Wrap
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES + 2); // Wrap
}

// TODO: Consider supporting newFrame() called both before and after addEntry() if possible
TEST(Profiler, AddEntryBeforeNewFrame)
{
	{
		Profiler profiler(profilerFileName);
		ASSERT_DEATH(profiler.addEntry(categories[0], 15s), "Assertion failed.*");
	}

	{
		const int frames{ 5 };
		Profiler profiler(profilerFileName);
		writeSamples(profiler, frames);
		ASSERT_DEATH(profiler.addEntry(categories[0], 15s), "Assertion failed.*");
	}
}

TEST(Profiler, SmallAmountOfFramesNonCircular)
{
	const int frames{ 5 };
	runTestOnFrames(frames);
}

TEST(Profiler, LargeAmountOfFramesNonCircular)
{
	const auto frames{ static_cast<int>(Profiler::MAX_FRAME_SAMPLES * .8) };
	runTestOnFrames(frames);
}

TEST(Profiler, BufferBoundaries)
{
	runTestOnFrames(Profiler::MAX_FRAME_SAMPLES - 1);

	runTestOnFrames(Profiler::MAX_FRAME_SAMPLES);
	runTestOnFrames(Profiler::MAX_FRAME_SAMPLES + 1);
	runTestOnFrames(Profiler::MAX_FRAME_SAMPLES + 2);
}

TEST(Profiler, CirculatingOneBufferPlusSome)
{
	const auto frames{ static_cast<int>(Profiler::MAX_FRAME_SAMPLES * 1.5) };
	runTestOnFrames(frames);
}

TEST(Profiler, CirculatingMultipleBuffers)
{
	const auto frames{ static_cast<int>(Profiler::MAX_FRAME_SAMPLES * 3) };
	runTestOnFrames(frames);
}

TEST(Profiler, AssertTests)
{
	GTEST_MESSAGE_("Not implemented tests!", testing::TestPartResult::Type::kNonFatalFailure);
}
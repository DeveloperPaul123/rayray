#include <raytracer/image/image.h>

#include <gtest/gtest.h>
#include <numeric>
#include "raytracer/image/image_io.h"

using namespace rayray;

TEST(ImageTests, TestIndexing)
{
	image<unsigned char> img(300, 200);
	ASSERT_EQ(img.size(), 60000 * 3);


	std::fill(img.begin(), img.end(), 0);
	long long sum = std::accumulate(img.begin(), img.end(), 0);

	ASSERT_EQ(sum, 0);

	std::fill(img.begin(), img.end(), 1);
	sum = std::accumulate(img.begin(), img.end(), long long());

	ASSERT_EQ(sum, 1 * img.size());

	img[0] = 255;
	img[3] = 255;
	img[6] = 255;

	auto pixel_1_r = img.at(0, 0, channel::red);
	auto pixel_2_r = img.at(0, 1, channel::red);
	auto pixel_3_r = img.at(0, 2, channel::red);

	ASSERT_EQ(pixel_1_r, 255);
	ASSERT_EQ(pixel_2_r, 255);
	ASSERT_EQ(pixel_3_r, 255);
}

TEST(ImageTests, TestCopy)
{
	const image<unsigned char> img(300, 200);

	std::fill(img.begin(), img.end(), 5);

	auto copy = img;

	ASSERT_EQ(copy.size(), img.size());

	ASSERT_EQ(copy[0], 5);
}


TEST(ImageTests, TestWriteImage)
{
	image<unsigned char> img(300, 200);
	std::fill(img.begin(), img.end(), 0);
	
	for(auto c = 10; c < 81; c++)
	{
		img.set(10, c, channel::red, 255);
	}

	EXPECT_NO_THROW(write_ppm_image(img, "test.ppm"));
}
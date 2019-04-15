#include <raytracer/core/nd_base.h>
#include <raytracer/core/point.h>

#include <gtest/gtest.h>
#include "raytracer/core/vector.h"

using namespace rayray;
using vec3 = vector<double, 3>;
using vec2 = vector<double, 2>;
TEST(NdBaseTests, TestConstruction)
{
	nd_base<double, 3> base = { 1.0, 2.0, 3.0 };

	nd_base<double, 3> empty;

	ASSERT_EQ(base.dimension(), 3);
	ASSERT_EQ(empty.dimension(), 3);

	ASSERT_DOUBLE_EQ(base[0], 1.0);
	ASSERT_DOUBLE_EQ(base[1], 2.0);
	ASSERT_DOUBLE_EQ(base[2], 3.0);

	ASSERT_DOUBLE_EQ(empty[0], 0.0);
	ASSERT_DOUBLE_EQ(empty[1], 0.0);
	ASSERT_DOUBLE_EQ(empty[2], 0.0);
}

TEST(NdBaseTests, TestSubtraction)
{
	nd_base<double, 3> first = { 1.0, 2.0, 3.0 };
	nd_base<double, 3> second = { 2.0, 3.0, 4.0 };

	auto result = second - first;
	ASSERT_DOUBLE_EQ(result[0], 1.0);
	ASSERT_DOUBLE_EQ(result[1], 1.0);
	ASSERT_DOUBLE_EQ(result[2], 1.0);
}

TEST(NdBaseTests, TestSubtractionPointVector)
{
	const point<double, 3> first = { 1.0, 2.0, 3.0 };
	const vector<double, 3> second = { 2.0, 3.0, 4.0 };
	using base = nd_base<double, 3>;

	auto result = second - first;
	auto result_2 = first - second; 

	ASSERT_DOUBLE_EQ(result[0], 1.0);
	ASSERT_DOUBLE_EQ(result[1], 1.0);
	ASSERT_DOUBLE_EQ(result[2], 1.0);

	ASSERT_DOUBLE_EQ(result_2[0], -1.0);
	ASSERT_DOUBLE_EQ(result_2[1], -1.0);
	ASSERT_DOUBLE_EQ(result_2[2], -1.0);
}

TEST(PointTests, TestConstruction)
{
	point<double> pt(2.0, 3.0);
	point<double> empty;

	ASSERT_EQ(pt.dimension(), 2);
	ASSERT_EQ(empty.dimension(), 2);

	ASSERT_DOUBLE_EQ(empty[0], 0.0);
	ASSERT_DOUBLE_EQ(empty[1], 0.0);
}

TEST(VectorTests, TestAddVectors)
{
	using vec3 = vector<double, 3>;
	using vec2 = vector<double, 2>;

	const vec3 first({ 1.0, 2.0, 3.0 });
	const vec3 second({ 2.0, 3.0, 4.0 });
	auto result = first + second;

	ASSERT_DOUBLE_EQ(result.x(), 3.0);
	ASSERT_DOUBLE_EQ(result.y(), 5.0);
	ASSERT_DOUBLE_EQ(result.z(), 7.0);

	const vec2 left({ 1.0, 2.0 });
	const vec2 right({ 2.0, 3.0 });
	auto result_2d = left + right;

	ASSERT_DOUBLE_EQ(result_2d.x(), 3.0);
	ASSERT_DOUBLE_EQ(result_2d.y(), 5.0);
}

TEST(VectorTests, TestSubtraction)
{
	const vec3 first = { 1.0, 2.0, 3.0 };
	const vec3 second = { 2.0, 3.0, 4.0 };
	auto result = second - first;

	ASSERT_DOUBLE_EQ(result[0], 1.0);
	ASSERT_DOUBLE_EQ(result[1], 1.0);
	ASSERT_DOUBLE_EQ(result[2], 1.0);
}

TEST(VectorTests, TestUnitVector)
{
	vector<double, 3> vec({ 1.0, 3.0, 2.0 });
	
	ASSERT_DOUBLE_EQ(vec.length_squared(), 14.0);
	ASSERT_DOUBLE_EQ(vec.length(), std::sqrt(vec.length_squared()));

	auto unit_vector = vec.to_unit_vector();

	ASSERT_DOUBLE_EQ(unit_vector.length(), 1.0);
}

TEST(VectorTests, TestPointConversion)
{
	vector<double, 3> data = { 1.0, 2.0, 3.0 };
	point<double, 3> point_data = data.to_point();

	for(auto i = 0; i < 3; i++)
	{
		ASSERT_DOUBLE_EQ(data[i], point_data[i]);
	}
}
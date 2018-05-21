#include <raytracer/core/nd_base.h>
#include <raytracer/core/point.h>

#include <gtest/gtest.h>

using namespace rayray;

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

TEST(PointTests, TestConstruction)
{
	point<double> pt(2.0, 3.0);
	point<double> empty;
}
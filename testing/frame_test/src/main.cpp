#include <HeartBeatRateTypes.h>
#include <gtest/gtest.h>

//#include <list>
//#include <vector>
//#include <map>
//#include <string>
//#include <boost/lambda/lambda.hpp>
//namespace bl = boost::lambda;

namespace HRM_Testing {

/*
 * Frame rect
 */
TEST(ImageTest, ImageRectEmpty) {

//    int i[] = {100, 3, 200, 4, 300, 9, 1000, 230, 3, 1, 900};
//    std::vector<int> l1(i, i + sizeof(i) / sizeof(i[0]));
//
//    std::vector<int>::iterator last = std::remove_if(l1.begin(), l1.end(), bl::_1 < 10);
//    std::for_each(l1.begin(), last, std::cout << bl::_1 << "\n");
//    std::cout << "===========" << std::endl;
//    std::for_each(l1.begin(), l1.end(), std::cout << bl::_1 << "\n");

    hrm::ImageRect ir1;

    EXPECT_FALSE(ir1);
    EXPECT_TRUE(!ir1);

    hrm::ImageRect ir2(10, 10);
    EXPECT_TRUE(ir2);
    EXPECT_FALSE(!ir2);
}
TEST(ImageTest, ImageRectArea) {
    hrm::ImageRect ir1(1, 1);
    EXPECT_EQ(1, ir1.area());

    hrm::ImageRect ir2(10, 10);
    EXPECT_EQ(100, ir2.area());

    hrm::ImageRect ir3(20, 20);
    EXPECT_EQ(400, ir3.area());

    hrm::ImageRect ir4(100, 100);
    EXPECT_EQ(10000, ir4.area());

    hrm::ImageRect ir5(200, 200);
    EXPECT_EQ(40000, ir5.area());

    hrm::ImageRect ir6(480, 640);
    EXPECT_EQ(307200, ir6.area());
}

TEST(ImageTest, ImageRectEqual) {
    hrm::ImageRect ir1(10, 20), ir2(10, 20);
    EXPECT_TRUE(ir1 == ir2);
    EXPECT_FALSE(ir1 != ir2);

    hrm::ImageRect ir3(100, 200), ir4(200, 100);
    EXPECT_FALSE(ir3 == ir4);
    EXPECT_TRUE(ir3 != ir4);
}

/*
 * Frame format
 */
TEST(ImageTest, ImageFormatEmpty) {
    hrm::ImageFormat if1;
    EXPECT_FALSE(if1);
    EXPECT_TRUE(!if1);

    hrm::ImageFormat if2(hrm::ImageRect(10, 10));
    EXPECT_TRUE(if2);
    EXPECT_FALSE(!if2);
}

TEST(ImageTest, ImageFormatSize) {
    hrm::ImageFormat if1;
    EXPECT_EQ(0, if1.size());

    hrm::ImageFormat if2(hrm::ImageRect(10, 10));
    EXPECT_EQ(100, if2.size());

    hrm::ImageFormat if3(hrm::ImageRect(10, 10), 16);
    EXPECT_EQ(200, if3.size());

    hrm::ImageFormat if4(hrm::ImageRect(100, 100));
    EXPECT_EQ(10000, if4.size());

    hrm::ImageFormat if5(hrm::ImageRect(100, 100), 24);
    EXPECT_EQ(30000, if5.size());

    hrm::ImageFormat if6(hrm::ImageRect(480, 640));
    EXPECT_EQ(307200, if6.size());

    hrm::ImageFormat if7(hrm::ImageRect(480, 640), 16);
    EXPECT_EQ(614400, if7.size());

    hrm::ImageFormat if8(hrm::ImageRect(480, 640), 24);
    EXPECT_EQ(921600, if8.size());

    hrm::ImageFormat if9(hrm::ImageRect(480, 640), 12);
    EXPECT_EQ(460800, if9.size());
}

TEST(ImageTest, ImageFormatEqual) {
    hrm::ImageFormat if1(hrm::ImageRect(100, 100)), if2(
            hrm::ImageRect(100, 100));
    EXPECT_TRUE(if1 == if2);
    EXPECT_FALSE(if1 != if2);

    hrm::ImageFormat if3(hrm::ImageRect(100, 100)), if4(
            hrm::ImageRect(100, 100), 2);
    EXPECT_FALSE(if3 == if4);
    EXPECT_TRUE(if3 != if4);

    hrm::ImageFormat if5, if6(hrm::ImageRect(100, 100));
    EXPECT_FALSE(if5 == if6);
    EXPECT_TRUE(if5 != if6);
}

/*
 * Image
 */
TEST(ImageTest, ImageEmpty) {
    hrm::Image i1;
    EXPECT_FALSE(i1);
    EXPECT_TRUE(!i1);

    uint8_t * data1 = i1.getData();
    EXPECT_TRUE(data1 == NULL);

    hrm::Image i2(hrm::ImageFormat(hrm::ImageRect(100, 100)));
    EXPECT_TRUE(i2);
    EXPECT_FALSE(!i2);

    uint8_t * data2 = i2.getData();
    EXPECT_TRUE(data2 != NULL);
}

TEST(ImageTest, ImageAssignment){
    hrm::Frame i1(hrm::ImageFormat(hrm::ImageRect(10, 10))), i2 = i1;
    EXPECT_TRUE(i1.getFormat() == i2.getFormat());
    EXPECT_TRUE(i1.getData() == i2.getData());

    uint8_t * data1 = i1.getData();
    for (int i = 0; i < i1.getFormat().size(); ++i, ++data1) {
        *data1 = i;
    }

    uint8_t * data2 = i1.getData(), *data3 = i2.getData();
    EXPECT_TRUE(
            data2[i1.getFormat().size() - 1]
                    == data3[i2.getFormat().size() - 1]);

    EXPECT_EQ(99, data2[i1.getFormat().size() - 1]);
    EXPECT_EQ(99, data3[i1.getFormat().size() - 1]);
}

}  // namespace HRM_Testing

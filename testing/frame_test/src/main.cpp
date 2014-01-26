#include <HeartBeatRateTypes.h>
#include <gtest/gtest.h>

namespace HRM_Testing {

/*
 * Frame rect
 */

TEST(FrameTest, FrameRectEmpty) {
    hrm::FrameRect fr1;

    EXPECT_FALSE(fr1);
    EXPECT_TRUE(!fr1);

    hrm::FrameRect fr2(10, 10);
    EXPECT_TRUE(fr2);
    EXPECT_FALSE(!fr2);
}
TEST(FrameTest, FrameRectArea) {
    hrm::FrameRect fr1(1, 1);
    EXPECT_EQ(1, fr1.area());

    hrm::FrameRect fr2(10, 10);
    EXPECT_EQ(100, fr2.area());

    hrm::FrameRect fr3(20, 20);
    EXPECT_EQ(400, fr3.area());

    hrm::FrameRect fr4(100, 100);
    EXPECT_EQ(10000, fr4.area());

    hrm::FrameRect fr5(200, 200);
    EXPECT_EQ(40000, fr5.area());

    hrm::FrameRect fr6(480, 640);
    EXPECT_EQ(307200, fr6.area());
}

TEST(FrameTest, FrameRectEqual) {
    hrm::FrameRect fr1(10, 20), fr2(10, 20);
    EXPECT_TRUE(fr1 == fr2);
    EXPECT_FALSE(fr1 != fr2);

    hrm::FrameRect fr3(100, 200), fr4(200, 100);
    EXPECT_FALSE(fr3 == fr4);
    EXPECT_TRUE(fr3 != fr4);
}

/*
 * Frame format
 */
TEST(FrameTest, FrameFormatEmpty) {
    hrm::FrameFormat ff1;
    EXPECT_FALSE(ff1);
    EXPECT_TRUE(!ff1);

    hrm::FrameFormat ff2(hrm::FrameRect(10, 10));
    EXPECT_TRUE(ff2);
    EXPECT_FALSE(!ff2);
}

TEST(FrameTest, FrameFormatSize) {
    hrm::FrameFormat ff1;
    EXPECT_EQ(0, ff1.size());

    hrm::FrameFormat ff2(hrm::FrameRect(10, 10));
    EXPECT_EQ(100, ff2.size());

    hrm::FrameFormat ff3(hrm::FrameRect(10, 10), 2);
    EXPECT_EQ(200, ff3.size());

    hrm::FrameFormat ff4(hrm::FrameRect(100, 100));
    EXPECT_EQ(10000, ff4.size());

    hrm::FrameFormat ff5(hrm::FrameRect(100, 100), 3);
    EXPECT_EQ(30000, ff5.size());

    hrm::FrameFormat ff6(hrm::FrameRect(480, 640));
    EXPECT_EQ(307200, ff6.size());

    hrm::FrameFormat ff7(hrm::FrameRect(480, 640), 2);
    EXPECT_EQ(307200 * 2, ff7.size());

    hrm::FrameFormat ff8(hrm::FrameRect(480, 640), 3);
    EXPECT_EQ(307200 * 3, ff8.size());
}

TEST(FrameTest, FrameFormatEqual) {
    hrm::FrameFormat ff1(hrm::FrameRect(100, 100)), ff2(
            hrm::FrameRect(100, 100));
    EXPECT_TRUE(ff1 == ff2);
    EXPECT_FALSE(ff1 != ff2);

    hrm::FrameFormat ff3(hrm::FrameRect(100, 100)), ff4(
            hrm::FrameRect(100, 100), 2);
    EXPECT_FALSE(ff3 == ff4);
    EXPECT_TRUE(ff3 != ff4);

    hrm::FrameFormat ff5, ff6(hrm::FrameRect(100, 100));
    EXPECT_FALSE(ff5 == ff6);
    EXPECT_TRUE(ff5 != ff6);
}

/*
 * Frame
 */
TEST(FrameTest, FrameEmpty) {
    hrm::Frame f1;
    EXPECT_FALSE(f1);
    EXPECT_TRUE(!f1);

    uint8_t * data1 = f1.getData();
    EXPECT_TRUE(data1 == NULL);

    hrm::Frame f2(hrm::FrameFormat(hrm::FrameRect(100, 100)));
    EXPECT_TRUE(f2);
    EXPECT_FALSE(!f2);

    uint8_t * data2 = f2.getData();
    EXPECT_TRUE(data2 != NULL);
}

TEST(FrameTest, FrameAssignment){
    hrm::Frame f1(hrm::FrameFormat(hrm::FrameRect(10, 10))), f2 = f1;
    EXPECT_TRUE(f1.getFrameFormat() == f2.getFrameFormat());
    EXPECT_TRUE(f1.getData() == f2.getData());

    uint8_t * data1 = f1.getData();
    for (int i = 0; i < f1.getFrameFormat().size(); ++i, ++data1) {
        *data1 = i;
    }

    uint8_t * data2 = f1.getData(), *data3 = f2.getData();
    EXPECT_TRUE(
            data2[f1.getFrameFormat().size() - 1]
                    == data3[f2.getFrameFormat().size() - 1]);

    EXPECT_EQ(99, data2[f1.getFrameFormat().size() - 1]);
    EXPECT_EQ(99, data3[f1.getFrameFormat().size() - 1]);
}

}  // namespace HRM_Testing

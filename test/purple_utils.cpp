#include <gtest/gtest.h>
#include "utils.h"
#include "widget/random_util.h"

class PurpleUtilsTest : public ::testing::Test{
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(PurpleUtilsTest, randomIntTest) {
    int min = 0;
    int max = 100;
    for(int i = 0 ; i< 100 ; i++){
        auto rndValue = purple::RndInt(min, max);
        // std::cout << "rndValue = " << rndValue << std::endl;
        EXPECT_GE(rndValue , min);
        EXPECT_LE(rndValue , max);
    }//end for i
}

TEST_F(PurpleUtilsTest, randomFloatTest) {
    float min = 0.0f;
    float max = 1.0f;
    for(int i = 0 ; i< 100 ; i++){
        auto rndValue = purple::RndFloat(min, max);
        // std::cout << "rndValue = " << rndValue << std::endl;
        EXPECT_GE(rndValue , min);
        EXPECT_LE(rndValue , max);
    }//end for i
}

TEST_F(PurpleUtilsTest, randomIntTest2) {
     int min = 0;
    int max = 100;
    for(int i = 0 ; i< 100 ; i++){
        auto rndValue = purple::RandomUtil::randomInt(min , max);
        // std::cout << "rndValue = " << rndValue << std::endl;
        EXPECT_GE(rndValue , min);
        EXPECT_LE(rndValue , max);
    }//end for i
}

TEST_F(PurpleUtilsTest, randomFloatTest2) {
    float min = 0.0f;
    float max = 1.0f;
    for(int i = 0 ; i< 100 ; i++){
        auto rndValue = purple::RandomUtil::randomFloat(min , max);
        // std::cout << "rndValue = " << rndValue << std::endl;
        EXPECT_GE(rndValue , min);
        EXPECT_LE(rndValue , max);
    }//end for i
}







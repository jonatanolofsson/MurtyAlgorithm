#include <gtest/gtest.h>
#include <typeinfo>
#include <Miller.h>
#include <eigen3/Eigen/Core>

class MillerTests : public ::testing::Test {
    protected:
        MurtyMiller<> miller;
        Eigen::Matrix<double, 10, 10> COST;

    public:
        MillerTests() {
            COST << 7, 51, 52, 87, 38, 60, 74, 66, 0, 20,
                    50, 12, 0, 64, 8, 53, 0, 46, 76, 42,
                    27, 77, 0, 18, 22, 48, 44, 13, 0, 57,
                    62, 0, 3, 8, 5, 6, 14, 0, 26, 39,
                    0, 97, 0, 5, 13, 0, 41, 31, 62, 48,
                    79, 68, 0, 0, 15, 12, 17, 47, 35, 43,
                    76, 99, 48, 27, 34, 0, 0, 0, 28, 0,
                    0, 20, 9, 27, 46, 15, 84, 19, 3, 24,
                    56, 10, 45, 39, 0, 93, 67, 79, 19, 38,
                    27, 0, 39, 53, 46, 24, 69, 46, 23, 1;
        }

        ~MillerTests() {
        }
};


TEST_F(MillerTests, SingleHypothesis) {
    auto res = MurtyMiller<>::getMBestAssignments(COST);
    Eigen::Matrix<int, 5, 10> correct;
    correct <<
        8, 6, 2, 7, 5, 3, 9, 0, 4, 1,
        8, 6, 2, 7, 5, 3, 9, 0, 4, 1,
        0, 9, 2, 6, 5, 3, 7, 8, 4, 1,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        9, 2, 8, 7, 5, 3, 6, 0, 4, 1;
    int i = 0;
    for(auto edges : res) {
        int j = 0;
        for(auto e : edges) {
            ASSERT_EQ(e.y, correct(i, j));
            ++j;
        }
        ++i;
    }
}

#include "gtest/gtest.h"
#include "StatsCalculator.hpp"
#include "Student.hpp"

TEST(StatsCalculatorTest, AverageAndCount) {
    std::vector<Student> students = {
        Student("Alice", 80),
        Student("Bob", 60),
        Student("Charlie", 100)
    };

    EXPECT_EQ(StatsCalculator::countStudents(students), 3);
    EXPECT_DOUBLE_EQ(StatsCalculator::calculateAverage(students), 80.0);
}

TEST(StatsCalculatorTest, MinMaxGrade) {
    std::vector<Student> students = {
        Student("Alice", 80),
        Student("Bob", 60),
        Student("Charlie", 100)
    };

    EXPECT_EQ(StatsCalculator::findMinGrade(students), 60);
    EXPECT_EQ(StatsCalculator::findMaxGrade(students), 100);
}

TEST(StatsCalculatorTest, GradeDistribution) {
    std::vector<Student> students = {
        Student("Alice", 5),
        Student("Bob", 15),
        Student("Charlie", 95)
    };

    auto dist = StatsCalculator::gradeDistribution(students);
    EXPECT_EQ(dist[0], 1); // grade 5
    EXPECT_EQ(dist[1], 1); // grade 15
    EXPECT_EQ(dist[9], 1); // grade 95
}

#include <gtest/gtest.h>
#include "Student.hpp"
#include "StudentManager.hpp"

TEST(StudentManagerTest, AddStudent) {
    StudentManager manager;
    manager.addStudent("Alice", 90);
    Student* s = manager.searchStudentByName("Alice");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->getGrade(), 90);
}

TEST(StudentManagerTest, DeleteStudent) {
    StudentManager manager;
    manager.addStudent("Bob", 80);
    EXPECT_TRUE(manager.deleteStudent("Bob"));
    EXPECT_EQ(manager.searchStudentByName("Bob"), nullptr);
}

TEST(StudentManagerTest, FilterByGrade) {
    StudentManager manager;
    manager.addStudent("Alice", 90);
    manager.addStudent("Bob", 70);
    auto filtered = manager.filterByGrade(75, 95);
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].getName(), "Alice");
}

TEST(StudentManagerTest, StatsAverage) {
    StudentManager manager;
    manager.addStudent("Alice", 90);
    manager.addStudent("Bob", 70);
    auto students = manager.getStudents();
    double avg = 0;
    for(auto& s : students) avg += s.getGrade();
    avg /= students.size();
    EXPECT_DOUBLE_EQ(avg, 80.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

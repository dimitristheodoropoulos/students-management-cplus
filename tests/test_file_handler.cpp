#include <gtest/gtest.h>
#include <fstream>
#include "Student.hpp"
#include "StudentManager.hpp"
#include "FileHandler.hpp"
#include "StatsCalculator.hpp"

// Temporary test file
const std::string TEST_FILE = "test_students.json";

// Clean up after tests
void cleanup() {
    std::remove(TEST_FILE.c_str());
}

// Test saving and loading students
TEST(FileHandlerTest, SaveAndLoad) {
    StudentManager manager;
    manager.addStudent(Student("Alice", 90));
    manager.addStudent(Student("Bob", 70));

    // Save to JSON
    FileHandler::saveToFile(TEST_FILE, manager);

    // Load into a new manager
    StudentManager loadedManager;
    FileHandler::loadFromFile(TEST_FILE, loadedManager);

    // Check count
    auto students = loadedManager.getStudents();
    ASSERT_EQ(students.size(), 2);

    // Check contents
    Student* alice = loadedManager.searchStudentByName("Alice");
    ASSERT_NE(alice, nullptr);
    EXPECT_EQ(alice->getGrade(), 90);

    Student* bob = loadedManager.searchStudentByName("Bob");
    ASSERT_NE(bob, nullptr);
    EXPECT_EQ(bob->getGrade(), 70);

    cleanup();
}

// Test statistics after load
TEST(FileHandlerTest, StatisticsAfterLoad) {
    StudentManager manager;
    manager.addStudent(Student("Alice", 80));
    manager.addStudent(Student("Bob", 60));
    manager.addStudent(Student("Charlie", 100));

    FileHandler::saveToFile(TEST_FILE, manager);

    StudentManager loadedManager;
    FileHandler::loadFromFile(TEST_FILE, loadedManager);

    auto students = loadedManager.getStudents();
    EXPECT_DOUBLE_EQ(StatsCalculator::calculateAverage(students), 80.0);
    EXPECT_EQ(StatsCalculator::findMinGrade(students), 60);
    EXPECT_EQ(StatsCalculator::findMaxGrade(students), 100);

    cleanup();
}

// Test editing student and saving
TEST(FileHandlerTest, EditAndSave) {
    StudentManager manager;
    manager.addStudent(Student("Alice", 90));

    Student* s = manager.searchStudentByName("Alice");
    ASSERT_NE(s, nullptr);
    s->setName("Alicia");
    s->setGrade(95);

    FileHandler::saveToFile(TEST_FILE, manager);

    StudentManager loadedManager;
    FileHandler::loadFromFile(TEST_FILE, loadedManager);

    Student* updated = loadedManager.searchStudentByName("Alicia");
    ASSERT_NE(updated, nullptr);
    EXPECT_EQ(updated->getGrade(), 95);

    cleanup();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

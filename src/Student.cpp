#include "Student.hpp"

std::atomic<int> Student::nextId{1};

Student::Student(const std::string& name_, int grade_)
    : id(nextId++), name(name_), grade(grade_) {}

Student::Student(int id_, const std::string& name_, int grade_)
    : id(id_), name(name_), grade(grade_) {
    if (id_ >= nextId) nextId = id_ + 1;
}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
int Student::getGrade() const { return grade; }

void Student::setName(const std::string& newName) { name = newName; }
void Student::setGrade(int newGrade) { grade = newGrade; }

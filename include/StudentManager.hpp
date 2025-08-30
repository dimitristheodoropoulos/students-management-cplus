#ifndef STUDENTMANAGER_HPP
#define STUDENTMANAGER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "Student.hpp"

class StudentManager {
private:
    std::vector<Student> students;
    std::unordered_map<int, Student*> idMap;
    std::unordered_map<std::string, Student*> nameMap;

    void rebuildMaps();

public:
    StudentManager() = default;

    void addStudent(const std::string& name, int grade);
    void addStudent(const Student& s);

    bool deleteStudent(const std::string& name);

    Student* searchStudentById(int id);
    Student* searchStudentByName(const std::string& name);

    void listStudents() const;
    void sortByName();
    void sortByGrade();
    std::vector<Student> filterByGrade(int minGrade, int maxGrade) const;
    std::vector<Student> getStudents() const;

    void clear();
};

#endif

#include "StudentManager.hpp"
#include <algorithm>
#include <iostream>

void StudentManager::addStudent(const std::string& name, int grade) {
    Student s(name, grade);
    students.push_back(s);
    rebuildMaps();
}

void StudentManager::addStudent(const Student& s) {
    students.push_back(s);
    rebuildMaps();
}

bool StudentManager::deleteStudent(const std::string& name) {
    auto it = std::remove_if(students.begin(), students.end(),
                             [&name](const Student& s){ return s.getName() == name; });
    if (it == students.end()) return false;
    students.erase(it, students.end());
    rebuildMaps();
    return true;
}

Student* StudentManager::searchStudentById(int id) {
    auto it = idMap.find(id);
    return it != idMap.end() ? it->second : nullptr;
}

Student* StudentManager::searchStudentByName(const std::string& name) {
    auto it = nameMap.find(name);
    return it != nameMap.end() ? it->second : nullptr;
}

void StudentManager::listStudents() const {
    for (const auto& s : students)
        std::cout << s.getId() << " : " << s.getName() << " : " << s.getGrade() << "\n";
}

void StudentManager::sortByName() {
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b){ return a.getName() < b.getName(); });
    rebuildMaps();
}

void StudentManager::sortByGrade() {
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b){ return a.getGrade() < b.getGrade(); });
    rebuildMaps();
}

std::vector<Student> StudentManager::filterByGrade(int minGrade, int maxGrade) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (s.getGrade() >= minGrade && s.getGrade() <= maxGrade)
            result.push_back(s);
    }
    return result;
}

std::vector<Student> StudentManager::getStudents() const { return students; }

void StudentManager::clear() {
    students.clear();
    idMap.clear();
    nameMap.clear();
}

void StudentManager::rebuildMaps() {
    idMap.clear(); nameMap.clear();
    for (auto& s : students) {
        idMap[s.getId()] = &s;
        nameMap[s.getName()] = &s;
    }
}

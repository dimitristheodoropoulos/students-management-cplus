#include "FileHandler.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void FileHandler::saveToFile(const std::string& filename, const StudentManager& manager) {
    json j;
    for (auto& s : manager.getStudents()) {
        j.push_back({{"id", s.getId()}, {"name", s.getName()}, {"grade", s.getGrade()}});
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

void FileHandler::loadFromFile(const std::string& filename, StudentManager& manager) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto& item : j) {
        Student s(item["id"], item["name"], item["grade"]);
        manager.addStudent(s);
    }
}

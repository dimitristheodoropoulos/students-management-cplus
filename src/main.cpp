#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>  // https://github.com/nlohmann/json
#include "Student.hpp"
#include "StudentManager.hpp"
#include "StatsCalculator.hpp"

using json = nlohmann::json;

// --- JSON Persistence ---
void saveToJSON(const std::string& filename, const std::vector<Student>& students) {
    json j;
    for (const auto& s : students) {
        j.push_back({{"id", s.getId()}, {"name", s.getName()}, {"grade", s.getGrade()}});
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

std::vector<Student> loadFromJSON(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file) return students;
    json j;
    file >> j;
    for (auto& item : j) {
        students.push_back(Student(item["id"], item["name"], item["grade"]));
    }
    return students;
}

// --- Main ---
int main(int argc, char* argv[]) {
    std::string dataFile = "students.json";
    if (argc > 1) dataFile = argv[1];

    StudentManager manager;
    for (auto& s : loadFromJSON(dataFile)) manager.addStudent(s);

    int option;
    while (true) {
        std::cout << "\n--- Menu ---\n"
                  << "1. Add Student\n2. View Students\n3. Delete Student\n"
                  << "4. Search Student by Name\n5. Search Student by ID\n"
                  << "6. Sort Students\n7. Save to JSON\n8. Load from JSON\n"
                  << "9. Edit Student\n10. View Statistics\n11. Search by Grade Range\n12. Exit\n"
                  << "Choice: ";
        std::cin >> option;

        switch(option) {
            case 1: {
                std::string name; int grade;
                std::cout << "Enter student's name: "; std::cin >> name;
                std::cout << "Enter student's grade: "; std::cin >> grade;
                manager.addStudent(name, grade);
                break;
            }
            case 2: manager.listStudents(); break;
            case 3: {
                std::string name; std::cout << "Enter name to delete: "; std::cin >> name;
                if(manager.deleteStudent(name)) std::cout << "Deleted successfully.\n";
                else std::cout << "Student not found.\n";
                break;
            }
            case 4: {
                std::string name; std::cout << "Enter name to search: "; std::cin >> name;
                Student* s = manager.searchStudentByName(name);
                if(s) std::cout << s->getId() << " : " << s->getName() << " : " << s->getGrade() << "\n";
                else std::cout << "Student not found.\n";
                break;
            }
            case 5: {
                int id; std::cout << "Enter ID to search: "; std::cin >> id;
                Student* s = manager.searchStudentById(id);
                if(s) std::cout << s->getId() << " : " << s->getName() << " : " << s->getGrade() << "\n";
                else std::cout << "Student not found.\n";
                break;
            }
            case 6: {
                int criteria; std::cout << "Sort by name(1) or grade(0): "; std::cin >> criteria;
                if(criteria==1) manager.sortByName(); else manager.sortByGrade();
                std::cout << "Sorted successfully.\n"; break;
            }
            case 7: saveToJSON(dataFile, manager.getStudents()); std::cout << "Saved successfully.\n"; break;
            case 8: {
                manager.clear();
                for(auto& s : loadFromJSON(dataFile)) manager.addStudent(s);
                std::cout << "Loaded successfully.\n"; break;
            }
            case 9: {
                int id; std::cout << "Enter ID to edit: "; std::cin >> id;
                Student* s = manager.searchStudentById(id);
                if(s) {
                    std::string newName; int newGrade;
                    std::cout << "New name: "; std::cin >> newName;
                    std::cout << "New grade: "; std::cin >> newGrade;
                    s->setName(newName); s->setGrade(newGrade);
                    std::cout << "Edited successfully.\n";
                } else std::cout << "Student not found.\n";
                break;
            }
            case 10: {
                auto students = manager.getStudents();
                std::cout << "--- Statistics ---\n";
                std::cout << "Number of students: " << StatsCalculator::countStudents(students) << "\n";
                std::cout << "Average grade: " << StatsCalculator::calculateAverage(students) << "\n";
                std::cout << "Min grade: " << StatsCalculator::findMinGrade(students) << "\n";
                std::cout << "Max grade: " << StatsCalculator::findMaxGrade(students) << "\n";
                auto dist = StatsCalculator::gradeDistribution(students);
                std::cout << "Grade distribution (0-100 by 10):\n";
                for(int i=0;i<10;++i) std::cout << i*10 << "-" << (i==9?100:i*10+9) << ": " << dist[i] << "\n";
                break;
            }
            case 11: {
                int minG,maxG; std::cout << "Enter grade range (min max): "; std::cin >> minG >> maxG;
                for(auto &s: manager.filterByGrade(minG,maxG))
                    std::cout << s.getId() << " : " << s.getName() << " : " << s.getGrade() << "\n";
                break;
            }
            case 12: saveToJSON(dataFile, manager.getStudents()); std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid option.\n";
        }
    }
    return 0;
}

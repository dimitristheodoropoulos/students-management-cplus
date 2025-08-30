#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <atomic>

class Student {
private:
    static std::atomic<int> nextId;
    int id;
    std::string name;
    int grade;

public:
    Student(const std::string& name, int grade);
    Student(int id, const std::string& name, int grade);

    int getId() const;
    std::string getName() const;
    int getGrade() const;

    void setName(const std::string& newName);
    void setGrade(int newGrade);
};

#endif

#ifndef STATSCALCULATOR_HPP
#define STATSCALCULATOR_HPP

#include <vector>
#include "Student.hpp"

class StatsCalculator {
public:
    static int countStudents(const std::vector<Student>& students);
    static double calculateAverage(const std::vector<Student>& students);
    static int findMinGrade(const std::vector<Student>& students);
    static int findMaxGrade(const std::vector<Student>& students);
    static std::vector<int> gradeDistribution(const std::vector<Student>& students);
};

#endif

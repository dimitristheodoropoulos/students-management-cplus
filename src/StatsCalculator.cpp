#include "StatsCalculator.hpp"
#include <algorithm>

int StatsCalculator::countStudents(const std::vector<Student>& students) {
    return students.size();
}

double StatsCalculator::calculateAverage(const std::vector<Student>& students) {
    if (students.empty()) return 0.0;
    double sum = 0;
    for (auto& s : students) sum += s.getGrade();
    return sum / students.size();
}

int StatsCalculator::findMinGrade(const std::vector<Student>& students) {
    if (students.empty()) return 0;
    int minVal = students[0].getGrade();
    for (auto& s : students) minVal = std::min(minVal, s.getGrade());
    return minVal;
}

int StatsCalculator::findMaxGrade(const std::vector<Student>& students) {
    if (students.empty()) return 0;
    int maxVal = students[0].getGrade();
    for (auto& s : students) maxVal = std::max(maxVal, s.getGrade());
    return maxVal;
}

std::vector<int> StatsCalculator::gradeDistribution(const std::vector<Student>& students) {
    std::vector<int> dist(10,0);
    for (auto& s : students) {
        int idx = std::min(s.getGrade()/10, 9);
        dist[idx]++;
    }
    return dist;
}

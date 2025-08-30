#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include "StudentManager.hpp"

class FileHandler {
public:
    static void saveToFile(const std::string& filename, const StudentManager& manager);
    static void loadFromFile(const std::string& filename, StudentManager& manager);
};

#endif

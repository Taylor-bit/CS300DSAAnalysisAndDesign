//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Taylor Colton
// Version     : 1.0
// Description : Project Two - Hash Table Implementation
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Define Course object
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Load, Read, Parse File, Check Format
std::unordered_map<std::string, Course> LoadCourses(const std::string& filePath) {
    // Declare HashTable<String, Course> courseTable
    std::unordered_map<std::string, Course> courseTable;

    // Open file containing Courses data
    std::ifstream file(filePath);

    // Handle file not opening
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return courseTable;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(ss, token, ',')) {
            // Handle empty strings as tokens
            if (token != "")
                tokens.push_back(token);
        }

        // Handle insufficient course data
        if (tokens.size() < 2) {
            std::cout << "Format error: each line must have at least a course number and title\n";
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (tokens[i].length() > 0)
                course.prerequisites.push_back(tokens[i]);
        }

        courseTable[course.courseNumber] = course;
    }

    std::cout << "Course data loaded.\n";
    return courseTable;
}

// Print a single course's information
void PrintCourseInfo(const std::string& courseNumber, const std::unordered_map<std::string, Course>& courseTable) {
    auto it = courseTable.find(courseNumber);
    if (it == courseTable.end()) {
        std::cout << "Course not found\n";
        return;
    }

    const Course& course = it->second;
    std::cout << course.courseNumber << ": " << course.courseTitle << "\n";

    // Handle empty prerequisites
    if (course.prerequisites.empty()) {
        std::cout << "Prerequisites: None\n";
    }
    else {
        // Add prerequisites
        std::cout << "Prerequisites:\n";
        for (const auto& prereq : course.prerequisites) {
            std::cout << "  " << prereq << "\n";
        }
    }
}

// Sort and print all courses
void SortAndPrintCourses(const std::unordered_map<std::string, Course>& courseTable) {
    std::vector<Course> sortedCourses;

    for (const auto& pair : courseTable) {
        sortedCourses.push_back(pair.second);
    }

    std::sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : sortedCourses) {
        std::cout << course.courseNumber << ", " << course.courseTitle << "\n";
    }
}

// Menu system
void DisplayMenu() {
    std::unordered_map<std::string, Course> courseTable;
    std::string userOption = "0";

    while (userOption != "9") {
        std::cout << "\n1. Load Data Structure\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> userOption;
        
        if (userOption == "1") {
        // Prompt user for filepath
            std::cout << std::endl << "Enter the filepath for the courses csv: ";
            std::cin >> userOption;
            courseTable = LoadCourses(userOption);
        }
        else if (userOption == "2") {
            SortAndPrintCourses(courseTable);
        }
        else if (userOption == "3") {
            // Prompt user for course number
            std::string courseNumber;
            std::cout << "Enter course number: ";
            std::cin >> courseNumber;
            PrintCourseInfo(courseNumber, courseTable);
        }
        else if (userOption == "9") {
            std::cout << "Goodbye!\n";
        }
        else {
            // Handle invalid user input
            std::cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    DisplayMenu();
    return 0;
}

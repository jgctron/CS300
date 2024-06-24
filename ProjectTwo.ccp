#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Course {
    std::string title;
    std::vector<std::string> prerequisites;
};

std::map<std::string, Course> loadCourseData(const std::string &filename) {
    std::map<std::string, Course> courses;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return courses;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseTitle, prerequisite;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.title = courseTitle;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses[courseNumber] = course;
    }

    file.close();
    return courses;
}

void displayMenu() {
    std::cout << "Welcome to the course planner." << std::endl;
    std::cout << "1. Load Data Structure." << std::endl;
    std::cout << "2. Print Course List." << std::endl;
    std::cout << "3. Print Course." << std::endl;
    std::cout << "9. Exit" << std::endl;
}

int getChoice() {
    int choice;
    std::cout << "What would you like to do? ";
    std::cin >> choice;
    return choice;
}

void printCourseList(const std::map<std::string, Course> &courses) {
    std::vector<std::string> courseNumbers;
    for (const auto &pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    std::sort(courseNumbers.begin(), courseNumbers.end());

    std::cout << "Here is a sample schedule:" << std::endl;
    for (const std::string &courseNumber : courseNumbers) {
        std::cout << courseNumber << ", " << courses.at(courseNumber).title << std::endl;
    }
}

void printCourse(const std::map<std::string, Course> &courses) {
    std::string courseNumber;
    std::cout << "What course do you want to know about? ";
    std::cin >> courseNumber;

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course &course = it->second;
        std::cout << courseNumber << ", " << course.title << std::endl;
        std::cout << "Prerequisites: ";
        for (const std::string &prerequisite : course.prerequisites) {
            std::cout << prerequisite << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Course not found." << std::endl;
    }
}

int main() {
    std::map<std::string, Course> courses;
    int choice;
    std::string filename;

    do {
        displayMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                std::cout << "Enter the file name: ";
                std::cin >> filename;
                courses = loadCourseData(filename);
                break;
            case 2:
                printCourseList(courses);
                break;
            case 3:
                printCourse(courses);
                break;
            case 9:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 9);

    return 0;
}

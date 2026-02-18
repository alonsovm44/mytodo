#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void initTodo();
void showTodo();
void addTodo(const std::string& task);
void doneTodo(int taskNum);

std::string VERSA_VERSION = "0.0.1";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: mytodo <command> [args]" << std::endl;
        std::cout << "commands: init, show, add, done" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {


        std::ofstream file("todo.txt", std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error: Could not create todo.txt" << std::endl;
            return 1;
        }
        file.close();
        std::cout << "Initialized empty todo list." << std::endl;


    } 
    else if (command == "show") {


        std::ifstream file("todo.txt");
        if (!file.is_open()) {
            std::cerr << "Error: Could not open todo.txt" << std::endl;
            return 1;
        }

        std::vector<std::string> tasks;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty())
                tasks.push_back(line);
        }
        file.close();

        if (tasks.empty()) {
            std::cout << "List is empty" << std::endl;
        } else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << (i + 1) << ". " << tasks[i] << std::endl;
            }
        }


    } 
    else if (command == "add") {
        if (argc < 3) { std::cout << "Error: Missing task name." << std::endl; return 1; }


        std::string task = argv[2];

        std::ifstream infile("todo.txt");
        if (!infile.is_open()) {
            std::cerr << "Error: Could not open todo.txt" << std::endl;
            return 1;
        }

        std::string line;
        bool exists = false;
        while (std::getline(infile, line)) {
            if (line == task) {
                exists = true;
                break;
            }
        }
        infile.close();

        if (exists) {
            std::cout << "Warning: Task already exists." << std::endl;
        } else {
            std::ofstream outfile("todo.txt", std::ios::app);
            if (!outfile.is_open()) {
                std::cerr << "Error: Could not write to todo.txt" << std::endl;
                return 1;
            }
            outfile << task << std::endl;
            outfile.close();
            std::cout << "Added task: " << task << std::endl;
        }


    } 
    else if (command == "done") {
        if (argc < 3) { std::cout << "Error: Missing task number." << std::endl; return 1; }


        int taskNum = std::stoi(argv[2]);

        std::ifstream infile("todo.txt");
        if (!infile.is_open()) {
            std::cerr << "Error: Could not open todo.txt" << std::endl;
            return 1;
        }

        std::vector<std::string> tasks;
        std::string line;
        while (std::getline(infile, line)) {
            if (!line.empty())
                tasks.push_back(line);
        }
        infile.close();

        if (taskNum < 1 || taskNum > (int)tasks.size()) {
            std::cerr << "Error: Invalid task number." << std::endl;
            return 1;
        }

        tasks.erase(tasks.begin() + (taskNum - 1));

        std::ofstream outfile("todo.txt", std::ios::out | std::ios::trunc);
        if (!outfile.is_open()) {
            std::cerr << "Error: Could not write to todo.txt" << std::endl;
            return 1;
        }

        for (const auto& t : tasks) {
            outfile << t << std::endl;
        }
        outfile.close();

        std::cout << "Marked task " << taskNum << " as done." << std::endl;


    } 
    else if (command == "-v" || command == "--version") {
        std::cout << "mytodo version " << VERSA_VERSION << std::endl;
    } else {
        std::cout << "Unknown command." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Helper function declarations
void initTodo();
void showTodo();
void addTodo(const std::string& task);
void doneTodo(int taskNum);
void setPriority(int taskNum, const std::string& priority);
void showPrioritySorted();

std::string VERSA_VERSION = "0.0.1";

std::vector<std::string> getTaskList() {
    std::vector<std::string> tasks;
    std::ifstream file("todo.txt");
    std::string line;
    while (std::getline(file, line)) {
        tasks.push_back(line);
    }
    file.close();
    return tasks;
}

void saveTaskList(const std::vector<std::string>& tasks) {
    std::ofstream file("todo.txt");
    for (const auto& task : tasks) {
        file << task << "\n";
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: mytodo <command> [args]" << std::endl;
        std::cout << "commands: init, show, add, done, pr, -v, --version" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        std::ofstream file("todo.txt");
        if (!file) {
            std::cerr << "Error: Could not create todo.txt" << std::endl;
            return 1;
        }
        file.close();
    } 
    else if (command == "show") {
        if (argc > 2 && argv[2] == std::string("pr")) {
            auto tasks = getTaskList();
            std::vector<std::pair<std::string, std::string>> prioritizedTasks;
            for (const auto& task : tasks) {
                size_t commaPos = task.find_last_of(',');
                if (commaPos != std::string::npos) {
                    std::string priority = task.substr(commaPos + 2);
                    prioritizedTasks.emplace_back(priority, task.substr(0, commaPos));
                } else {
                    prioritizedTasks.emplace_back("", task);
                }
            }
            std::sort(prioritizedTasks.begin(), prioritizedTasks.end(), [](const auto& a, const auto& b) {
                if (a.first == "") return false;
                if (b.first == "") return true;
                // Sort order: T (top), H (high), M (medium), L (low)
                return a.first > b.first;
            });
            int count = 1;
            for (const auto& task : prioritizedTasks) {
                std::cout << count << ". " << task.second << "\n";
                count++;
            }
        } else {
            auto tasks = getTaskList();
            if (tasks.empty()) {
                std::cout << "List is empty" << std::endl;
            } else {
                int count = 1;
                for (const auto& task : tasks) {
                    std::cout << count << ". " << task << "\n";
                    count++;
                }
            }
        }
    } 
    else if (command == "add") {
        if (argc < 3) { std::cout << "Error: Missing task name." << std::endl; return 1; }
        std::string task = argv[2];
        auto tasks = getTaskList();
        for (const auto& existingTask : tasks) {
            if (existingTask == task) {
                std::cout << "Warning: Task already exists." << std::endl;
                return 1;
            }
        }
        tasks.push_back(task);
        saveTaskList(tasks);
    } 
    else if (command == "pr") {
        if (argc < 4) { std::cout << "Error: Missing task number or priority." << std::endl; return 1; }
        int taskNum = std::stoi(argv[2]) - 1;
        std::string priority = argv[3];
        auto tasks = getTaskList();
        if (taskNum < 0 || taskNum >= tasks.size()) {
            std::cout << "Error: Invalid task number." << std::endl;
            return 1;
        }
        std::string priorityTag;
        if (priority == "low") priorityTag = ", L";
        else if (priority == "medium") priorityTag = ", M";
        else if (priority == "high") priorityTag = ", H";
        else if (priority == "top") priorityTag = ", T";
        else {
            std::cout << "Error: Invalid priority level." << std::endl;
            return 1;
        }
        tasks[taskNum] += priorityTag;
        saveTaskList(tasks);
    }
    else if (command == "done") {
        if (argc < 3) { std::cout << "Error: Missing task number." << std::endl; return 1; }
        int taskNum = std::stoi(argv[2]) - 1;
        auto tasks = getTaskList();
        if (taskNum < 0 || taskNum >= tasks.size()) {
            std::cout << "Error: Invalid task number." << std::endl;
            return 1;
        }
        tasks.erase(tasks.begin() + taskNum);
        saveTaskList(tasks);
    } 
    else if (command == "-v" || command == "--version") {
        std::cout << "mytodo version " << VERSA_VERSION << std::endl;
    } else {
        std::cout << "Unknown command." << std::endl;
    }

    return 0;
}

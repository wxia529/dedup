#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

void deduplicateStream(std::istream& in, std::ostream& out, bool infoMode) {
    std::unordered_map<std::string, int> lineCount;
    std::vector<std::string> order;
    std::string line;

    while (std::getline(in, line)) {

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        auto [it, inserted] = lineCount.try_emplace(line, 0);
        if (inserted) {
            order.push_back(line);
        }
        it->second++;
    }

    if (!infoMode) {

        for (const auto& s : order) {
            out << s << '\n';
        }
    } else {

        out << "Repeated lines info:\n\n";
        for (const auto& s : order) {
            if (lineCount[s] > 1) {
                out << "Count: " << lineCount[s]
                    << " | Line: " << s << '\n';
            }
        }
    }
}

int main(int argc, char* argv[]) {
    bool infoMode = false;
    std::vector<std::string> files;


    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-i" || arg == "--info") {
            infoMode = true;
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: dedup [OPTION]... [FILE]\n"
                      << "Options:\n"
                      << "  -i, --info   Output repeated lines information.\n";
            return 0;
        } else if (arg[0] != '-') {
            files.push_back(arg);
        } else {
            std::cerr << "dedup: invalid option -- '" << arg << "'\n"
                      << "Try 'dedup --help' for more information.\n";
            return 1;
        }
    }


    if (files.empty()) {
        std::cerr << "dedup: no file\n";
        return 1;
    }

    std::string filename = files[0];

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file: " << filename << '\n';
        return 1;
    }

    deduplicateStream(file, std::cout, infoMode);

    return 0;
}



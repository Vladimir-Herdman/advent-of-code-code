#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define ULLI unsigned long long int
using namespace std;

bool check_id(vector<string>& ranges, ULLI id) {
    for (string& line : ranges) {
        int dash = line.find('-');
        ULLI l = stoull(line.substr(0, dash));
        ULLI r = stoull(line.substr(dash+1));
        if (id >= l && id <= r) {return true;}
    }
    return false;
}

int main() {
    vector <string> ranges{}; ranges.reserve(100);
    vector <ULLI> ids; ids.reserve(100);
    ULLI count{};

    ifstream f("./day5-input.txt");
    bool range{true};
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            if (range) {
                if (line.empty()) {range = false; continue;}
                ranges.emplace_back(line);
            } else {
                if (check_id(ranges, stoull(line))) {++count;}
            }
        }

        f.close();
    }

    cout << "The number of all fresh id's is: " << count << '\n';
    return 0;
}

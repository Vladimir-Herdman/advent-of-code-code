#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define ULLI unsigned long long int
using namespace std;

struct Pair {
    ULLI l;
    ULLI r;
};

bool check_ranges(vector<Pair>& ranges, Pair& pair) {
    //go through each range pair, and look for overlap between ranges and new pair, and adjust accordingly
    for (Pair& range : ranges) {
        if (range.l <= pair.l && range.r >= pair.r) { //range fully contains pair ( ||| )
            return false;
        } else if (range.l >= pair.l && range.r <= pair.r) { //pair contains range ||(|||)||
            Pair new_pair{range.r+1, pair.r};
            pair.r = range.l-1;
            if (check_ranges(ranges, new_pair)) {
                ranges.emplace_back(new_pair);
            }
        } else if (range.r >= pair.l && range.r < pair.r) { //pair inside, but farther right (  ||)|||
            pair.l = range.r+1;
        } else if (range.l > pair.l && range.l <= pair.r) { //pair inside, but farther left |||(||  )
            pair.r = range.l-1;
        }
    }
    return true;
}

int main() {
    vector <Pair> ranges{}; ranges.reserve(100);
    vector <ULLI> ids; ids.reserve(100);
    ULLI count{};

    ifstream f("./day5-input.txt");
    bool range{true};
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            if (range) {
                if (line.empty()) {range = false; continue;}
                int dash = line.find('-');
                Pair pair{stoull(line.substr(0, dash)), stoull(line.substr(dash+1))};
                if (check_ranges(ranges, pair)) {
                    ranges.emplace_back(pair);
                }
            } else {break;} //break on empty line found, go to next section
        }

        f.close();
    }

    for (Pair p : ranges) {
        count += p.r - p.l + 1;
    }

    cout << "The number of all fresh id's is: " << count << '\n';
    return 0;
}

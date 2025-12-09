#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#define CONNECTIONS 1000 //change this for how many connections to make between junction boxes
#define MULTIPLY 3 //change this for how many connection sizes to multiply
using namespace std;
using u64 = uint64_t;

struct Point {
    u64 x, y, z, count{1};
    Point* source{nullptr};

    bool operator<(const Point& other) const {return count < other.count;}

    Point(const unsigned int x, const unsigned int y, const unsigned int z): x(x), y(y), z(z) {}
    void print() const {cout<<"x:"<<x<<", y:"<<y<<", z:"<<z<<", count:"<<count;}
};
struct Connection {
    Point* p1;
    Point* p2;
    u64 distance;

    bool operator<(const Connection& other) const {return distance < other.distance;}
};

u64 get_largest_three_multiple(vector<Point>& points) {
    u64 sum{1};
    for (int i=0; i<MULTIPLY; i++) {
        sum *= points.at(i).count;
    }
    return sum;
}

//does not squeare root to save time and not deal with fractional math
u64 euclidean_distance(Point p1, Point p2) {
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z);
}

int main() {
    ifstream f("./day8-input.txt");
    if (!f.is_open()) {return 1;}

    vector<Point> points{}; points.reserve(CONNECTIONS*5);
    string line;
    while (getline(f, line)) {
        const int cone = line.find(",");
        const int ctwo = line.find(",", cone+1);
        const unsigned int x = static_cast<unsigned int>(stoi(line.substr(0, cone)));
        const unsigned int y = static_cast<unsigned int>(stoi(line.substr(cone+1, ctwo-cone-1)));
        const unsigned int z = static_cast<unsigned int>(stoi(line.substr(ctwo+1)));
        points.emplace_back(Point(x, y, z));
    } f.close();
    if (points.empty()) {return 1;}

    vector<Connection> distances{}; distances.reserve(CONNECTIONS*5);
    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            distances.emplace_back((Connection){&points.at(i), &points.at(j), euclidean_distance(points.at(i), points.at(j))});
        }
    }

    sort(distances.begin(), distances.end());
    for (int i=0; i<CONNECTIONS; i++) {
        const Connection& c = distances.at(i);
        Point* l = c.p1;
        Point* r = c.p2;
        if (l == nullptr && r == nullptr) {
            r->source = l;
            l->count += r->count;
        } else if (l == nullptr && r != nullptr) {
            while (r->source != nullptr) {r = r->source;}
            if (r != l) {r->source = l; l->count += r->count; r->count = 1;}
        } else if (l != nullptr && r == nullptr) {
            while (l->source != nullptr) {l = l->source;}
            if (l != r) {l->source = r; r->count += l->count; l->count = 1;}
        } else { //l != nullptr && r != nullptr
            while (r->source != nullptr) {r = r->source;}
            while (l->source != nullptr) {l = l->source;}
            if (l != r) {r->source = l; l->count += r->count; r->count = 1;}
        }
    }

    sort(points.rbegin(), points.rend());
    cout << "After " << CONNECTIONS << " connections, this is the result of multiplying the size of the top "<<MULTIPLY<<":\n";
    cout << get_largest_three_multiple(points) << '\n';
    return 0;
}

#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

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

//does not squeare root to save time and not deal with fractional math
u64 euclidean_distance(Point p1, Point p2) {
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z);
}

bool check_all_connected(vector<Point>& points) {
    Point* first{nullptr};
    for (Point& p : points) {
        if (first == nullptr && p.source == nullptr) {first=&p; continue;}
        else if (p.source == nullptr && first != &p) {return false;}
    }
    return true;
}

int main() {
    ifstream f("./day8-input.txt");
    if (!f.is_open()) {return 1;}

    vector<Point> points{}; points.reserve(1000);
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

    vector<Connection> distances{}; distances.reserve(1000*5);
    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            distances.emplace_back((Connection){&points.at(i), &points.at(j), euclidean_distance(points.at(i), points.at(j))});
        }
    }

    sort(distances.begin(), distances.end());
    u64 count{0};
    Point* p1;
    Point* p2;
    while (!check_all_connected(points)) {
        const Connection& c = distances.at(count);
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

        ++count;
        //if (count >= distances.size()) {count = 0;} //I don't believe this happens, it's correctly set all
        p1 = c.p1; //last'll be set at end of loop
        p2 = c.p2;
        //c.p1->print();cout<<" ;; ";c.p2->print();cout<<" ;; distance:"<<c.distance<<'\n';
    }
    cout<<"Final points here: "; p1->print(); cout<<" ;; "; p2->print(); cout<<'\n';
    cout<<"x's multiplied: "<<p1->x*p2->x; cout<<'\n';
    return 0;

    sort(points.rbegin(), points.rend());
    for (const Point& p : points) {
        cout<<"point: ";p.print();cout<<'\n';
    }

    //cout << "After " << CONNECTIONS << " connections, this is the result of multiplying the size of the top "<<MULTIPLY<<":\n";
    //cout << get_largest_three_multiple(points) << '\n';
    return 0;
}

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;
using u64 = uint64_t;

struct Point {
    int x, y, count{1};
    Point* source{nullptr};

    bool operator<(const Point& other) const {return count < other.count;}

    Point(const unsigned int x, const unsigned int y): x(x), y(y) {}
    void print() const {cout<<"x:"<<x<<", y:"<<y;}
};
struct Square {
    Point* p1; //corner 1
    Point* p2; //opposite corner 2
    u64 area;

    bool operator<(const Square& other) const {return area < other.area;}
};

u64 area_calc(const Point& p1, const Point& p2) {
    u64 dx = static_cast<u64>(abs(p1.x-p2.x)) + 1ULL;
    u64 dy = static_cast<u64>(abs(p1.y-p2.y)) + 1ULL;
    return dx*dy;
}

template <typename T>
void printt(const T& container, const string before="", const string after="") {
    for (const auto& c : container) {
        cout<<before; c.print(); cout<<after; cout<<'\n';
    }
}

int main() {
    ifstream f("./day9-input.txt");
    if (!f.is_open()) {return 1;}

    vector<Point> points{}; points.reserve(1000);
    string line;
    while (getline(f, line)) {
        const int comma = line.find(",");
        const unsigned int x = static_cast<unsigned int>(stoi(line.substr(0, comma)));
        const unsigned int y = static_cast<unsigned int>(stoi(line.substr(comma+1)));
        points.emplace_back(Point(x, y));
    } f.close();
    if (points.empty()) {return 1;}
    //for (const Point& p : points) {
    //    p.print();cout<<'\n';
    //}
    //printt(points, "points - ");

    vector<Square> squares{}; squares.reserve(1000);
    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            Point* p1 = &points.at(i);
            Point* p2 = &points.at(j);
            squares.emplace_back((Square){p1, p2, area_calc(*p1, *p2)});
        }
    }
    //for (const Square& p : squares) {
    //    p.p1->print();cout<<" ;; ";p.p2->print();cout<<" ;; Area:"<<p.area<<'\n';
    //}

    //sort(squares.begin(), squares.end());
    //for (const Square& p : squares) {
    //    p.p1->print();cout<<" ;; ";p.p2->print();cout<<" ;; Area:"<<p.area<<'\n';
    //}
    auto max_area = max_element(squares.begin(), squares.end(),
        [](const Square& a, const Square& b){
            return a.area < b.area;
        });

    cout << "Max area: " << (*max_area).area << '\n';
    return 0;
    //for (int i=0; i<CONNECTIONS; i++) {
    //    const Square& c = squares.at(i);
    //    Point* l = c.p1;
    //    Point* r = c.p2;
    //    if (l == nullptr && r == nullptr) {
    //        r->source = l;
    //        l->count += r->count;
    //    } else if (l == nullptr && r != nullptr) {
    //        while (r->source != nullptr) {r = r->source;}
    //        if (r != l) {r->source = l; l->count += r->count; r->count = 1;}
    //    } else if (l != nullptr && r == nullptr) {
    //        while (l->source != nullptr) {l = l->source;}
    //        if (l != r) {l->source = r; r->count += l->count; l->count = 1;}
    //    } else { //l != nullptr && r != nullptr
    //        while (r->source != nullptr) {r = r->source;}
    //        while (l->source != nullptr) {l = l->source;}
    //        if (l != r) {r->source = l; l->count += r->count; r->count = 1;}
    //    }
    //}

    //sort(points.rbegin(), points.rend());
    //cout << "After " << CONNECTIONS << " connections, this is the result of multiplying the size of the top "<<MULTIPLY<<":\n";
    //cout << get_largest_three_multiple(points) << '\n';
    return 0;
}

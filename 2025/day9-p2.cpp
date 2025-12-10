#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
using u64 = uint64_t;

struct Point {
    int x, y;

    Point(): x(-1), y(-1) {}
    Point(const int x, const int y): x(x), y(y) {}
    void print() const {cout<<"x:"<<x<<", y:"<<y;}
};
struct Square {
    Point p1;
    Point p2;
    u64 area;

    bool operator<(const Square& other) const {return area < other.area;}

    Square(const Point tl, const Point br, const u64 area): p1(tl), p2(br), area(area) {}
    void print() const {p1.print();cout<<" ;; ";p2.print();cout<<" ;; Area:"<<area;}
};

template <typename T>
void printt(const T& container, const string before="", const string after="") {
    for (const auto& c : container) {
        cout<<before; c.print(); cout<<after; cout<<'\n';
    }
}

void fill_floor(vector<vector<int>>& floor, vector<Point>& points) {
    Point p1{-1, -1};
    char direction;
    u64 length;
    points.emplace_back(points.at(0));
    for (const Point& p : points) {
        if (p1.x == -1) {p1 = p; continue;}

        if (p1.x != p.x) {
            direction = (p1.x - p.x < 0 ? 'r' : 'l');
            length = static_cast<u64>(abs(p1.x-p.x)) + 1ULL;
        } else {
            direction = (p1.y - p.y < 0 ? 'd' : 'u');
            length = static_cast<u64>(abs(p1.y-p.y)) + 1ULL;
        }
        for (int i=0; i<length; i++) {
            //cout << "p1.x:"<<p1.x<<", p1.y:"<<p1.y<<", direction:"<<direction<<'\n';
            switch (direction) {
                case 'u': floor[p1.y-i][p1.x] = 1; break;
                case 'd': floor[p1.y+i][p1.x] = 1; break;
                case 'l': floor[p1.y][p1.x-i] = 1; break;
                case 'r': floor[p1.y][p1.x+i] = 1; break;
            }
        }
        p1 = p;
    }
    points.pop_back();
}

void flood_fill(vector<vector<int>>& arr, const int maxy, const int maxx) {
    queue<Point> q;
    q.emplace(maxx*0.5,maxy*0.4);
    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (arr[p.y][p.x] == 0) {
            arr[p.y][p.x] = 1;
            q.emplace(p.x+1, p.y);
            q.emplace(p.x-1, p.y);
            q.emplace(p.x, p.y+1);
            q.emplace(p.x, p.y-1);
        }
    }
}

u64 area_calc(const Point& p1, const Point& p2) {
    const u64 dx = static_cast<u64>(abs(p1.x-p2.x)) + 1ULL;
    const u64 dy = static_cast<u64>(abs(p1.y-p2.y)) + 1ULL;
    return dx*dy;
}

void fill_map(unordered_map<int,int>& map, vector<Point>& points) {
    vector<int> vals; vals.reserve(points.size()*2);
    for (const Point& p : points) {
        vals.emplace_back(p.x);
        vals.emplace_back(p.y);
    } sort(vals.begin(), vals.end());
    int count{0};
    for (const int v : vals) {
        if (!map.contains(v)) {
            map.insert({v, count});
            ++count;
        }
    }
}

bool check_lines_for_zero(const vector<vector<int>>& arr, const Point p1, const Point p2) {
    //check horizontals
    if (p1.x - p2.x <= 0) { //p2 farther right
        for (int i=p1.x; i<=p2.x; i++) {if (arr[p1.y][i] == 0) {return true;}}
        for (int i=p1.x; i<=p2.x; i++) {if (arr[p2.y][i] == 0) {return true;}}
    } else {
        for (int i=p1.x; i>=p2.x; i--) {if (arr[p1.y][i] == 0) {return true;}}
        for (int i=p1.x; i>=p2.x; i--) {if (arr[p2.y][i] == 0) {return true;}}
    }

    //check verticals
    if (p1.y - p2.y <= 0) { //p2 farther down
        for (int i=p1.y; i<=p2.y; i++) {if (arr[i][p1.x] == 0) {return true;}}
        for (int i=p1.y; i<=p2.y; i++) {if (arr[i][p2.x] == 0) {return true;}}
    } else {
        for (int i=p1.y; i>=p2.y; i--) {if (arr[i][p1.x] == 0) {return true;}}
        for (int i=p1.y; i>=p2.y; i--) {if (arr[i][p2.x] == 0) {return true;}}
    }

    return false;
}

int main() {
    ifstream f("./day9-input.txt");
    if (!f.is_open()) {return 1;}

    //Get list of points
    vector<Point> points{}; points.reserve(1000);
    string line;
    while (getline(f, line)) {
        const int comma = line.find(",");
        const unsigned int x = static_cast<unsigned int>(stoi(line.substr(0, comma)));
        const unsigned int y = static_cast<unsigned int>(stoi(line.substr(comma+1)));
        points.emplace_back(x, y);
    } f.close();
    if (points.empty()) {return 1;}

    //Compress coordinates
    unordered_map<int,int> map;
    fill_map(map, points);
    vector<Point> points_compressed; points_compressed.reserve(map.size());
    int maxx{0},maxy{0};
    for (Point& p : points) {
        maxx = max(maxx, map.at(p.x));
        maxy = max(maxy, map.at(p.y));
        points_compressed.emplace_back(map.at(p.x), map.at(p.y));
    }

    //Generate compressed points vector representation of red and green
    vector<vector<int>> arr; arr.resize(maxy + 1); for(vector<int>& v : arr) {v.resize(maxx + 1);}
    fill_floor(arr, points_compressed);
    flood_fill(arr, maxy, maxx);
    points_compressed.clear();

    //Generate all possible squares from points (original uncompressed for area comparisons)
    vector<Square> squares{}; squares.reserve(points.size()*2);
    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            Point p1 = points.at(i);
            Point p2 = points.at(j);
            squares.emplace_back(p1, p2, area_calc(p1, p2));
        }
    } sort(squares.rbegin(), squares.rend(), [](const Square& a, const Square& b) {return a < b;});
    points.clear();

    //Now, start from largest area square, compress to fit in smaller arr, and
    //check if it's out of bounds. Return first that is contained.
    Square* largest_square;
    for (Square& sq : squares) {
        Point c1{map.at(sq.p1.x), map.at(sq.p1.y)}, c2{map.at(sq.p2.x), map.at(sq.p2.y)};
        if (check_lines_for_zero(arr, c1, c2)) {continue;}
        largest_square = &sq; break;
    }

    largest_square->print();cout<<'\n';
    //Point ptest1{map.at(largest_square->p1.x), map.at(largest_square->p1.y)};
    //Point ptest2{map.at(largest_square->p2.x), map.at(largest_square->p2.y)};
    //ptest1.print();cout<<'\n';
    //ptest2.print();cout<<'\n';
    //cout<<";;;;;;\n";
    //printt(points_compressed);
    //cout<<"area: "<<area_calc(ptest1, ptest2);
    //printt(squares);
    return 0;
}

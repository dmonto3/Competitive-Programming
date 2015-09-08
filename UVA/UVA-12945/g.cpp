using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <bitset>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r;}

#define D(x) //cout << #x " = " << (x) << endl;
using namespace std;

struct point {
  int x, y, w;
  point () {}
  point(int _x, int _y, int _w) : x(_x), y(_y), w(_w) {}  
};

point pivot(0, 0, 0);
vector <point> poly;

inline int distsqr(const point &a, const point &b) {
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);  
}

inline double dist(const point &a, const point &b) {
  return sqrt(distsqr(a, b));  
}

int cross(const point &a, const point &b, const point &c) {
  return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);  
}

bool
angleCmp(const point &self, const point &that) {
  int t = cross(pivot, that, self);
  if (t < 0) return true;
  if (t == 0) return (distsqr(pivot, self) < distsqr(pivot, that));
  return false;  
}

double area() {
  double r = 0.0;
  for (int i = 0; i < poly.size(); ++i) {
    int j = (i + 1) % poly.size();
    r += (poly[i].x * poly[j].y - poly[j].x * poly[i].y); 
  }
  //D(r);
  return r / 2.0;
}

double cx(double a) {
  double ans = 0.0;
  for (int i = 0; i < poly.size() - 1; ++i) {
    point p = poly[i], p_next = poly[i + 1];
   // ans += ((p.x + p_next.x) * (p.x * p_next.y - p_next.x * p.y));
    ans += p.x;
  }
  // return ans / (6.0 * a);
   return ans;
}

double cy(double a) {
  double ans = 0.0;
  for (int i = 0; i < poly.size() - 1; ++i) {
    point p = poly[i], p_next = poly[i + 1];
   // ans += ((p.y + p_next.y) * (p.x * p_next.y - p_next.x * p.y));
    ans += p.y;
  }
   //return ans / (6.0 * a);
   return ans;
}

double
watering(double x, double y) {
  double ans = 0.0;
  for (int i = 0; i < poly.size() - 1; ++i) {
    point p = poly[i];
    ans += p.w * ((1.0*p.x/p.w - x) * (1.0*p.x/p.w - x) + (1.0*p.y/p.w - y)*(1.0*p.y/p.w - y));
  }
  return ans;
}

int sumW(){
   int acum = 0;
   for(int i = 0; i < poly.size() - 1; ++i){
      point p = poly[i];
      acum += p.w;
   }
   return acum;
}

int
main() {
  int n;
  while (cin >> n) {
    poly.clear();
    for (int i = 0; i < n; ++i) {
      int x, y, w;
      cin >> x >> y >> w;
      poly.push_back(point(x * w, y * w, w));
    }
    //pivot = poly[0];
    sort(poly.begin(), poly.end(), angleCmp);
    double A = area();
    poly.push_back(poly[0]);
    D(sumW());
    double cX = cx(A) / sumW() , cY = cy(A) / sumW();
    D(cX); D(cY);
    printf("%.3f\n", watering(cX, cY));
  }
  return 0;
}

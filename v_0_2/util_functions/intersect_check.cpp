#ifndef INTERSECT_CHECK_CPP
#define INTERSECT_CHECK_CPP

#include "data_types.h"
// A C++ program to check if two given line segments intersect
#include <iostream>
using namespace std;
 
/*struct Point
{
    int x;
    int y;
};*/
 
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(pair<double, double> p, pair<double, double> q, pair<double, double> r)//Point p, Point q, Point r
{
    if (q.first <= max(p.first, r.first) && 
    	q.first >= min(p.first, r.first) && 
    	q.second <= max(p.second, r.second) && 
    	q.second >= min(p.second, r.second)) 
    	return true;//q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)
 
    return false;
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(pair<double, double> p, pair<double, double> q, pair<double, double> r)//Point p, Point q, Point r
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);//(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)
 
    if (val == 0) return 0;  // colinear
 
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool do_intersect(road road1, road road2)//Point p1, Point q1, Point p2, Point q2
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(road1.first, road1.second, road2.first);//p1, q1, p2
    int o2 = orientation(road1.first, road1.second, road2.second);//p1, q1, q2
    int o3 = orientation(road2.first, road2.second, road1.first);//p2, q2, p1
    int o4 = orientation(road2.first, road2.second, road1.second);//p2, q2, q1
 
 	/*
 	cout << "road1: " << road1.first.first << " , " << road1.first.second << " - " << road1.second.first << " , " << road1.second.second << "\n";
 	cout << "road2: " << road2.first.first << " , " << road2.first.second << " - " << road2.second.first << " , " << road2.second.second << "\n";
 	cout << "o1: " << o1 << "\n";
 	cout << "o2: " << o1 << "\n";
 	cout << "o3: " << o1 << "\n";
 	cout << "o4: " << o1 << "\n";
 	
 	bool temp;
 	cin >> temp;
 	*/
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(road1.first, road2.first, road1.second)) return true;//p1, p2, q1
 
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(road1.first, road2.second, road1.second)) return true;//p1, q2, q1
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(road2.first, road1.first, road2.second)) return true;//p2, p1, q2
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(road2.first, road1.second, road2.second)) return true;//p2, q1, q2
 
    return false; // Doesn't fall in any of the above cases
}
 
// Driver program to test above functions
/*
int main()
{
    //struct Point p1 = {1, 1}, q1 = {10, 1};
    //struct Point p2 = {1, 2}, q2 = {10, 2};
 	
 	road my_road1;
 	road my_road2;
 	
 	my_road1 = make_pair(make_pair(1, 1), make_pair(10, 1));
 	my_road2 = make_pair(make_pair(1, 2), make_pair(10, 2));
 	
    do_intersect(my_road1, my_road2)? cout << "Yes\n": cout << "No\n";
 
    //p1 = {10, 0}, q1 = {0, 10};
    //p2 = {0, 0}, q2 = {10, 10};
    
    my_road1 = make_pair(make_pair(10, 0), make_pair(0, 10));
 	my_road2 = make_pair(make_pair(0, 0), make_pair(10, 10));
    
    do_intersect(my_road1, my_road2)? cout << "Yes\n": cout << "No\n";
 
    //p1 = {-5, -5}, q1 = {0, 0};
    //p2 = {1, 1}, q2 = {10, 10};
    
    my_road1 = make_pair(make_pair(-5, -5), make_pair(0, 0));
 	my_road2 = make_pair(make_pair(1, 1), make_pair(10, 10));
    
    do_intersect(my_road1, my_road2)? cout << "Yes\n": cout << "No\n";
 
    return 0;
}
*/
#endif

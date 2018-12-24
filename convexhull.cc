#include "convexhull.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
//struct Point{
//	x_value;
//	y_value;
//};

// helper functions below this line //


//Given an rvector object with Points, returns the Point with minimum x value
Point find_minx( std::vector<Point>& alist ){
	std::vector<Point>::iterator begin = alist.begin();
	std::vector<Point>::iterator end = alist.end();
	Point min_pointx = *begin;
	while ( begin != end ){
		if ((*begin).x_value < min_pointx.x_value){
			min_pointx = *begin;
		}
		begin++;
	}
	return min_pointx;
}


//Given an rvector object with Points, returns the Point with maximum x value
Point find_maxx( std::vector<Point>& alist ){
	std::vector<Point>::iterator begin = alist.begin();
	std::vector<Point>::iterator end  = alist.end();
	Point min_pointx = *begin;
	while ( begin != end ){
		if ((*begin).x_value > min_pointx.x_value){
			min_pointx = *begin;
		}
		begin++;
	}
	return min_pointx;
}


//Given 3 Points, the funtion returns the area of the triangle spawned by the 3 points using the cross product.
//AB X AC -->  Sign of the result is determined through the right hand rule and the z axis.
int tri_area(Point pointA, Point pointB, Point pointC){
	int vectorAB_x = pointB.x_value - pointA.x_value;
	int vectorAB_y = pointB.y_value - pointA.y_value;
	int vectorAC_x = pointC.x_value - pointA.x_value;
	int vectorAC_y = pointC.y_value - pointA.y_value;
	
	int cross_product = ((vectorAB_x * vectorAC_y) - (vectorAB_y * vectorAC_x));
	return cross_product;
}  
	

int convexhull( std::vector<Point>& alist ){
	//forming the basic return array that will just contain the Points with the minimum and maximum x coordinate
	std::vector<Point> return_array;

	//find the Point with the least x coordinate and the Point with the max x coordinate; put in return array
	Point min_pointx = find_minx( alist );
	Point max_pointx = find_maxx( alist );
  return_array.push_back(min_pointx);
	return_array.push_back(max_pointx);	
 
	for (auto i: return_array){
		std::cout << "x value is" << i.x_value << "and y value is" << i.y_value;
	}

	//make 2 vectors, upper side and lower side; they contain points that lie above and below the line	
	//drawn by min_pointx and max_pointx as determined by the triangle area helper function

	std::vector<Point> upper_side;
	std::vector<Point> lower_side;
	for (auto i : alist){
		int signed_area = tri_area( min_pointx, max_pointx, i );
		if (signed_area > 0){
			upper_side.push_back( i );
 		}	
		else{
			lower_side.push_back( i );
		}
	}
	for (auto i: upper_side){
		std::cout << "x value of upper side  is" << i.x_value << "and y value of upper side is" << i.y_value << "\n";
	}
	
	for (auto i: lower_side){
		std::cout << "x value of lower side is" << i.x_value << "and y value of lower side is" << i.y_value << "\n";
	}		

		
	

	//std::vector<Point> hull1 = hull( min_pointx, max_pointx, upper_side, True );
	//std::vector<Point> hull2 = hull( min_pointx, max_pointx, lower_side, False );
	
//	return_array.insert( return_array.end(), hull1.begin(), hull1.end() )
//	return_array.insert( return_array.end(), hull2.begin(), hull2.end() )
	return 0;
}

int main(){
	Point point1;
	point1.x_value = 1;
	point1.y_value = 2;
	
	Point point2;
	point2.x_value = 3;
	point2.y_value = 1;
	
	Point point3;
	point3.x_value = 2;
	point3.y_value = 5;

	Point point4;
	point4.x_value = 6;
	point4.y_value = 2;

	std::vector<Point> myvector;
	myvector.push_back(point1);
	myvector.push_back(point2);
	myvector.push_back(point3);
	myvector.push_back(point4);

	convexhull(myvector);
	return 0;
}












	

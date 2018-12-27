#include "quickhull.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>

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
	
std::vector<Point> hull( Point pointA, Point pointB, std::vector<Point> arr_points, bool positive_area ){
	//Base case
	if ( arr_points.size() == 1 or arr_points.size() == 0 ){		
		return arr_points;
	}
	
	//Finding out which point in ArrPonts is furthest from the line drawn by PointA and PointB 
	int max_area = abs( tri_area( pointA, pointB, arr_points[0] ) );
	Point max_areaP = arr_points[0];
	for ( auto point: arr_points ){
		int area = abs( tri_area( pointA, pointB, point ) );
		if ( area > max_area ){
			max_area = area;
			max_areaP = point;
		}
	}
	//std::cout << "max area point x value is  " << max_areaP.x_value << " and y value is  " <<  max_areaP.y_value << "\n";
	 
	//The triangle PointA, PointB, max_areaP divides arrPoints in 3 regions. Need to call hull recursively on the two
  //regions that face outwards, i.e. points not contained in the triangle.
	std::vector<Point> recur_array_a;
	std::vector<Point> recur_array_b;

	for (auto point:  arr_points){
		int signed_area = tri_area( pointA, max_areaP, point);
	
	//if ArrPoints were the points with positive area to start with (PositiveArea == True), then the points of importance in the
  //2 regions will have positive triangle area w.r.t PointA and max_areaP 
  	if ( positive_area ){
			if ( signed_area > 0){
				recur_array_a.push_back( point );
			}
		}
		else{
			if (signed_area < 0 ){
				recur_array_a.push_back( point );
 			}
		}
	}
	
	
	//Repeat with PointB
	for (auto point:  arr_points){
		int signed_area = tri_area( max_areaP, pointB, point);
  	if ( positive_area ){
			if ( signed_area > 0){
				recur_array_b.push_back( point );
			}
		}
		else{
			if (signed_area < 0 ){
				recur_array_b.push_back( point );
			}
		}
	}
	
	//for (auto point: recur_array_a){
	//std::cout << "recur array A point x value is " << point.x_value << " and y value is " << point.y_value << "\n";
//	}
	
	//for (auto point: recur_array_b){
	//std::cout << "recur array B point x value is " << point.x_value << " and y value is " << point.y_value << "\n";
	//} 

	std::vector<Point> recursive_vector1 = hull( pointA, max_areaP, recur_array_a, positive_area );
	std::vector<Point> recursive_vector2 = hull( max_areaP, pointB, recur_array_b, positive_area );
	
	recursive_vector1.insert( recursive_vector1.end(), recursive_vector2.begin(), recursive_vector2.end() );
	recursive_vector1.push_back( max_areaP );
	return recursive_vector1;
}

std::vector<Point> convexhull( std::vector<Point>& alist ){
	//forming the basic return array that will just contain the Points with the minimum and maximum x coordinate
	std::vector<Point> return_array;

	//find the Point with the least x coordinate and the Point with the max x coordinate; put in return array
	Point min_pointx = find_minx( alist );
	Point max_pointx = find_maxx( alist );
  return_array.push_back(min_pointx);
	return_array.push_back(max_pointx);	
 
	//for (auto i: return_array){
	//	std::cout << "x value is " << i.x_value << " and y value is " << i.y_value << "\n";
	//}

	//make 2 vectors, upper side and lower side; they contain points that lie above and below the line	
	//drawn by min_pointx and max_pointx as determined by the triangle area helper function

	std::vector<Point> upper_side;
	std::vector<Point> lower_side;
	for (auto i : alist){
		int signed_area = tri_area( min_pointx, max_pointx, i );
		if (signed_area > 0){
			upper_side.push_back( i );
 		}
		//not using simple else because don't want to include min and max 'x' points 
		//which would give a signed area of 0	
		else if (signed_area < 0){   
			lower_side.push_back( i );
		}
	}
	//for (auto i: upper_side){
	//	std::cout << "x value of upper side  is " << i.x_value << " and y value of upper side is " << i.y_value << "\n";
 //}
	
	//for (auto i: lower_side){
	//	std::cout << "x value of lower side is " << i.x_value << " and y value of lower side is " << i.y_value << "\n";
//	}		

		
	

		std::vector<Point> hull1 = hull( min_pointx, max_pointx, upper_side, true );
		std::vector<Point> hull2 = hull( min_pointx, max_pointx, lower_side, false );
	
		return_array.insert( return_array.end(), hull1.begin(), hull1.end() );
 		return_array.insert( return_array.end(), hull2.begin(), hull2.end() );
		
		return return_array;
		
}

	


int main(){
	using namespace std;
 	
	srand(time(0));	
	std::ofstream file;
	file.open("Input.txt");
	std::vector<Point> myvector;
//	file << "X Values" << setw(40) << right << "Y_Values" << "\n";
	for (int i = 0; i < 100; i++){
		Point rand_point;
		rand_point.x_value = rand() % 100;
		rand_point.y_value = rand() % 100;
		myvector.push_back( rand_point );

		file << rand_point.x_value << setw(40) << right <<  rand_point.y_value << left << "\n";
	}
	file.close();
	std::vector<Point> hull_points = convexhull(myvector);
	file.open("Output.txt");
	//file << "X Values" << setw(40) << right << "Y_Values" << "\n";	
	for (auto point: hull_points){
		file << point.x_value << setw(40) << right <<  point.y_value << left << "\n";
	}
					


	return 0;
}












	

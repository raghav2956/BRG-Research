import numpy as np
import matplotlib.pyplot as plt

def main(alist):
    return_array= []                               # Forming final return array, empty to start with
    min_pointx = find_minx( alist )                # Finding point with min x coordinate
    max_pointx = find_maxx( alist )                # Finding point with max x coordinate
    return_array.append( min_pointx )            # Since these points will always be a part of the convex hull, add them to the return array
    return_array.append( max_pointx )   
    #plot(alist)
    
    #plt.plot(min_pointx, max_pointx)
    #plt.show()
    
    Upper_side = []        # Empty list of all the points 'above'/ on one side of the line drawn by min_pointx and maxpointx
    Lower_side = []        # Empty list of all the points 'below'/ on other side of the line drawn by min_pointx and maxpointx
    for Point in alist:
        Signed_area = tri_area( min_pointx, max_pointx, Point ) # Calculating signed area of triangle formed by some point, min_pointx and maxpointx
        #print ("Signed Area is " + str(Signed_area))
        if Signed_area > 0:
            Upper_side.append( Point )                       # Appending depending on sign of triangle
        if Signed_area < 0:
            Lower_side.append( Point )
    
    #print ("Upper Points are" + str(Upper_side))
    #print ("Lower Points are" + str(Lower_side))
            
    hull1 = hull( min_pointx, max_pointx, Upper_side, True )# Passing in min_pointx, maxpointx, array of points and a boolean for the +ve triangle area side
    #print (hull1)                                            # ....returns list of points
    hull2 = hull( min_pointx, max_pointx, Lower_side, False )
    #print (hull2)
    #print (return_array)
    return return_array + hull1 + hull2
        
    
    #print (Upper_side)
    #print (Lower_side)

def hull( PointA, PointB, ArrPoints, PositiveArea ):
    if ( len(ArrPoints) == 1 or len(ArrPoints) == 0 ):                         # Base Case
        return ArrPoints
    
    max_area = abs( tri_area( PointA, PointB, ArrPoints[0] ) )   # Finding out which point in ArrPonts is furthest from the line drawn by PointA and PointB 
    max_areaP = ArrPoints[ 0 ]
    for Point in ArrPoints:
        Area = abs( tri_area( PointA, PointB, Point ) )
        #print( "Abs Area is" + str(Area))
        if Area > max_area:
            max_area = Area
            max_areaP = Point
    
    #print ("Furthest Point is" + str(max_areaP))
    Recur_arrayA = []     # The triangle PointA, PointB, max_areaP divides arrPoints in 3 regions. Need to call hull recursively on the two
                          # regions that face outwards, i.e. points not contained in the triangle.
    Recur_arrayB = []
    for Point in ArrPoints:
        Signed_area = tri_area( PointA, max_areaP, Point )
        
         # if ArrPoints were the points with positive area to start with (PositiveArea == True), then the points in the
         # 2 regions of importance will have positive triangle area w.r.t PointA and max_areaP 
        
        if PositiveArea:                                                 
            if Signed_area > 0:
                Recur_arrayA.append(Point)
        
          # if ArrPoints were the points with positive area to start with (PositiveArea == True), then the points in the 
          # 2 regions of importance will have positive triangle area w.r.t PointA and max_areaP    
                
        else:                            
            if Signed_area < 0:
                Recur_arrayA.append(Point)
                
        Signed_area = tri_area( max_areaP, PointB, Point )  # Repeat with PointB
        #print ("Signed Area for PointB and maxAreaP is" + str(Signed_area))
        if PositiveArea:
            if Signed_area > 0:
                Recur_arrayB.append(Point)
        else:
            if Signed_area < 0:
                Recur_arrayB.append(Point)
    
    #print ("RecurArrA is" + str(Recur_arrayA))
    #print ("RecurArrB is" + str(Recur_arrayB))

    
    return [max_areaP] + hull(PointA, max_areaP, Recur_arrayA, PositiveArea) + hull(PointB, max_areaP, Recur_arrayB, PositiveArea)
        
    
# Helper Functions   

def find_minx(alist):
    min_pointx = alist[0]
    for x in alist:
        if x[0] < min_pointx[0]:
            min_pointx = x
    return min_pointx

def find_maxx(alist):
    max_pointx = alist[0]
    for x in alist:
        if x[0] > max_pointx[0]:
            max_pointx = x
    return max_pointx

def plot(alist):
    x_coords = []
    y_coords = []
    
    for point in alist:
        x_coords.append(point[0])
        y_coords.append(point[1])
    
    plt.plot(x_coords, y_coords, 'ro')
    plt.show()
    
def tri_area( PointA, PointB, PointC ):                             #calculates area of triangle spawned by PointA, PointB, PointC
    vectorAB = [PointB[0] - PointA[0], PointB[1] - PointA[1] ]      #Use vector calculus to caluclate signed area
    vectorAC = [PointC[0] - PointA[0], PointC[1] - PointA[1] ]
    CrossProduct_mag = vectorAB[0] * vectorAC[1] - vectorAB[1] * vectorAC[0]  #Cross Product
    
    return CrossProduct_mag
    

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// to store queries results
#include <vector>

// just for output
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
//
#include "../Source/Functions/functions.h"
#include "../Source/Functions/functions.hh"
#include "../Source/Geometry/geometry.h"
#include "../Source/Geometry/geometry.hh"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef double T; 

typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<box, unsigned> value;


using namespace std;

void testOriginalExample(); 

void testGeometry(); 

void testGeometry2(); 

void testPolygon(); 

int main()
{
  // create the rtree using default constructor
  //testOriginalExample(); 
  //testGeometry(); 
  //testGeometry2(); 

 testPolygon(); 
}

void testOriginalExample()
{
std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
bgi::rtree< value, bgi::quadratic<16> > rtree;
// create some values
for ( unsigned i = 0 ; i < 10 ; ++i )
{
    // create a box
    box b(point(i + 0.0f, i + 0.0f), point(i + 0.5f, i + 0.5f));
    // insert new value
    rtree.insert(std::make_pair(b, i));
}
// find values intersecting some area defined by a box
box query_box(point(0, 0), point(5, 5));
std::vector<value> result_s;
rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));
// find 5 nearest values to a point
std::vector<value> result_n;
rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));
// display results
point p(1.,1.); 
point o(0.,0.); 
double l = bg::distance(p,o); 
std::cout << "length : " << bg::distance(p,o) << std::endl; 
//std::cout << " p : " << p/l << std::endl; 
std::cout << "spatial query box:" << std::endl;
std::cout << bg::wkt<box>(query_box) << std::endl;
std::cout << "spatial query result:" << std::endl;
BOOST_FOREACH(value const& v, result_s)
    std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;

std::cout << "knn query point:" << std::endl;
std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
std::cout << "knn query result:" << std::endl;
BOOST_FOREACH(value const& v, result_n)
    std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;
}

void testGeometry()
{
std::cout << " test Geometry " << std::endl; 
using namespace gokstad;
Point2D p(2.,3.); 
Point2D p2(4.,5.); 
std::cout << "p : " ; 
display(std::cout,p); 
std::cout << std::endl; 
std::cout << "p : " << " " << p << std::endl; 
Point2D q = p + p2; 
std::cout << " q : " << q << std::endl; 
Point2D r(-6.);
setPointValue(r,-5.5); 
std::cout << " r : " << r << std::endl; 
double l = length(r);
std::cout << " l : " << l << " ana : " << sqrt( 5.5*5.5*2) << std::endl; 
Point2D pp;
//pp = multiply(r,3.); 
pp = r*3.; 
std::cout << " r*3. : " << pp << std::endl; 
//point p(2.,3.);
//int n = bg::dimension<point>(); 
//std::cout << " p : " << n << std::endl; 
///std::cout << p; 
//std::cout << " p : " << p << std::endl; 
//std::cout << " p : " << bg::wkt<point>(point(0, 0)) << std::endl; 
//std::cout << gokstad::bg::wkt<point>(point(0, 0)) << std::endl;
}

void testGeometry2()
{
std::cout << " test Geometry 2" << std::endl; 
using namespace gokstad;
Point2D p0(2.,3.); 
Point2D p1(5.,6.); 
//std::cout << " dist(p1,p0) : " << distance(p1,p0) << std::endl; 
std::cout << " p1 - p0 : " << subtract(p1,p0) << std::endl; 
Segment<Point2D> line(p0,p1);
T s0,s1;
line.getParameterRange(s0,s1); 
std::cout << "s0 : " << s0 << " s1 : " << s1 << std::endl; 
Point2D q = line.pointOnLine(0.5*(s0+s1)); 
std::cout << " q : " << q << " ana : " << 0.5*(p0 + p1) << std::endl; 
}

void testPolygon()
{
  std::cout << " in test polygon " << std::endl; 
  using namespace gokstad; 
  std::vector< const Line<Point2D>* > lineArray;
  std::vector< Point2D > pointArray;
  pointArray.push_back( Point2D(1.,1.) );
  pointArray.push_back( Point2D(4.,2.) );
  pointArray.push_back( Point2D(5.,6.) );
  pointArray.push_back( Point2D(3.5,8.3) );
  pointArray.push_back( Point2D(0.,3.78) );
  for(int i =0 ; i < pointArray.size() ; ++i){
    int iNext = (i+1)%pointArray.size(); 
    lineArray.push_back( new Segment<Point2D>(pointArray[i],pointArray[iNext])); 
  }
  Boundary2D outerBoundary(lineArray);
  std::vector< const Line<Point2D>* > lineArray2;
  std::vector< Point2D > pointArray2;
  pointArray2.push_back( Point2D(2.,2.) );
  pointArray2.push_back( Point2D(3.,4.) );
  pointArray2.push_back( Point2D(3.,2.5) );
  for(int i =0 ; i < pointArray2.size() ; ++i){
    int iNext = (i+1)%pointArray2.size(); 
    lineArray2.push_back( new Segment<Point2D>(pointArray2[i],pointArray2[iNext])); 
  }
  Boundary2D innerBoundary(lineArray2);
  std::vector< const Boundary2D* > boundaryArray; 
  boundaryArray.push_back(&outerBoundary); 
  boundaryArray.push_back(&innerBoundary); 
  //  PolygonalApproximation2D polygon(&outerBoundary,0.1); 
  PolygonalApproximation2D polygon(boundaryArray,0.1); 

  std::ofstream hinaus("Output/outerPolygon.dat");
  polygon.displayRing(hinaus,0); 
  std::ofstream hinaus2("Output/innerPolygon.dat");
  polygon.displayRing(hinaus2,1); 

  Point2D p0(2.7,2.8); 
  Point2D p1(1.5,3.);
  Point2D p2(1.,6.); 

  std::cout << " p0 : " << ( polygon.isPointInside(p0) ? "true" : "false" ) << std::endl; 
  std::cout << " p1 : " << ( polygon.isPointInside(p1) ? "true" : "false" ) << std::endl; 
  std::cout << " p2 : " << ( polygon.isPointInside(p2) ? "true" : "false" ) << std::endl; 

  for(int i = lineArray2.size()-1 ; i >= 0 ; --i){
    delete [] lineArray2[i]; 
  }
  for(int i = lineArray.size()-1 ; i >= 0 ; --i){
    delete [] lineArray[i]; 
  }
}

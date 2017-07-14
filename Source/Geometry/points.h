/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_POINTS_H
#define GOKSTAD_POINTS_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <ostream> 
#include <iostream>

namespace gokstad {

  namespace bgGokstad = boost::geometry; 
  typedef bgGokstad::model::point<double, 2, bgGokstad::cs::cartesian> Point2D;
  typedef bgGokstad::model::point<double, 3, bgGokstad::cs::cartesian> Point3D;

  template<typename Point>
  Point multiply(const Point & p,
		   typename bgGokstad::detail::param< Point >::type value) ; 
/*
  template<typename Point>
  Point operator*(const Point & p, typename bgGokstad::detail::param< Point >::type value) ;

  template<typename Point>
  Point operator/(const Point & p, typename bgGokstad::detail::param< Point >::type value) ; 
*/
  Point2D operator/(const Point2D & p, double value) ; 

  Point2D operator*(const Point2D & p, double value) ; 

  Point2D operator*(double value, const Point2D & p) ; 

  template<typename Point>
  Point sum(const Point & q, const Point & p);
  
  Point2D operator+(const Point2D & q, const Point2D & p);

  template<typename Point>
  Point subtract(const Point & q, const Point & p);

  Point2D operator-(const Point2D & q, const Point2D & p);

  template<typename Point>
  void setPointValue(Point & q, typename bgGokstad::detail::param< Point >::type value); 

  template<typename Point>
  typename bgGokstad::default_distance_result<Point,Point>::type distance(Point const& p, Point const& q); 


  template<typename Point>
  typename bgGokstad::default_distance_result<Point,Point>::type length(Point const& q); 

  template<typename Point>
  void display(std::ostream& os, Point const& p); 

  std::ostream& operator<<(std::ostream& os, Point2D const& p); 

} /// namespace

#endif

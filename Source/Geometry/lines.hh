/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_LINES_HH
#define GOKSTAD_LINES_HH

#include "lines.h"

namespace gokstad {

  template<typename Point>
  Point Line<Point>::pointOnLine(T x) const
  {
    return this->evaluate(x,0); 
  }

  template<typename Point>
  Point Line<Point>::tangentialOnLine(T x) const
  {
    return this->evaluate(x,1); 
  }

  template<typename Point>
  bool Line<Point>::isStraight() const
  { 
    return false; 
  }

  ////////////////////////StraightLine////////////////////////////

  template<typename Point>
  Segment<Point>::Segment(Point x0_, Point x1)
    : l(distance(x0_,x1)),x0(x0_),vec()
  {
    vec = multiply(subtract(x1,x0),1./l); 
    //    std::cout << " vec : " << vec << std::endl; 
  }

  template<typename Point>
  void Segment<Point>::getParameterRange
  (typename bgGokstad::default_distance_result<Point,Point>::type & s0,
   typename bgGokstad::default_distance_result<Point,Point>::type & s1) const
  {
    s0 = 0;
    s1 = l; 
  }

  template<typename Point>
  Point Segment<Point>::evaluate(typename Line<Point>::T x, int d) const
  {
    switch(d){
    case 0:
      return x0 + multiply(vec,x);
    case 1:
      return vec; 
    default:
      Point p;
      setPointValue(p,0); 
      return p;
    }
  }

  template<typename Point>
  void Segment<Point>::getBoundingBox(Point & x0_, Point & x1_) const
  {
    x0_ = x0;
    x1_ = x0 + multiply(vec,l); 
  }

  template<typename Point>
  bool Segment<Point>::isStraight() const
  {
    return true; 
  }

} // namespace gokstad

#endif

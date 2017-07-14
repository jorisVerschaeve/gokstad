/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_BOUNDARY_H
#define GOKSTAD_BOUNDARY_H

#include "lines.h"
#include "lines.hh"

namespace gokstad {

// basically a collection of lines
class Boundary2D 
{
 public: 
  Boundary2D(std::vector< const Line<Point2D>* > boundaryArray);
  int getSize() const; 
  const Line<Point2D>* getLine(int i) const; 
 private:
  std::vector< const Line<Point2D>* > array; 
}; 

class Domain2D
{
 public:
  virtual bool isPointInside(Point2D const& p) const = 0; 
}; 

 class PolygonalApproximation2D : public Domain2D
{
  typedef boost::geometry::model::polygon<Point2D> Polygon;
  typedef double T; 
 public:
  // dx = typical discretization distance of the arclength between 
  // consecutive points
  PolygonalApproximation2D(const Boundary2D *const boundary, T dx); 
  // having holes inside: the user is responsible for having a correct boundary
  // i.e. rotation correctly. 
  PolygonalApproximation2D(std::vector<const Boundary2D *> boundaryArray, T dx); 
  void displayRing(std::ostream & os, int iR) const; 
  virtual bool isPointInside(Point2D const& p) const; 
 protected:
  void computePointArray(const Boundary2D *const boundary,
			 T dx, std::vector<Point2D> & array); 
 private:
  Polygon poly; 
}; 

} // namespace gokstad

#endif

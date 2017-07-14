/*
 *
 *
 *
 * Joris Verschaeve
 *
 *
 *
 */

#ifndef GOKSTAD_BOUNDARY_HH
#define GOKSTAD_BOUNDARY_HH

#include "boundary.h"

namespace gokstad {

Boundary2D::Boundary2D(std::vector< const Line<Point2D>* > boundaryArray)
  : array(boundaryArray)
{

}

int Boundary2D::getSize() const
{
  return array.size(); 
}

  const Line<Point2D>* Boundary2D::getLine(int i) const
{
  return array[i]; 
}

  //////////////////////////PolygonalApproximation2D//////////////////////

  PolygonalApproximation2D::PolygonalApproximation2D(const Boundary2D *const boundary, T dx)
  {
    std::vector<Point2D> array;
    this->computePointArray(boundary,dx,array); 
    boost::geometry::append(poly,array);
  }

  PolygonalApproximation2D::PolygonalApproximation2D
  (std::vector<const Boundary2D *> boundaryArray, T dx)
  {
    std::vector<Point2D> array;
    this->computePointArray(boundaryArray[0],dx,array); 
    boost::geometry::append(poly,array);
    if( boundaryArray.size() > 1 ){
      boost::geometry::interior_rings(poly).resize(boundaryArray.size()-1);
      for(int i = 1; i < boundaryArray.size() ; ++i){
	std::vector<Point2D> array;
	this->computePointArray(boundaryArray[i],dx,array); 
	boost::geometry::append(poly,array,i-1);
      }
    }
  }

  void PolygonalApproximation2D::computePointArray(const Boundary2D *const boundary,
						   T dx,
						   std::vector<Point2D> & array)
  {
    T s0,s1; 
    for(int i = 0 ; i < boundary->getSize() ; ++i){
      boundary->getLine(i)->getParameterRange(s0,s1); 
      if( boundary->getLine(i)->isStraight() ){
	Point2D p0 = boundary->getLine(i)->pointOnLine(s0); 
	array.push_back(p0); 
      } else {
	int N = ceil( (s1-s0)/dx);
	for(int j = 0; j < N ; ++j){
	  T s = (s1-s0)*T(i)/T(N) + s0;
	  Point2D p0 = boundary->getLine(i)->pointOnLine(s); 
	  array.push_back(p0); 
	}
      }
    }
    boundary->getLine(0)->getParameterRange(s0,s1); 
    Point2D p0 = boundary->getLine(0)->pointOnLine(s0); 
    array.push_back(p0); 
  }

  void PolygonalApproximation2D::displayRing(std::ostream & os, int iR) const
  {
    if( iR == 0 ){
      std::vector< Point2D > const& array = poly.outer(); 
      for(int i =0; i < array.size() ; ++i){
	os << array[i] << std::endl; 
      }
      //      boost::geometry::model::ring<Point2D> const& ring
      //	= boost::geometry::exterior_ring(poly); 
      //      typename boost::geometry::model::ring<Point2D>::iterator iter; 
      //      for( iter = ring.begin() ; iter != ring.end() ; ++iter){
      //	os << *iter << std::endl; 
      //      }
    } else {
      std::vector< Point2D > const& array = poly.inners()[iR-1]; 
      for(int i =0; i < array.size() ; ++i){
	os << array[i] << std::endl; 
      }
    }
  }

  bool PolygonalApproximation2D::isPointInside(Point2D const& p) const
  {
    return boost::geometry::within(p,poly); 
  }

} // namespace gokstad

#endif

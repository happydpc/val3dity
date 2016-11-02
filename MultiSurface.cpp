//
//  MultiSurface.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "MultiSurface.h"
#include "Primitive.h"
#include "input.h"


MultiSurface::MultiSurface(std::string id) {
  _id = id;
  _is_valid = -1;
}

MultiSurface::~MultiSurface() {
}

bool MultiSurface::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
  _is_valid = _surface->validate_as_multisurface(tol_planarity_d2p, tol_planarity_normals);
  return _is_valid;
}


std::string MultiSurface::get_type() 
{
  return "MultiSurface";
}

bool MultiSurface::is_valid() {
  return _is_valid;
}

bool MultiSurface::is_empty() {
  return _surface->is_empty();
}


std::string MultiSurface::get_report_xml() {
  std::stringstream ss;
  ss << "\t<MultiSurface>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t<id>none</id>" << std::endl;
  ss << "\t\t<numberfaces>" << this->number_faces() << "</numberfaces>" << std::endl;
  // ss << "\t\t<numbervertices>" << this->num_vertices() << "</numbervertices>" << std::endl;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<faces>" << std::get<0>(e) << "</faces>" << std::endl;
      ss << "\t\t\t<info>" << std::get<1>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  ss << _surface->get_report_xml();
  ss << "\t</MultiSurface>" << std::endl;
  return ss.str();}


int MultiSurface::number_faces() 
{
  return _surface->number_faces();
}


bool MultiSurface::set_surface(Surface* s) 
{
  _surface = s;
  return true;
}

std::set<int> MultiSurface::get_unique_error_codes() {
  std::set<int> errs = Primitive::get_unique_error_codes();
  std::set<int> tmp = _surface->get_unique_error_codes();
  errs.insert(tmp.begin(), tmp.end());
  return errs;
}


Surface* MultiSurface::get_surface() 
{
  return _surface;
}

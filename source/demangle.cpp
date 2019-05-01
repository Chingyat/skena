#include "demangle.hpp"
#include <boost/core/demangle.hpp>

std::string lince::demangle(const std::string &Name) {
  return boost::core::demangle(Name.c_str());
}

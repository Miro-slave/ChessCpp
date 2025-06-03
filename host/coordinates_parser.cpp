#include "coordinates_parser.h"

#include <regex>
#include <sstream>

namespace chess {


std::optional<std::pair<Coordinates, Coordinates>> CoordinatesParser::tryParse(const std::string& coordinates) {
  std::stringstream sstream(coordinates);

  std::string start;
  std::string dest;

  sstream >> start;
  sstream >> dest;

  const std::regex expr("[a-h][1-8]");

  if (!std::regex_match(start, expr) ||
	  !std::regex_match(dest, expr))
  {
    return {};
  }

  Coordinates start_coords = {start[1] - '1', start[0] - 'a'};
  Coordinates dest_coords = {dest[1] - '1', dest[0] - 'a'};

  return std::make_pair(start_coords, dest_coords);
}

};  // namespace chess

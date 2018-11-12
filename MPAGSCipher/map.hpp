#ifndef MPAGSCIPHER_MAP_HPP
#define MPAGSCIPHER_MAP_HPP

#include <map>
#include <utility>
/**
 * \file map.hpp
 * \brief Contains the typedef of the maps.
 */

/**
 * \typedef Cartesian
 * \brief Alias for the XY coords
 */
typedef std::pair < size_t,  size_t> Cartesian;

/**
 * \typedef Grid
 * \brief Alias for the map's coords
 */
typedef std::map < size_t, size_t > Grid;

/**
 * \typedef CharOnGrid
 * \brief Alias for the coords to map association
 */
typedef std::map < char, Cartesian > CharOnGrid;

/**
 * \typedef GridOnChar
 * \brief Alias for the map to coords association
 */
typedef std::map < Cartesian, char > GridOnChar;


#endif // MPAGSCIPHER_MAP_HPP

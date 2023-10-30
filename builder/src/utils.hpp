#pragma once

// STL
#include <iostream>
#include <string>
// boost
#include <boost/filesystem.hpp>
// CppParser
#include <cppparser.h>

namespace fs = boost::filesystem;

/// @brief if not `Assert` print the other args and exit failure
#define ASSERT(Assert, ...)                \
  do {                                     \
    if (Assert) break;                     \
    std::cerr << __VA_ARGS__ << std::endl; \
    std::exit(EXIT_FAILURE);               \
  } while (false)
/// @brief if not fs::is_directori((Dir)) fails
#define ASSERT_DIR(Dir) \
  ASSERT(fs::is_directory((Dir)), (Dir) << " is not a valid directory")

/// @brief removes `[[.*]]` sequences from the string because the parser does
/// not handle them well
inline void remove_attributes(std::string& contents);
/// @brief same as readFile from CppParser but calls remove_attributes
inline std::string read_file(const std::string& filename);
/// @brief same as parseFile from CppParser but calls read_file instead of
/// readFile
inline CppCompoundPtr parse_file(CppParser& parser,
                                 const std::string& filename);
/// @brief wrapper to get a string repr of a CppObj
inline std::string str_of_cpp(const CppObj* cppObj);
/// @brief wrapper to get a string repr of a CppObj
inline std::string str_of_cpp(const CppObjPtr& cppObjPtr);
/// @brief std::string to UPPER
inline std::string to_upper(std::string_view str);
/// @brief std::string_view to PascalCase
inline std::string to_pascal_case(std::string_view str);
/// @brief std::string_view(s) to just_name, to PascalCase
template <typename... Args>
inline std::string make_pascal_name(const Args&... args);
/// @brief remove everything before the last occcurence of `::` (not in place)
inline std::string just_name(const std::string& name);
/// @brief remove everything before the last occcurence of `::` (in place)
inline std::string just_name(std::string&& name);

// utils/
#include "utils/hash.hpp"
#include "utils/ptr_iter.hpp"
#include "utils/sep.hpp"

// hxx
#include "utils.hxx"
// ros2_control_py_builder
#include "parse.hpp"
#include "utils.hpp"
#include "write.hpp"

int main(int argc, char** argv) {
  ASSERT(argc == 3, "Invalid number of command line arguments, expected 2 got "
                        << argc - 1);

  fs::path hi_dir = argv[1];
  fs::path dst_dir = argv[2];
  ASSERT(fs::is_directory(hi_dir), hi_dir << " is not a valid directory");
  ASSERT(fs::is_directory(dst_dir), dst_dir << " is not a valid file");

  std::vector<std::string> headers;
  std::unordered_map<std::string, std::vector<Cls>> classes;

  for (auto entry : fs::recursive_directory_iterator{hi_dir}) {
    const fs::path& path = entry.path();
    if (!entry.is_regular_file() || path.extension() != ".hpp" ||
        path.filename() == "macros.hpp" ||
        path.filename() == "component_parser.hpp")
      continue;

    std::string name = path.lexically_relative(hi_dir).string();
    parse_header(headers, classes, path, name);
  }

  fs::path src_dir = dst_dir / "src";
  fs::path hi_py = src_dir / "hardware_interface_py.cpp";
  fs::path inc_hi_dir = dst_dir / "include" / "hardware_interface";
  fs::path inc_hi_types_dir = inc_hi_dir / "types";

  fs::create_directories(src_dir);
  fs::create_directories(inc_hi_types_dir);

  for (const auto& [name, classes] : classes)
    write_named_hi_py_hpp(inc_hi_dir, name, classes);

  write_hi_py_cpp(hi_py, headers);

  return 0;
}

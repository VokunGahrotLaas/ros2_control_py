#pragma once

// STL
#include <string>
#include <vector>

struct Attr {
  Attr(const std::string& name) : name{name} {}

  std::string name;
};

struct Ctor {
  Ctor(std::vector<std::string>&& args) : args{std::move(args)} {}

  std::vector<std::string> args;
};

struct Memb {
  Memb(const std::string& name) : name{name} {}

  std::string name;
};

struct VMemb {
  VMemb(const std::string& name, const std::string& ret_type,
        const std::string cls, const std::vector<std::string>&& args,
        const std::vector<std::string>&& args_names)
      : name{name},
        ret_type{ret_type},
        cls{cls},
        args{std::move(args)},
        args_names{std::move(args_names)} {}

  std::string name;
  std::string ret_type;
  std::string cls;
  std::vector<std::string> args;
  std::vector<std::string> args_names;
};

struct Cls {
  Cls(const std::string& name, const std::string& mother)
      : name{name}, mother{mother} {}

  std::string name;
  std::string mother;
  std::vector<Attr> attrs;
  std::vector<Memb> membs;
  std::vector<Ctor> ctors;
  std::vector<VMemb> vmembs;
};

struct Enum {
  Enum(const std::string& name) : name{name} {};

  std::string name;
  std::vector<std::string> items;
};

struct Var {
  Var(const std::string& name) : name{name} {};

  std::string name;
};

struct Header {
  Header(const std::string& name) : name{name} {}

  std::string name;
  std::vector<std::string> namespaces;
  std::vector<Cls> classes;
  std::vector<Enum> enums;
  std::vector<Var> vars;
};

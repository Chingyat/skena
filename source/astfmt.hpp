#pragma once
#include "ast.hpp"

#include <fmt/format.h>

template <> struct fmt::formatter<lince::AST> {
  int NIndent = 0;

  template <typename OutIt> static OutIt Indent(OutIt O) {
    return format_to(O, " ");
  }

  template <typename OutIt> static OutIt Indent(OutIt O, int N) {
    while (N--)
      O = Indent(O);
    return O;
  }

  template <typename OutIt> OutIt writeChar(OutIt O, char C) {
    format_to(O, "{}", C);
    if (C == '\n')
      Indent(O, NIndent);
    return O;
  }

  template <typename ParseContext> auto parse(ParseContext &C) {
    return C.begin();
  }

  template <typename FormatContext>
  auto format(const lince::AST &A, FormatContext &C) {
    NIndent = 0;
    auto ASTS = A.dump();
    for (char X : ASTS) {
      if (X == '{' || X == '[') {
        NIndent++;
        writeChar(C.out(), X);
        writeChar(C.out(), '\n');
      } else if (X == '}' || X == ']') {
        NIndent--;
        writeChar(C.out(), '\n');
        writeChar(C.out(), X);
      } else if (X == ',') {
        writeChar(C.out(), X);
        writeChar(C.out(), '\n');
      } else {
        writeChar(C.out(), X);
      }
    }
    return C.out();
  }
};

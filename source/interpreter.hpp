#pragma once
#include "ast.hpp"
#include "exceptions.hpp"
#include "module.hpp"
#include "value.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <vector>

namespace lince {

class Interpreter : public ModuleBase<Interpreter> {
  friend class ModuleBase<Interpreter>;

public:
  struct ScopeGuard {
    Interpreter *I;

    explicit ScopeGuard(Interpreter *C) noexcept : I(C) {}

    ~ScopeGuard() {
      I->ValueNS.pop_back();
      I->FunctionNS.pop_back();
    }
  };

  ScopeGuard createScope() {
    ValueNS.emplace_back();
    FunctionNS.emplace_back();
    return ScopeGuard(this);
  }

  std::unique_ptr<AST> parse(const std::string &Expr) const;

  void eval(AST *MyAST, Value &Result);

  Value getValue(const std::string &Name) const {
    if (auto V = findVariable(Name))
      return *V;
    throw EvalError("No such variable: " + Name);
  }

  const Value &setValue(const std::string &Name, Value V) {
    if (auto Var = findVariable(Name))
      return const_cast<Value &>(*Var) = std::move(V);
    return ValueNS.back()[Name] = std::move(V);
  }

  const Value &addLocalValue(const std::string &Name, Value V) {
    return ValueNS.back()[Name] = std::move(V);
  }

  template <typename Sequence>
  Function const &getFunction(const std::string &Name,
                              Sequence const &Type) const &;

  const Function &addLocalFunction(const std::string &Name, Function Func);

  template <typename Sequence>
  Value callFunction(const std::string &Name, Sequence &&Args);

  std::set<std::string> getCompletionList(const std::string &Text) const;

  template <typename ModuleImpl> void addModule(ModuleBase<ModuleImpl> &&M) {
    FunctionNS.emplace_back(std::move(M).getFunctionNS());
    ValueNS.emplace_back(std::move(M).getValueNS());
  }

private:
  const Value *findVariable(const std::string &Name) const noexcept;

  auto findFunctions(const std::string &Name) const noexcept
      -> std::vector<std::reference_wrapper<const Function>>;

  std::vector<std::multimap<std::string, Function>> FunctionNS;
  std::vector<std::map<std::string, Value>> ValueNS;

  ScopeGuard SG = createScope();
};

template <typename Sequence>
Function DynamicFunction(Sequence &&ParamsV, std::shared_ptr<AST> Body);

} // namespace lince

#include "interpreter.tpp"

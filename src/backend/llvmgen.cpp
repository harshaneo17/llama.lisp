#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/DerivedTypes.h>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>

using json = nlohmann::json;

class LLVMCodeGenerator {
public:
    LLVMCodeGenerator() : module("Bril_Module", context) {}

    llvm::Module module;

    void generate(const json& bril_prog) {
        for (auto& fn : bril_prog["functions"]) {
            gen_function(fn);
        }
    }

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder{ context };
    std::map<std::string, llvm::Value*> func_symtab;
    std::map<std::string, llvm::BasicBlock*> func_bbs;

    llvm::Type* gen_type(const std::string& type) {
        if (type == "int") {
            return llvm::Type::getInt32Ty(context);
        }
        else if (type == "void") {
            return llvm::Type::getVoidTy(context);
        }
        else if (type == "bool") {
            return llvm::Type::getInt1Ty(context);
        }
        else {
            throw std::runtime_error("Unknown type " + type);
        }
    }

    llvm::Value* gen_var(const std::string& var) {
        auto it = func_symtab.find(var);
        if (it != func_symtab.end()) {
            return it->second;
        }
        else {
            throw std::runtime_error("Unknown variable " + var);
        }
    }

    llvm::BasicBlock* gen_label(const std::string& label) {
        auto it = func_bbs.find(label);
        if (it != func_bbs.end()) {
            return it->second;
        }
        else {
            auto* bb = llvm::BasicBlock::Create(context, label, builder.GetInsertBlock()->getParent());
            func_bbs[label] = bb;
            return bb;
        }
    }


};

int main() {
    LLVMCodeGenerator code_gen;
    json bril_prog;
    std::cout << "Enter the json file" << std::endl;
    std::cin >> bril_prog;
    code_gen.generate(bril_prog);
    code_gen.module.print(llvm::outs(), nullptr);
    return 0;
}

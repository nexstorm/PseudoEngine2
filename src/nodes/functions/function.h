#pragma once
#include "nodes/base.h"
#include "psc/procedure.h"

class ReturnErrSignal {};

class FunctionNode : public Node {
private:
    std::unique_ptr<PSC::Function> function;

public:
    FunctionNode(const Token &token, PSC::Function *function);

    // Adds function to ctx
    std::unique_ptr<NodeResult> evaluate(PSC::Context &ctx) override;
};

class FunctionCallNode : public Node {
private:
    const std::string functionName;
    const std::vector<Node*> args;

public:
    FunctionCallNode(const Token &token, std::vector<Node*> &&args);

    std::unique_ptr<NodeResult> evaluate(PSC::Context &ctx) override;
};

class ReturnNode : public UnaryNode {
public:
    using UnaryNode::UnaryNode;

    std::unique_ptr<NodeResult> evaluate(PSC::Context &ctx) override;
};

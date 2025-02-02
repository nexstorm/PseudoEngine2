#include "pch.h"

#include "psc/error.h"
#include "nodes/variable.h"

DeclareNode::DeclareNode(const Token &token, std::vector<const Token*> &&identifiers, PSC::DataType type)
    : Node(token), identifiers(std::move(identifiers)), type(type)
{}

std::unique_ptr<NodeResult> DeclareNode::evaluate(PSC::Context &ctx) {
    for (auto identifier : identifiers) {
        if (ctx.getVariable(identifier->value) != nullptr)
            throw PSC::RedeclarationError(token, ctx, identifier->value);

        ctx.addVariable(new PSC::Variable(identifier->value, type, false));
    }

    return std::make_unique<NodeResult>(nullptr, PSC::DataType::NONE);
}


ConstDeclareNode::ConstDeclareNode(const Token &token, Node &node, const Token &identifier)
    : UnaryNode(token, node), identifier(identifier)
{}

std::unique_ptr<NodeResult> ConstDeclareNode::evaluate(PSC::Context &ctx) {
    auto value = node.evaluate(ctx);

    if (ctx.getVariable(identifier.value) != nullptr)
        throw PSC::RedeclarationError(token, ctx, identifier.value);

    ctx.addVariable(new PSC::Variable(identifier.value, value->type, true, value->data.get()));

    return std::make_unique<NodeResult>(nullptr, PSC::DataType::NONE);
}


AssignNode::AssignNode(const Token &token, Node &node, const Token &identifier)
    : UnaryNode(token, node), identifier(identifier)
{}

std::unique_ptr<NodeResult> AssignNode::evaluate(PSC::Context &ctx) {
    auto valueRes = node.evaluate(ctx);

    PSC::Variable *var = ctx.getVariable(identifier.value);
    if (var == nullptr) {
        var = new PSC::Variable(identifier.value, valueRes->type, false);
        ctx.addVariable(var);
    }

    if (var->isConstant)
        throw PSC::ConstAssignError(token, ctx, var->name);

    valueRes->implicitCast(var->type);
    if (var->type != valueRes->type)
        throw PSC::InvalidUsageError(token, ctx, "assignment operator: incompatible data types");

    switch (var->type) {
        case PSC::DataType::INTEGER:
            var->get<PSC::Integer>() = valueRes->get<PSC::Integer>();
            break;
        case PSC::DataType::REAL:
            var->get<PSC::Real>() = valueRes->get<PSC::Real>();
            break;
        case PSC::DataType::BOOLEAN:
            var->get<PSC::Boolean>() = valueRes->get<PSC::Boolean>();
            break;
        case PSC::DataType::CHAR:
            var->get<PSC::Char>() = valueRes->get<PSC::Char>();
            break;
        case PSC::DataType::STRING:
            var->get<PSC::String>() = valueRes->get<PSC::String>();
            break;
        default:
            std::abort();
    }

    return std::make_unique<NodeResult>(nullptr, PSC::DataType::NONE);
}


std::unique_ptr<NodeResult> AccessNode::evaluate(PSC::Context &ctx) {
    PSC::Variable *var = ctx.getVariable(token.value);

    if (var == nullptr)
        throw PSC::NotDefinedError(token, ctx, "Identifier '" + token.value + "'");

    PSC::Value *data;
    switch (var->type) {
        case PSC::DataType::INTEGER:
            data = new PSC::Integer(var->get<PSC::Integer>());
            break;
        case PSC::DataType::REAL:
            data = new PSC::Real(var->get<PSC::Real>());
            break;
        case PSC::DataType::BOOLEAN:
            data = new PSC::Boolean(var->get<PSC::Boolean>());
            break;
        case PSC::DataType::CHAR:
            data = new PSC::Char(var->get<PSC::Char>());
            break;
        case PSC::DataType::STRING:
            data = new PSC::String(var->get<PSC::String>());
            break;
        default:
            std::abort();
    }

    return std::make_unique<NodeResult>(data, var->type);
}

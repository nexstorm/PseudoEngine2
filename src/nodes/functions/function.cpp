#include "pch.h"

#include "psc/error.h"
#include "psc/scope/block.h"
#include "nodes/variable.h"
#include "nodes/array.h"
#include "nodes/functions/function.h"

FunctionNode::FunctionNode(const Token &token, PSC::Function *function)
    : Node(token), function(function)
{}

std::unique_ptr<NodeResult> FunctionNode::evaluate(PSC::Context &ctx) {
    if (ctx.getFunction(function->name) != nullptr)
        throw PSC::RedeclarationError(token, ctx, function->name);

    ctx.addFunction(std::move(function));

    return std::make_unique<NodeResult>(nullptr, PSC::DataType::NONE);
}


FunctionCallNode::FunctionCallNode(const Token &token, std::vector<Node*> &&args)
    : Node(token), functionName(token.value), args(std::move(args))
{}

std::unique_ptr<NodeResult> FunctionCallNode::evaluate(PSC::Context &ctx) {
    PSC::Function *function = ctx.getFunction(functionName);

    if (function == nullptr)
        throw PSC::NotDefinedError(token, ctx, "Function '" + functionName + "'");

    size_t nArgs = function->parameters.size();
    if (args.size() != nArgs)
        throw PSC::InvalidArgsError(token, ctx);

    auto functionCtx = std::make_unique<PSC::Context>(&ctx, functionName, true, function->returnType);
    ctx.switchToken = &token;

    for (size_t i = 0; i < args.size(); i++) {
        auto argRes = args[i]->evaluate(ctx);

        if (!function->byRef) argRes->implicitCast(function->parameters[i].type);
        if (function->parameters[i].type != argRes->type) {
            throw PSC::InvalidArgsError(token, ctx);
        }

        PSC::Variable *var;
        if (function->byRef) {
            AccessNode *accsNode = dynamic_cast<AccessNode*>(args[i]);
            ArrayAccessNode *arrAccsNode = dynamic_cast<ArrayAccessNode*>(args[i]);
            if (!accsNode) {
                throw PSC::RuntimeError(token, ctx, "Only variables can be used as arguements when passing by reference");
            }

            if (accsNode) {
                PSC::Variable *original = ctx.getVariable(accsNode->getToken().value);
                if (original == nullptr) std::abort();
                var = original->createReference(function->parameters[i].name);
            } else {
                var = PSC::Variable::createArrayElementReference(function->parameters[i].name, argRes->type, arrAccsNode->getValue(ctx).first);
            }
        } else {
            var = new PSC::Variable(function->parameters[i].name, argRes->type, false);

            switch (var->type) {
                case PSC::DataType::INTEGER:
                    var->get<PSC::Integer>() = argRes->get<PSC::Integer>();
                    break;
                case PSC::DataType::REAL:
                    var->get<PSC::Real>() = argRes->get<PSC::Real>();
                    break;
                case PSC::DataType::BOOLEAN:
                    var->get<PSC::Boolean>() = argRes->get<PSC::Boolean>();
                    break;
                case PSC::DataType::CHAR:
                    var->get<PSC::Char>() = argRes->get<PSC::Char>();
                    break;
                case PSC::DataType::STRING:
                    var->get<PSC::String>() = argRes->get<PSC::String>();
                    break;
                default:
                    std::abort();
            }
        }

        functionCtx->addVariable(var);
    }

    try {
        function->run(*functionCtx);
    } catch (ReturnErrSignal&) {}

    if (!functionCtx->returnValue)
        throw PSC::RuntimeError(*(function->defToken), *functionCtx, "Missing RETURN statement");

    ctx.switchToken = nullptr;

    return std::move(functionCtx->returnValue);
}

std::unique_ptr<NodeResult> ReturnNode::evaluate(PSC::Context &ctx) {
    if (!ctx.isFunctionCtx) 
        throw PSC::InvalidUsageError(token, ctx, "RETURN statement");

    ctx.returnValue = node.evaluate(ctx);
    ctx.returnValue->implicitCast(ctx.returnType);

    if (ctx.returnValue->type != ctx.returnType)
        throw PSC::RuntimeError(token, ctx, "Invalid return type");

    throw ReturnErrSignal();
}

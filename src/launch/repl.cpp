#include "pch.h"

#include "launch/run.h"

static const char *multilineKeywords[] = {
    "IF",
    "CASE",
    "WHILE",
    "REPEAT",
    "FOR",
    "PROCEDURE",
    "FUNCTION"
};

bool startREPL() {
    std::cout << "PseudoEngine2 v0.1 REPL\nEnter 'EXIT' to quit\n";

    Lexer lexer;
    Parser parser;
    auto globalCtx = PSC::Context::createGlobalContext();

    while (true) {
        std::cout << "> " << std::flush;
        std::string code;
        std::getline(std::cin, code);

        if (code == "EXIT") break;
        if (code.size() == 0) continue;

        for (const char *keyword : multilineKeywords) {
            if (code.rfind(keyword, 0) == 0) {
                std::string line = " ";
                while (line.size() > 0) {
                    code += "\n";
                    std::cout << ". " << std::flush;
                    std::getline(std::cin, line);
                    code += line;
                }
                break;
            }
        }

        lexer.setExpr(&code);
        try {
            const std::vector<Token*> &tokens = lexer.makeTokens();
            parser.setTokens(&tokens);
            PSC::Block *block = parser.parse();

            std::cout.precision(10);
            block->run(*globalCtx);
        } catch (const PSC::Error &e) {
            e.print();
        }
    }
    return true;
}

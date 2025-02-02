#include "pch.h"
#include <fstream>

#include "launch/run.h"

extern std::string psfilename;

bool runFile() {
    std::ifstream file(psfilename);

    if (!file.is_open()) {
        std::cerr << "Error: File '" << psfilename << "' not found!" << std::endl;
        return false;
    }

    std::string fData;
    while (file.good()) {
        std::string line;
        std::getline(file, line);
        fData += line;
        fData += "\n";
    }
    file.close();

    Lexer lexer(&fData);
    try {
        const std::vector<Token*> &tokens = lexer.makeTokens();
        Parser parser(&tokens);
        PSC::Block *block = parser.parse();
        std::cout.precision(10);

        auto globalCtx = PSC::Context::createGlobalContext();
        block->run(*globalCtx);
    } catch (const PSC::Error &e) {
        e.print();
        return false;
    }
    return true;
}

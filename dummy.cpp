#include <stdlib.h>

#include <fstream>
#include <iostream>
#include "frontends/common/constantFolding.h"
#include "frontends/common/options.h"
#include "frontends/common/parseInput.h"
#include "frontends/common/parser_options.h"
#include "frontends/common/resolveReferences/referenceMap.h"
#include "frontends/p4/frontend.h"
#include "frontends/p4/toP4/toP4.h"
#include "frontends/p4/typeChecking/typeChecker.h"
#include "frontends/p4/typeMap.h"
#include "ir/ir.h"
#include "ir/pass_manager.h"
#include "ir/visitor.h"
#include "lib/compile_context.h"
#include "lib/cstring.h"
#include "lib/error.h"
#include "options.h"
#include "test/gtest/helpers.h"

int main(int argc, char *const argv[]) {
    AutoCompileContext autoP4DummyContext(new P4Dummy::P4DummyContext);
    
    auto &options = P4Dummy::P4DummyContext::get().options();

    if (options.process(std::min(2, argc), argv) == nullptr) {
        return EXIT_FAILURE; 
    }

    options.setInputFile();

    if (::errorCount()) {
        return EXIT_FAILURE; 
    }

    const IR::P4Program *program = P4::parseP4File(options);

    if (program == nullptr || ::errorCount()) {
        return EXIT_FAILURE;
    }

    if (argc > 2) {
        std::ofstream outputFile(argv[2]);

        if (!outputFile.is_open()) {
            std::cerr << "Error: Failed to open file " << argv[2] << std::endl;
            return EXIT_FAILURE; 
        }

        auto top4 = P4::ToP4(&outputFile, false);
        program->apply(top4);

    } else { 
        auto top4 = P4::ToP4(&std::cout, false);
        program->apply(top4);
    }

    return ::errorCount() > 0 ? EXIT_FAILURE : EXIT_SUCCESS; 
}


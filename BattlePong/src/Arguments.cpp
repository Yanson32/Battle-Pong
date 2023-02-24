#include "Arguments.h"
#include <GameUtilities/Core/ProgramArguments.h>
#include <iostream>
#include "Settings.h"
#include "GameUtilities/Core/Macros.h"
#include <string>
#include <cstdlib>

void help(GU::Core::ArgumentData params)
{   
    UNUSED(params);
    std::cout << "--help            Display help text" << std::endl;
    std::cout << "--version, -v     Display program version" << std::endl;
    exit(0);
}


void programArguments(int argc, char* argv[])
{
    GU::Core::ProgramArguments arguments(argc, argv);
    
    //Add help option 
    if(!arguments.add("--help", '\0', help))
        throw std::runtime_error("Error: unable to add key");


    //Add version option
    if(!arguments.add("--version", 'v', [](GU::Core::ArgumentData params){
        UNUSED(params);
        std::cout << "version = " << std::string(BP_VERSION) << std::endl;
        exit(0);
    }))
        throw std::runtime_error("Error: Unable to add key");
    arguments.run();
}


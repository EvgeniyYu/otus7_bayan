/**
    \file
    \mainpage Homework 7 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\brief Homework 7 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\author Bulanov Sergey
	\version 0.1.0
	\date January 2020
	\warning There was done for educational purposes.

*The purpose of this work is to familiarize with the boost option library and the file system library,
*in the context of their use when writing an application for finding duplicate files.
*/

#include "parser.h"
#include "finder.h"
#include "handler.h"

int main(int argc, char** argv) {

    using namespace bayan;

    std::shared_ptr<IOptions> options = OptionsParser().getOptions(argc, argv);

    if(!options)
        return 0;

    std::unique_ptr<IHandler> hendl = std::make_unique<Handler>(options);
    FileFinder filefinder(options);

    filefinder.scan();
    filefinder.out(std::move(hendl));

    return 0;
}

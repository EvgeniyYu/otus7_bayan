#include "def.h"
#include "cmd_line_processor.h"
#include "file_scanner.h"
#include "file_comparator.h"
#include <iostream>
#include <memory>
#include <exception>

int main(int argc, char *argv[])
{
    uptr_ICommandLineProcessor uptr_cmdline = std::make_unique<CommandLineProcessor>();
    if (!uptr_cmdline->process_cmd_line(argc, argv, std::cout))
    {
        std::cerr << "Error parsing options in command line" << std::endl;
        return 1;
    }
    //uptr_cmdline->print(std::cout);

    FileScanner scanner(uptr_cmdline->get_options());
    if (!scanner.scan())
    {
        std::cerr << "Error scanning files" << std::endl;
        return 1;
    }

    uptr_IFileComparetor fileComparator = std::make_unique<FileComparator>(uptr_cmdline->get_options(), scanner.getFilesList());
    try
    {
        fileComparator->compare();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    fileComparator->print(std::cout);

    return 0;
}

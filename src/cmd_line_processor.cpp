#include "cmd_line_processor.h"
#include <boost/program_options.hpp>
#include <sstream>

namespace po = boost::program_options;


bool CommandLineProcessor::process_cmd_line(int argc, char** argv, std::ostream& ofs)
{
    try
    {
        po::options_description desc("Options");
        desc.add_options()
            ("help",     "help message")
            ("include",   po::value<std::string>(&options.include_dirs)->required(),      "set the directories to scan")
            ("exclude",   po::value<std::string>(&options.exclude_dirs),      "set the directories to exclude from scanning")
            ("level",   po::value<int>(&options.level),      "set the level of scanning")
            ("min_size",   po::value<int>(&options.min_file_size),      "set the minimum file size")
            ("mask",   po::value<std::string>(&options.mask),      "set the mask of file names for comparing")
            ("block_size",   po::value<int>(&options.block_size),      "set the block size")
            ("hash",   po::value<std::string>(&options.hash_method),      "set the hash algorithm")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help"))
        {
            ofs << desc << "\n";
            return false;
        }

        po::notify(vm);
    }
    catch(...)
    {
        return false;
    }

    return true;
}

const Options& CommandLineProcessor::get_options() const
{
    return options;
}

void CommandLineProcessor::print(std::ostream& ofs) const
{
    ofs << "Using options: " << std::endl;
    ofs << "Include directories to scan: " << options.include_dirs << std::endl;
    ofs << "Exclude directories to scan: " << options.exclude_dirs << std::endl;
    ofs << "Level: " << options.level << std::endl;
    ofs << "Minimum file size: " << options.min_file_size << std::endl;
    ofs << "Mask of file extension: " << options.mask << std::endl;
    ofs << "Block size: " << options.block_size << std::endl;
    ofs << "Hash method: " << options.hash_method << std::endl;

}

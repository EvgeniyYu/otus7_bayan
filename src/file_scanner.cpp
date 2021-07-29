#include "file_scanner.h"
#include <filesystem>
#include <exception>
#include <memory>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>

namespace fs = std::filesystem;

FileScanner::FileScanner(const Options& _options): options(_options)
{
    iptr_validator = std::make_unique<FileValidator>(options);
}

bool FileScanner::scan()
{
    std::vector<std::string> v_include_dirs;
    boost::split(v_include_dirs, options.include_dirs, boost::is_any_of(separator));
    for (auto& incl_dir: v_include_dirs)
        boost::algorithm::trim(incl_dir);

    try
    {
        for (const auto& incl_dir: v_include_dirs)
        {
            //std::cout << "incl_dir: " << incl_dir << std::endl;
            for (auto it = fs::recursive_directory_iterator(incl_dir); it != fs::recursive_directory_iterator(); ++it)
            {
                std::string name = it->path();
                //std::cout << "filename: " << name << std::endl;
                if (!iptr_validator->validate(ValidatorParams(*it, it.depth()))) continue;
                files.emplace_back(name);

                //std::cout << "file: " << it->path() << "  size: " << fs::file_size(it->path()) << "  depth: " << it.depth() << std::endl;
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}


std::vector<File>& FileScanner::getFilesList()
{
    return files;
}

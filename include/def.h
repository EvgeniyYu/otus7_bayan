#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#include <fstream>
#include <memory>
#include <vector>


const std::string separator = ";";

struct File
{
    std::string name;
    size_t size;
    //std::vector<std::string> blocks;
    //std::unique_ptr<std::ifstream> f_stream;
    bool is_comparing;
    File(std::string& _name): name(_name), is_comparing(true) {}
};

struct FileData
{
    File file;
    std::vector<std::string> blocks;
    std::unique_ptr<std::ifstream> f_stream;
    FileData(const File& _file): file(_file) {}
};

struct Options
{
    std::string include_dirs;
    std::string exclude_dirs;
    int level = 0;
    int min_file_size = 1;
    std::string mask = ".*";
    int block_size = 5;
    std::string hash_method = "crc32";
};


#endif // DEF_H_INCLUDED

#ifndef FILE_COMPARATOR_H_INCLUDED
#define FILE_COMPARATOR_H_INCLUDED

#include "def.h"
#include "hash_algorithm.h"
#include <iostream>
#include <memory>
#include <vector>

using vv = std::vector<std::vector<std::string>>;

class IFileComparator
{
public:
    virtual void compare() = 0;
    virtual void print(std::ostream& ofs) = 0;
    virtual vv& get_vector_result() = 0;
};

class FileComparator: public IFileComparator
{
    uptr_IHashAlgorithm uptr_hashAlg;
    Options options;
    std::vector<FileData> v_filedata;
    vv v_results;
public:
    FileComparator(const Options& _options, const std::vector<File>& files);
    void compare() override;
    void print(std::ostream& ofs) override;
    vv& get_vector_result() override {return v_results;}
private:
    void read_next_block(FileData& file, size_t size_block);
    bool compare_vector_blocks(FileData& curr_file, FileData& other_file);
    bool compare_file(FileData& curr_file, FileData& other_file);
};

using uptr_IFileComparetor = std::unique_ptr<IFileComparator>;

#endif // FILE_COMPARATOR_H_INCLUDED

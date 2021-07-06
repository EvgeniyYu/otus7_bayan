#ifndef FILE_SCANNER_H_INCLUDED
#define FILE_SCANNER_H_INCLUDED

#include "def.h"
#include "file_validator.h"
#include <vector>


class FileScanner
{
    std::vector<File> files;
    Options options;
    uptr_IFileValidator iptr_validator;
public:
    FileScanner(const Options& _options);
    bool scan();
    std::vector<File>& getFilesList();
};

#endif // FILE_SCANNER_H_INCLUDED

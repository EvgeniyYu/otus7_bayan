#ifndef FILE_VALIDATOR_H_INCLUDED
#define FILE_VALIDATOR_H_INCLUDED

#include "def.h"
#include <vector>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

struct ValidatorParams
{
    std::filesystem::path filepath;
    int level;
    ValidatorParams(fs::path _filepath, int _level): filepath(_filepath), level(_level) {}
};

class IFileValidator
{
public:
    virtual bool validate(const ValidatorParams&) = 0;
};


class IsFileValidator: public IFileValidator
{
public:
    IsFileValidator();
    bool validate(const ValidatorParams& params) override;
};

class IsNotExcludedValidator: public IFileValidator
{
    std::vector<std::string> v_excluded_dirs;
public:
    IsNotExcludedValidator(const std::string& str_excluded_dirs);
    bool validate(const ValidatorParams& params) override;
};


class LevelValidator: public IFileValidator
{
    int limit_level;
public:
    LevelValidator(const int _limit_level);
    bool validate(const ValidatorParams& params) override;
};

class FileSizeValidator: public IFileValidator
{
    size_t min_size;
public:
    FileSizeValidator(const size_t _min_size);
    bool validate(const ValidatorParams& params) override;
};

class MaskValidator: public IFileValidator
{
    std::vector<std::string> v_masks;
public:
    MaskValidator(const std::string& mask);
    bool validate(const ValidatorParams& params) override;
};


class FileValidator: public IFileValidator
{
    std::vector<std::unique_ptr<IFileValidator>> vFileValidators;
public:
    FileValidator(const Options& options);
    bool validate(const ValidatorParams& params) override;
};


using uptr_IFileValidator = std::unique_ptr<IFileValidator>;

#endif // FILE_VALIDATOR_H_INCLUDED

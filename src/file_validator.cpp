#include "file_validator.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>

FileValidator::FileValidator(const Options& options)
{
    vFileValidators.push_back(std::make_unique<IsFileValidator>());
    vFileValidators.push_back(std::make_unique<IsNotExcludedValidator>(options.exclude_dirs));
    vFileValidators.push_back(std::make_unique<LevelValidator>(options.level));
    vFileValidators.push_back(std::make_unique<FileSizeValidator>(options.min_file_size));
    vFileValidators.push_back(std::make_unique<MaskValidator>(options.mask));
}

bool FileValidator::validate(const ValidatorParams& params)
{
    for (const auto& validator: vFileValidators)
    {
        if (!validator->validate(params)) return false;
    }
    return true;
}

IsFileValidator::IsFileValidator()
{
}

bool IsFileValidator::validate(const ValidatorParams& params)
{
    return (fs::is_directory(params.filepath))? false: true;
}


IsNotExcludedValidator::IsNotExcludedValidator(const std::string& str_excluded_dirs)
{
    boost::split(v_excluded_dirs, str_excluded_dirs, boost::is_any_of(separator));
    for (auto& excl_dir: v_excluded_dirs)
        boost::algorithm::trim(excl_dir);
}


bool IsNotExcludedValidator::validate(const ValidatorParams& params)
{
    for (const auto& excl_dir: v_excluded_dirs)
    {
        if (excl_dir.empty()) return true;
        if (params.filepath.string().find(excl_dir) != std::string::npos) return false;
    }
    return true;
}


LevelValidator::LevelValidator(const int _limit_level): limit_level(_limit_level)
{
}

bool LevelValidator::validate(const ValidatorParams& params)
{
    return (params.level <= limit_level)? true: false;
}

FileSizeValidator::FileSizeValidator(const size_t _min_size): min_size(_min_size)
{
}

bool FileSizeValidator::validate(const ValidatorParams& params)
{
    return (fs::file_size(params.filepath.string()) >= min_size)? true: false;
}

MaskValidator::MaskValidator(const std::string& mask)
{
    boost::split(v_masks, mask, boost::is_any_of(separator));
    for (auto& m: v_masks)
        boost::algorithm::trim(m);
}

bool MaskValidator::validate(const ValidatorParams& params)
{
    std::string ext = fs::path(params.filepath.string()).extension();
    for (const auto& m: v_masks)
        if (ext == m || m == "." || m == ".*" || m == "") return true;
    return false;
}

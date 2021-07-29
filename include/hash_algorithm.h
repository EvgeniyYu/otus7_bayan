#ifndef HASH_ALGORITHM_H_INCLUDED
#define HASH_ALGORITHM_H_INCLUDED

#include <string>
#include <memory>


class IHashAlgorithm
{
public:
    virtual std::string calculate(const std::string& str) = 0;
};

class CRC32: public IHashAlgorithm
{
public:
    std::string calculate(const std::string& str) override;
};

class MD5: public IHashAlgorithm
{
public:
    std::string calculate(const std::string& str) override;
};


using uptr_IHashAlgorithm = std::unique_ptr<IHashAlgorithm>;



#endif // HASH_ALGORITHM_H_INCLUDED

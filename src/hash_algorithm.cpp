#include "hash_algorithm.h"
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <sstream>

std::string CRC32::calculate(const std::string& str)
{
    boost::crc_32_type result;
    result.process_bytes(str.data(), str.length());
    std::stringstream ss;
    ss << result.checksum();
    return ss.str();
}


std::string MD5::calculate(const std::string& str)
{
    std::string res;

    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;

    hash.process_bytes(str.data(), str.length());
    hash.get_digest(digest);
    for (int i = 0; i < 4; i++)
        res += std::to_string(digest[i]);
    return res;
}

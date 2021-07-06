#include "file_comparator.h"
#include <sstream>
#include <algorithm>


FileComparator::FileComparator(const Options& _options, const std::vector<File>& files): options(_options)
{
    for (const auto& file: files)
        v_filedata.emplace_back(file);

    if (options.hash_method == "crc32")
            uptr_hashAlg = std::make_unique<CRC32>();
    else if (options.hash_method == "md5")
            uptr_hashAlg = std::make_unique<MD5>();
    else
        uptr_hashAlg = std::make_unique<CRC32>();
}


void FileComparator::read_next_block(FileData& file, size_t size_block)
{
	std::vector<char> buffer(options.block_size, '\0');
	file.f_stream->read(buffer.data(), size_block);

	std::stringstream sstr;
	std::for_each(buffer.begin(), buffer.end(), [&sstr](auto& val) {sstr << val;});

	std::string block = uptr_hashAlg->calculate(sstr.str());
	file.blocks.push_back(block);
}

bool FileComparator::compare_vector_blocks(FileData& curr_file, FileData& other_file)
{
	size_t vblocks_size = std::min(curr_file.blocks.size(), other_file.blocks.size());
	bool res = std::equal(curr_file.blocks.begin(), curr_file.blocks.begin() + vblocks_size, other_file.blocks.begin());
	if (vblocks_size && !res) return false;
	size_t cnt_blocks_to_read = std::labs(curr_file.blocks.size() - other_file.blocks.size());

	for (size_t i = 0; i < cnt_blocks_to_read; i++)
	{
		if (curr_file.blocks.size() < other_file.blocks.size())
		{
			read_next_block(curr_file, options.block_size);
			if (curr_file.blocks.back() != other_file.blocks[curr_file.blocks.size() - 1]) return false;
		}
		else
		{
			read_next_block(other_file, options.block_size);
			if (curr_file.blocks[other_file.blocks.size() - 1] != other_file.blocks.back()) return false;
		}
	}
	return true;
}

bool FileComparator::compare_file(FileData& curr_file, FileData& other_file)
{
	bool is_check_size = false;
	if (!curr_file.f_stream)
	{
		is_check_size = true;
		curr_file.f_stream = std::make_unique<std::ifstream>(curr_file.file.name, std::ios::binary);
		curr_file.file.size = curr_file.f_stream->seekg(0, std::ifstream::end).tellg();
		curr_file.f_stream->seekg(0, std::ifstream::beg);
	}
	if (!other_file.f_stream)
	{
		is_check_size = true;
		other_file.f_stream = std::make_unique<std::ifstream>(other_file.file.name, std::ios::binary);
		other_file.file.size = other_file.f_stream->seekg(0, std::ifstream::end).tellg();
		other_file.f_stream->seekg(0, std::ifstream::beg);
	}

	if (!curr_file.f_stream || !other_file.f_stream)
	{
		throw std::runtime_error("Error open file");
	}

	if (is_check_size)
		if (curr_file.file.size != other_file.file.size) return false;

	//compare vector of blocks for current file and other file
	if (curr_file.blocks.size() || other_file.blocks.size())
		if (!compare_vector_blocks(curr_file, other_file)) return false;

	//read next blocks and fill vectors of blocks and do comparing
	int remainder = curr_file.file.size;
	while (remainder)
	{
		size_t size_block = std::min(options.block_size, remainder);
		read_next_block(curr_file, size_block);
		read_next_block(other_file, size_block);

		//compare block
		if (curr_file.blocks.back() != other_file.blocks.back()) return false;

		remainder -= size_block;

		//std::cout << "remainder = " << remainder << "  size_block = " << size_block << std::endl;
	}
	return true;
}

void FileComparator::print(std::ostream& ofs)
{
    std::stringstream sstr;
    for (const auto& vv: v_results)
    {
        sstr << "\n";
        if (vv.size() <= 1) continue;
        for (const auto& v: vv)
            sstr << v << "\n";
    }
    ofs << sstr.str();
}


void FileComparator::compare()
{
	size_t curr_file_index = 0;
	if (v_filedata.size() < 2) return;
	while (curr_file_index < v_filedata.size())
	{
		if (!v_filedata[curr_file_index].file.is_comparing)
		{
			curr_file_index++;
			continue;
		}

        std::vector<std::string> v_res;
        v_res.push_back(v_filedata[curr_file_index].file.name);
		for (size_t i = 0; i < v_filedata.size(); i++)
		{
			if (i == curr_file_index) continue;
			if (!v_filedata[i].file.is_comparing) continue;
			if (compare_file(v_filedata[curr_file_index], v_filedata[i]))
			{
				v_filedata[i].file.is_comparing = false;

                v_res.push_back(v_filedata[i].file.name);

			}
			v_filedata[curr_file_index].file.is_comparing = false;
		}
		v_results.push_back(v_res);
		curr_file_index++;
	}
}



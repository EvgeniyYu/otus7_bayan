#define BOOST_TEST_MODULE test_bayan
#include <boost/test/unit_test.hpp>	
#include <iostream>
#include <filesystem>

#include "../include/def.h"
#include "../include/file_scanner.h"
#include "../include/file_comparator.h"
#include "../include/file_validator.h"
#include "../include/hash_algorithm.h"
#include <memory>
#include <vector>


namespace fs = std::filesystem;	
using vv = std::vector<std::vector<std::string>>;

BOOST_AUTO_TEST_SUITE(test_bayan)
BOOST_AUTO_TEST_CASE(test_result_level_0_hash_crc32)
{
	std::string str = "Current path: ";
	str += fs::current_path();
	BOOST_TEST_MESSAGE(str);
	
	Options options;
	options.include_dirs = "my_tests/next;my_tests/next2";
	options.exclude_dirs = "my_tests/next2/level_1;my_tests/next2/level_2";
	options.level = 0;
	options.min_file_size = 1;
	options.mask = ".*";
	options.block_size = 5;
	options.hash_method = "crc32";
	
    FileScanner scanner(options);
    bool is_scan = scanner.scan();
    BOOST_CHECK(is_scan == true);
    
    std::vector<File> files = scanner.getFilesList();
	BOOST_CHECK(files.size() == 11);
	
	/*
	IFileComparator *fileComparator = new FileComparator(options, files);    
    fileComparator->compare();
    vv vec_calc = fileComparator->get_vector_result();
    
    vv vec_true = {{"my_tests/next/my1.txt", "my_tests/next/ex1.cpp"}, 
    			{"my_tests/next/CTestTestfile.cmake", "my_tests/next/file_2.x", "my_tests/next/my_makefile2.x"}, 
    			{"my_tests/next2/exe_11", "my_tests/next2/exe_1", "my_tests/next2/exe_111"},
    			{"my_tests/next2/exe_22", "my_tests/next2/exe_2"}
    			};			
    			
    int index = 0;
    bool result = true;
    for (size_t i = 0; i < vec_calc.size(); i++)
    {        
    	//vector must contain more than one record so we check:
        if (vec_calc[i].size() <= 1) continue;
        for (size_t j = 0; j < vec_calc[i].size(); j++)
        {
        	if (vec_calc[i][j] != vec_true[index][j]) 
        	{
        		result = false;
        		BOOST_CHECK(result == true);
        	}
        }
        index++;
    }
	BOOST_CHECK(result == true);
	*/
}

BOOST_AUTO_TEST_SUITE_END()

/*
#define BOOST_TEST_MODULE test_bayan

#include <boost/test/unit_test.hpp>	
#include "../include/def.h"
#include "../include/file_scanner.h"
#include "../include/file_comparator.h"
#include "../include/file_validator.h"
#include "../include/hash_algorithm.h"
#include <memory>
#include <vector>

BOOST_AUTO_TEST_SUITE(test_bayan)

using vv = std::vector<std::vector<std::string>>;

bool compare_vectors(vv& v1, vv& v2)
{
    int index = 0;
    for (const auto& i: v1)
    {        
    	//vector must contain more than one record so we check:
        if (i.size() <= 1) continue;
        if (i != v2[index]) return false;
        index++;
    }
    return true;
}


BOOST_AUTO_TEST_CASE(test_result_level_0_hash_crc32)
{			
	Options options;
	options.include_dirs = "my_tests/next;my_tests/next2";
	options.exclude_dirs = "my_tests/next2/level_1;my_tests/next2/level_2";
	options.level = 0;
	options.min_file_size = 1;
	options.mask = ".*";
	options.block_size = 5;
	options.hash_method = "crc32";
	
    FileScanner scanner(options);
    bool is_scan = scanner.scan();
    BOOST_CHECK(is_scan == true);

    uptr_IFileComparetor fileComparator = std::make_unique<FileComparator>(options, scanner.getFilesList());    
    fileComparator->compare();
    vv vec_calc = fileComparator->get_vector_result();
    
    vv vec_true = {{"my_tests/next/my1.txt", "my_tests/next/ex1.cpp"}, 
    			{"my_tests/next/CTestTestfile.cmake", "my_tests/next/file_2.x", "my_tests/next/my_makefile2.x"}, 
    			{"my_tests/next2/exe_11", "my_tests/next2/exe_1", "my_tests/next2/exe_111"},
    			{"my_tests/next2/exe_22", "my_tests/next2/exe_2"}
    			};
    bool result = compare_vectors(vec_calc, vec_true);
    BOOST_CHECK(result == true);

}


BOOST_AUTO_TEST_CASE(test_result_level_1_hash_md5)
{
	Options options;
	options.include_dirs = "my_tests/next;my_tests/next2";
	options.exclude_dirs = "my_tests/next2/level_1;my_tests/next2/level_2";
	options.level = 1;
	options.min_file_size = 1;
	options.mask = ".*";
	options.block_size = 5;
	options.hash_method = "md5";
		
    FileScanner scanner(options);
    bool is_scan = scanner.scan();
    BOOST_CHECK(is_scan == true);

    uptr_IFileComparetor fileComparator = std::make_unique<FileComparator>(options, scanner.getFilesList());    
    fileComparator->compare();
    vv vec_calc = fileComparator->get_vector_result();
    
    vv vec_true = {{"my_tests/next/my1.txt", "my_tests/next/add/add_ex1.cpp", "my_tests/next/ex1.cpp"}, 
    			{"my_tests/next/CTestTestfile.cmake", "my_tests/next/add/add_file_2.x", "my_tests/next/file_2.x", "my_tests/next/my_makefile2.x"}, 
    			{"my_tests/next2/exe_11", "my_tests/next2/exe_1", "my_tests/next2/exe_111"},
    			{"my_tests/next2/exe_22", "my_tests/next2/exe_2"}
    			};
    bool result = compare_vectors(vec_calc, vec_true);
    BOOST_CHECK(result == true);
}

BOOST_AUTO_TEST_SUITE_END()
*/


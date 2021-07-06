# otus7_bayan
Files comparator

Using options:
--include (REQUIRED)
--exclude
--level (by default = 0)
--min_size (by default = 1)
--mask (by default = ".*". But you can write concrete extensions: ".cpp;.txt")
--block_size (by default = 5)
--hash (by default = "crc32")

For help write:
bayan --help

Example to run:
bayan --include="my_tests/next;my_tests/next2" --exclude="my_tests/next2/level_1;my_tests/next2/level_2" --level=1 --hash="md5"

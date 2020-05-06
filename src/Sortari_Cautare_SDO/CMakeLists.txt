build_test(RadixSort ${CMAKE_CURRENT_SOURCE_DIR}/radix_sort.cpp)
copy_file(radixsort.in RadixSort)

build_test(QuickSort ${CMAKE_CURRENT_SOURCE_DIR}/sortare_comparare.cpp)
copy_file(algsort.in QuickSort)

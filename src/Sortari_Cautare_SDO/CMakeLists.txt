build_test(RadixSort ${CMAKE_CURRENT_SOURCE_DIR}/radix_sort.cpp)
copy_file(radixsort.in RadixSort)

build_test(QuickSort ${CMAKE_CURRENT_SOURCE_DIR}/sortare_comparare.cpp)
copy_file(algsort.in QuickSort)

build_test(Inv ${CMAKE_CURRENT_SOURCE_DIR}/inv.cpp)
copy_file(inv.in Inv)

build_test(BinarySearch ${CMAKE_CURRENT_SOURCE_DIR}/cautare_binara.cpp)
copy_file(cautbin.in BinarySearch)

build_test(Factorial ${CMAKE_CURRENT_SOURCE_DIR}/factorial.cpp)
copy_file(fact.in Factorial)

build_test(NrTri ${CMAKE_CURRENT_SOURCE_DIR}/numarare_triunghiuri.cpp)
copy_file(nrtri.in NrTri)

build_test(SDO ${CMAKE_CURRENT_SOURCE_DIR}/quickselect.cpp)
copy_file(sdo.in SDO)

build_test(Binar ${CMAKE_CURRENT_SOURCE_DIR}/binar.cpp)
copy_file(binar.in Binar)

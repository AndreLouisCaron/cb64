# sha1 library demo projects.

macro(add_test_program name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} b64)
  add_dependencies(${name} b64)
endmacro()

add_test_program(b64-encode)
add_test_program(b64-decode)

set(encode ${CMAKE_BINARY_DIR}/b64-encode)
set(decode ${CMAKE_BINARY_DIR}/b64-decode)

set(test-data ${CMAKE_CURRENT_SOURCE_DIR}/data)

macro(encode_file target file expected-value)
  add_test(${target} "${encode}" "${test-data}/${file}")
  set_tests_properties(${target}
    PROPERTIES PASS_REGULAR_EXPRESSION ${expected-value})
endmacro()

macro(decode_file target file expected-value)
  add_test(${target} "${decode}" "${test-data}/${file}")
  set_tests_properties(${target}
    PROPERTIES PASS_REGULAR_EXPRESSION ${expected-value})
endmacro()

encode_file(001 001.txt "cGxlYXN1cmUu")
encode_file(002 002.txt "bGVhc3VyZS4=")
encode_file(003 003.txt "ZWFzdXJlLg==")
encode_file(004 004.txt "YXN1cmUu")
encode_file(005 005.txt "c3VyZS4=")

decode_file(006 006.txt "pleasure.")
decode_file(007 007.txt "leasure.")
decode_file(008 008.txt "easure.")
decode_file(009 009.txt "asure.")
decode_file(010 010.txt "sure.")

include_directories (${HELLO_SOURECE_DIR}/Hello)

link_directories(${HELLO_BINARY_DIR}/Hello)

add_executable(helloDemo demo.cxx demo_b.cxx)

target_link_libraries (helloDemo Hello)

set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST2 friendservice.cc ../friend.pb.cc)

add_executable(provider ${SRC_LIST})
add_executable(provider2 ${SRC_LIST2})
target_link_libraries(provider mprpc protobuf)
target_link_libraries(provider2 mprpc protobuf)
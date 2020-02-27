include_directories(${PROJECT_SOURCE_DIR})

add_library(sift_compute_lib SHARED sifts.cpp)
target_link_libraries(sift_compute_lib ${OpenCV_LIBS})

add_executable(BinaryTest BinaryTest.cpp)
target_link_libraries(BinaryTest 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

add_executable(BoVW BoVW.cpp)
target_link_libraries(MainProject ${OpenCV_LIBS})
target_link_libraries(MainProject sift_compute_lib ${OpenCV_LIBS})
target_link_libraries(MainProject 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

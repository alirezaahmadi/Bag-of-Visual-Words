include_directories(${PROJECT_SOURCE_DIR})

add_library(sift_compute_lib SHARED sifts.cpp)
target_link_libraries(sift_compute_lib ${OpenCV_LIBS})

add_executable(BoVW BoVW.cpp)
target_link_libraries(BoVW ${OpenCV_LIBS})
target_link_libraries(BoVW sift_compute_lib ${OpenCV_LIBS})
target_link_libraries(BoVW 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

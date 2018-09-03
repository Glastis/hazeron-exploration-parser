cmake_minimum_required(VERSION 3.9)
project(downloader)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        main.c              header/main.h
        utilities.c         header/utilities.h
        process.c           header/process.h
        xml_parser.c        header/xml_parser.h
        location.c          header/location.h
        location_new.c      header/location_new.h

        header/structure.h)

target_link_libraries(${PROJECT_NAME} pthread)

cmake_minimum_required(VERSION 3.16)

set(COMPONENTS 
    gmp 
    ff 
    fqfft 
    snark
    main
    nvs_sec_provider
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(malamut)

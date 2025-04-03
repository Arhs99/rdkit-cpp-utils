cmake_minimum_required(VERSION 3.30)

project(test-rdkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RDBASE $ENV{RDBASE})
set(CONDA_PREFIX $ENV{CONDA_PREFIX})
set(CAIRO_INCLUDE_DIRS "${CONDA_PREFIX}/include/cairo")
set(CAIRO_LIBRARIES "${CONDA_PREFIX}/lib/libcairo.so")
set(Boost_DIR "${CONDA_PREFIX}/lib/cmake/Boost-1.85.0")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${RDBASE}/Code/cmake/Modules")
set(RDKIT_INCLUDE_DIR ${RDBASE}/Code)


find_package(Boost 1.85 COMPONENTS iostreams REQUIRED)

include_directories ( ${RDKIT_INCLUDE_DIR} ${CAIRO_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
link_directories ( ${RDBASE}/lib)

set(RDKit_LIBS RDKitFileParsers RDKitFingerprints RDKitRDGeneral RDKitGraphMol)

find_package (Threads)
set(RDKit_THREAD_LIBS Threads::Threads)

set( LIBS  Boost::iostreams ${RDKit_THREAD_LIBS} ${CAIRO_LIBRARIES} z )

add_executable(test-rdkit fingerprints.cpp cnpy.cpp)
target_link_libraries(test-rdkit ${LIBS} ${RDKit_LIBS})

message(${LIBS})

include(GNUInstallDirs)
install(TARGETS test-rdkit
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)






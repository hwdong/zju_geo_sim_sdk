cmake_minimum_required(VERSION 2.8)

if(WIN32)
include($ENV{HOME}/usr/share/cmake/Modules/win32_default.cmake)
set(WIN_LIB_PATH "C:/MinGW/msys/home/wegatron/usr/lib64" CACHE PATH "")
endif(WIN32
)
set(WIN_LIB_PATH "C:/MinGW/msys/home/wegatron/usr/lib64" CACHE PATH "")
include($ENV{HOME}/usr/share/cmake/Modules/geo_sim_sdk.cmake)

include_geo_sim_sdk()
link_geo_sim_sdk()

if(WIN32)
	link_directories($ENV{HOME}/usr/lib64)
	link_directories($ENV{HOME}/usr/lib64/lapack_blas_windows)	
	set(UMFPACK_LIBRARIES umfpack amd SuiteSparse_config cholmod btf ccolamd  colamd ldl spqr camd klu metis lapack blas)
	# include_directories($ENV{HOME}/usr/OpenBLAS-v0.2.9.rc2-x86_64-Win/include)
	# link_directories($ENV{HOME}/usr/OpenBLAS-v0.2.9.rc2-x86_64-Win/lib)
else(WIN32)
	set(UMFPACK_LIBRARIES umfpack)
endif(WIN32)
## for dynamicly loading libs
if(WIN32)
	include_directories($ENV{HOME}/usr/gtk+-bundle_3.6.4-20131201_win64/include)
	include_directories($ENV{HOME}/usr/gtk+-bundle_3.6.4-20131201_win64/include/glib-2.0)
	include_directories($ENV{HOME}/usr/gtk+-bundle_3.6.4-20131201_win64/lib/glib-2.0/include)
	link_directories($ENV{HOME}/usr/gtk+-bundle_3.6.4-20131201_win64/lib)
else(WIN32)
	find_package(GTK2 REQUIRED)
	if(GTK2_FOUND)
		include_directories(${GTK2_INCLUDE_DIRS})
	endif(GTK2_FOUND)
endif(WIN32)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else(Boost_FOUND)
    message("CAN NOT FIND BOOST")
endif(Boost_FOUND)

#add_subdirectory(hjlib)
#add_subdirectory(jtflib)
add_subdirectory(zjucad)

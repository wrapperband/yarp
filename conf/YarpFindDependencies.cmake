# Copyright (C) 2009  RobotCub Consortium
# Copyright (C) 2012  iCub Facility, Istituto Italiano di Tecnologia
# Authors: Lorenzo Natale, Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


# USEFUL MACROS:

# Check if a package is installed and set some cmake variables
macro(checkandset_dependency package)

    if (${package}_FOUND)
        set(YARP_HAS_${package} TRUE CACHE BOOL "Package ${package} found" FORCE)
        set(YARP_USE_${package} TRUE CACHE BOOL "Use package ${package}")
    else (${package}_FOUND)
        set(YARP_HAS_${package} FALSE CACHE BOOL "" FORCE)
        set(YARP_USE_${package} FALSE CACHE BOOL "Use package ${package}")
    endif (${package}_FOUND)

    set(YARP_USE_SYSTEM_${package} TRUE CACHE INTERNAL "" FORCE)

    mark_as_advanced(YARP_HAS_${package} YARP_USE_${package})

    #store all dependency flags for later export
    set_property(GLOBAL APPEND PROPERTY YARP_DEPENDENCIES_FLAGS YARP_USE_${package})

endmacro (checkandset_dependency)


# Check if a package is installed or if is going to be built and set some cmake variables
macro(checkbuildandset_dependency package)

    if (${package}_FOUND)
        set(YARP_HAS_${package} TRUE CACHE BOOL "Package ${package} found" FORCE)
        set(YARP_USE_${package} TRUE CACHE BOOL "Use package ${package}")
        set(YARP_USE_SYSTEM_${package} TRUE CACHE BOOL "Use system-installed ${package}, rather than a private copy")
    else (${package}_FOUND)
        # If package was not found we force it to be built
        set(YARP_USE_SYSTEM_${package} FALSE CACHE BOOL "Use system-installed ${package}, rather than a private copy" FORCE)
        if(NOT YARP_USE_SYSTEM_${package})
            set(YARP_HAS_${package} TRUE CACHE BOOL "" FORCE)
            set(YARP_USE_${package} TRUE CACHE BOOL "Use package ${package}")
        else(NOT YARP_USE_SYSTEM_${package})
            set(YARP_HAS_${package} FALSE CACHE BOOL "" FORCE)
            set(YARP_USE_${package} FALSE CACHE BOOL "Use package ${package}")
        endif(NOT YARP_USE_SYSTEM_${package})
    endif (${package}_FOUND)

    mark_as_advanced(YARP_HAS_${package} YARP_USE_${package} YARP_USE_SYSTEM_${package})

    #store all dependency flags for later export
    set_property(GLOBAL APPEND PROPERTY YARP_DEPENDENCIES_FLAGS YARP_USE_${package})

endmacro(checkbuildandset_dependency)


# Check if a required package is installed.
macro(check_required_dependency package)
    if(NOT YARP_HAS_${package})
        message(FATAL_ERROR "Required package ${package} not found. Please install it to build yarp.")
#    else(NOT YARP_HAS_${package})
#        message(STATUS "${package} -> OK")
    endif(NOT YARP_HAS_${package})
endmacro(check_required_dependency)


# Check if an dependency required to enable an option is installed.
macro(check_optional_dependency optionname package)
    if(${optionname})
        if(NOT YARP_HAS_${package})
            message(FATAL_ERROR "Optional package ${package} not found. Please install it or disable the option \"${optionname}\" to build yarp.")
#        else(NOT YARP_HAS_${package})
#            message(STATUS "${package} ${optionname} -> OK")
        endif(NOT YARP_HAS_${package})
#    else(${optionname})
#        message(STATUS "${package} ${optionname} -> NOT REQUIRED")
    endif(${optionname})
endmacro(check_optional_dependency)


# Print status for a dependency
macro(print_dependency package)
    if(NOT YARP_USE_${package})
        message(STATUS "${package}: disabled")
    elseif(NOT YARP_USE_SYSTEM_${package})
        message(STATUS "${package}: compiling")
    elseif(${package}_FOUND)
        message(STATUS "${package}: found")
    else(NOT YARP_USE_${package})
        message(STATUS "${package}: not found")
    endif(NOT YARP_USE_${package})

    if (NOT YARP_HAS_${package} AND YARP_USE_${package})
        message("Warning: you requested to use the package ${package}, but it is unavailable (or was not found). This might lead to compile errors, we recommend you turn off the YARP_USE_${package} flag.")
    endif (NOT YARP_HAS_${package} AND YARP_USE_${package})
endmacro(print_dependency)



# OPTIONS:

option(CREATE_YMANAGER "Do you want to compile Yarp module manager?" ON)
option(CREATE_GUIS "Do you want to compile GUIs" OFF)

if(CREATE_GUIS)
    option(CREATE_YARPVIEW "Do you want to compile yarpview?" ON)
    option(CREATE_GYARPMANAGER "Do you want to compile gyarpmanager?" ON)
    option(CREATE_YARPSCOPE "Do you want to create yarpscope?" OFF)
else(CREATE_GUIS)
    unset(CREATE_YARPVIEW CACHE)
    unset(CREATE_GYARPMANAGER CACHE)
    unset(CREATE_YARPSCOPE CACHE)
endif(CREATE_GUIS)

message(STATUS "Detecting required libraries")
message(STATUS "CMake modules directory: ${CMAKE_MODULE_PATH}")


# FIND PACKAGES:

find_package(SQLite QUIET)
checkbuildandset_dependency(SQLite)

if(CREATE_YMANAGER OR CREATE_YARPSCOPE)
    find_package(TinyXML QUIET)
    checkbuildandset_dependency(TinyXML)
endif(CREATE_YMANAGER OR CREATE_YARPSCOPE)

if(CREATE_GUIS)
    find_package(Gthread QUIET)
    checkandset_dependency(Gthread)

    if(YARP_USE_GTK2)
        if(CREATE_YARPSCOPE)
            find_package(GTK2 2.20 COMPONENTS gtk gtkmm QUIET)
        elseif(CREATE_GYARPMANAGER)
            find_package(GTK2 2.8 COMPONENTS gtk gtkmm QUIET)
        elseif(CREATE_YARPVIEW)
            find_package(GTK2 2.8 COMPONENTS gtk QUIET)
        endif(CREATE_YARPSCOPE)

        checkandset_dependency(GTK2)

    else(YARP_USE_GTK2)
        find_package(GtkPlus QUIET)
        checkandset_dependency(GtkPlus)
        if(CREATE_YARPSCOPE OR CREATE_GYARPMANAGER)
            find_package(GtkMM QUIET)
            checkandset_dependency(GtkMM)
        endif(CREATE_YARPSCOPE OR CREATE_GYARPMANAGER)
    endif(YARP_USE_GTK2)
endif(CREATE_GUIS)

if(CREATE_YARPSCOPE)
    find_package(GtkDatabox QUIET)
    checkbuildandset_dependency(GtkDatabox)
    find_package(GtkDataboxMM QUIET)
    checkbuildandset_dependency(GtkDataboxMM)
endif(CREATE_YARPSCOPE)


# CHECK DEPENDENCIES:

check_required_dependency(SQLite)
check_optional_dependency(CREATE_YMANAGER TinyXML)
check_optional_dependency(CREATE_YARPSCOPE TinyXML)
check_optional_dependency(CREATE_GUIS Gthread)

if(YARP_USE_GTK2)
    check_optional_dependency(CREATE_GUIS GTK2)
else(YARP_USE_GTK2)
    check_optional_dependency(CREATE_YARPVIEW GtkPlus)
    check_optional_dependency(CREATE_GYARPMANAGER GtkPlus)
    check_optional_dependency(CREATE_GYARPMANAGER GtkMM)
    check_optional_dependency(CREATE_YARPSCOPE GtkPlus)
    check_optional_dependency(CREATE_YARPSCOPE GtkMM)
endif(YARP_USE_GTK2)

check_optional_dependency(CREATE_YARPSCOPE GtkDatabox)
check_optional_dependency(CREATE_YARPSCOPE GtkDataboxMM)


# PRINT DEPENDENCIES STATUS:

message(STATUS "I have found the following libraries:")

print_dependency(SQLite)
print_dependency(TinyXML)
print_dependency(Gthread)

if(YARP_USE_GTK2)
    print_dependency(GTK2)
else(YARP_USE_GTK2)
    print_dependency(GtkPlus)
    print_dependency(GtkMM)
endif(YARP_USE_GTK2)

print_dependency(GtkDatabox)
print_dependency(GtkDataboxMM)

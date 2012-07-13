# TinyXML
option(YARP_USE_SYSTEM_TINYXML "Use system TinyXML library" OFF)

if(CREATE_YMANAGER OR CREATE_YARPSCOPE)
    if(YARP_USE_SYSTEM_TINYXML)
        find_package(TinyXML REQUIRED)
    else(YARP_USE_SYSTEM_TINYXML)
        add_subdirectory(tinyxml)
    endif(YARP_USE_SYSTEM_TINYXML)
endif(CREATE_YMANAGER OR CREATE_YARPSCOPE)

if(CREATE_GUIS)
    # Gtk2
    option(YARP_USE_GTK2 FALSE "Use official CMake GTK2 find scripts, rather than homebrewed scripts")
    if(YARP_USE_GTK2)
        find_package(GTK2 2.8 COMPONENTS gtk gtkmm)
    else(YARP_USE_GTK2)
        find_package(GtkPlus REQUIRED)
    endif(YARP_USE_GTK2)


    # Gthread
    find_package(Gthread REQUIRED)


    # GtkMM
    find_package(GtkMM REQUIRED)


    if (CREATE_YARPSCOPE)
        # GtkDatabox
        option(YARP_USE_SYSTEM_GTKDATABOX "Use system GtkDatabox library" OFF)

        if(YARP_USE_SYSTEM_GTKDATABOX)
            find_package(GtkDatabox REQUIRED)
        else(YARP_USE_SYSTEM_GTKDATABOX)
            add_subdirectory(gtkdatabox)
        endif(YARP_USE_SYSTEM_GTKDATABOX)


        # GtkDataboxMM
        option(YARP_USE_SYSTEM_GTKDATABOXMM "Use system GtkDataboxMM library" OFF)

        if(YARP_USE_SYSTEM_GTKDATABOXMM)
            find_package(GtkDataboxMM REQUIRED)
        else(YARP_USE_SYSTEM_GTKDATABOXMM)
            add_subdirectory(gtkdataboxmm)
        endif(YARP_USE_SYSTEM_GTKDATABOXMM)
    endif (CREATE_YARPSCOPE)
endif(CREATE_GUIS)
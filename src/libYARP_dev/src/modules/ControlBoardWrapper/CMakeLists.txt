# use PARENT_SCOPE to make the following variables available at the 'parent' cmake

# Test using yarp_add_idl
include(YarpIDL)

# message("msg folder is ${yarp_msgs_SOURCE_DIR}")
# set(IDL_FILES_2 ${yarp_msgs_SOURCE_DIR}/ros/msg_file/robotology_msgs/controlBoardMsg.msg)
# yarp_add_idl(IDL_GEN_FILES_2 ${IDL_FILES_2})
#
# message("generated files ares ${IDL_GEN_FILES_2}")


set(cbw2_core_srcs      src/modules/ControlBoardWrapper/ControlBoardWrapper.cpp
                        src/modules/ControlBoardWrapper/RPCMessagesParser.cpp
                        src/modules/ControlBoardWrapper/StreamingMessagesParser.cpp
                        src/modules/ControlBoardWrapper/ROSCmdMessagesParser.cpp
                        src/modules/ControlBoardWrapper/SubDevice.cpp
                        PARENT_SCOPE)

set(cbw2_core_hrds      src/modules/ControlBoardWrapper/ControlBoardWrapper.h
                        src/modules/ControlBoardWrapper/RPCMessagesParser.h
                        src/modules/ControlBoardWrapper/StreamingMessagesParser.h
                        src/modules/ControlBoardWrapper/ROSCmdMessagesParser.h
                        src/modules/ControlBoardWrapper/SubDevice.h
                        src/modules/ControlBoardWrapper/yarpRosHelper.h
                        ${IDL_GEN_FILES_2}
                        PARENT_SCOPE)


set(cbw2_core_incl_dirs ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

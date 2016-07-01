/*
* Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
* Author: Alberto Cardellino
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*/

#ifndef YARP_DEV_CONTROLBOARDWRAPPER_ROSCMDMESSAGEPARSER_H
#define YARP_DEV_CONTROLBOARDWRAPPER_ROSCMDMESSAGEPARSER_H


// This file contains an helper class parsing ROS cmd messages and calling
// the correct wrapper function to execute the command
//
// N.B.: this parser goes in parallel with yarp one so commands from both sources
// can conflict which each other (but the same happen when receiving commands from
// two different applications on the same port)
//

// #include <yarp/os/PortablePair.h>
// #include <yarp/os/BufferedPort.h>
// #include <yarp/os/Time.h>
// #include <yarp/os/Network.h>
// #include <yarp/os/RateThread.h>
// #include <yarp/os/Stamp.h>
// #include <yarp/os/Vocab.h>

// #include <yarp/dev/ControlBoardInterfaces.h>
// #include <yarp/dev/PolyDriver.h>
// #include <yarp/dev/ControlBoardInterfacesImpl.h>
// #include <yarp/dev/PreciselyTimed.h>
// #include <yarp/sig/Vector.h>
// #include <yarp/os/Semaphore.h>
// #include <yarp/dev/Wrapper.h>

#include <yarp/os/PortReader.h>
#include "ControlBoardWrapper.h"
#include <robotology_msgs_controlBoardMsg.h>


#include <string>
#include <vector>

#ifdef MSVC
    #pragma warning(disable:4355)
#endif

/*
 * To optimize memory allocation, for group of joints we can have one mem reserver for rpc port
 * and on e for streaming. The size could be numOfSubDevices*maxNumOfjointForSubdevice.
 * (we could also use the actual joint number for each subdevice using a for loop). TODO
 */

/* Using yarp::dev::impl namespace for all helper class inside yarp::dev to reduce
 * name conflicts
 */

namespace yarp {
    namespace dev {
        class ControlBoardWrapper;
        namespace impl {
            class ROSCmdMessagesParser;
        }
    }
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS


/**
* Callback implementation after buffered input.
*/
class  yarp::dev::impl::ROSCmdMessagesParser :  public yarp::os::PortReader
{
protected:
    yarp::dev::IPositionControl2    *stream_IPosCtrl2;
    yarp::dev::IPositionDirect      *stream_IPosDirect;
    yarp::dev::IVelocityControl2    *stream_IVel2;
    yarp::dev::IOpenLoopControl     *stream_IOpenLoop;
    yarp::dev::ITorqueControl       *stream_ITorque;
    int                              joint_num;

public:
    /**
    * Constructor.
    */
    ROSCmdMessagesParser();

    virtual bool read(yarp::os::ConnectionReader& connection);

    /**
    * Initialization.
    * @param x is the instance of the container class using the callback.
    */
    bool initialize(yarp::dev::ControlBoardWrapper *x);

private:

    std::map<std::string, int>          jointMap;
    robotology_msgs_controlBoardMsg     inputMsg;


    bool inputMsgIsValid();
};


#endif // DOXYGEN_SHOULD_SKIP_THIS

#endif  //YARP_DEV_CONTROLBOARDWRAPPER_ROSCMDMESSAGEPARSER_H

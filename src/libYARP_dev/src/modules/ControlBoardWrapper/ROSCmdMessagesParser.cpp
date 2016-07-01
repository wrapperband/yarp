/*
 * Copyright (C) 2009 RobotCub Consortium
 * Author: Lorenzo Natale
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#include <stdexcept>      // std::out_of_range

#include "ControlBoardWrapper.h"
#include "ROSCmdMessagesParser.h"
#include <iostream>
#include <yarp/os/Log.h>
#include <yarp/os/LogStream.h>

using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::dev::impl;
using namespace yarp::sig;
using namespace std;


ROSCmdMessagesParser::ROSCmdMessagesParser() : joint_num(0) {}

bool ROSCmdMessagesParser::inputMsgIsValid()
{
    // TBD: this function should either be mutexed or have the input msg
    // as a parameter.

    // collect here all checks for a valid input message
    size_t cmdLenght = inputMsg.names.size();
    if( cmdLenght <= 0)
    {
        yError() << "Input message has mandatory field 'names' missing";
        return false;
    }

    if( inputMsg.reference.size() <= 0)
    {
        yError() << "Input message has mandatory field 'reference' missing. Name size is " << cmdLenght << " while cmd lenght is " << inputMsg.reference.size();
        return false;
    }

    if( cmdLenght != inputMsg.reference.size())
    {
        yError() << "Input message has fields 'names' and 'reference' of different sizes";
        return false;
    }
    return true;
}

bool ROSCmdMessagesParser::read(yarp::os::ConnectionReader& connection)
{
    inputMsg.read(connection);

    if(!inputMsgIsValid())
    {
        yTrace() << "\n\tCallback read failed because input ROS msg was not valid";
        return false;
    }

    int cmdLenght = inputMsg.names.size();

    // process data in inputMsg
    printf("-------------------------------\nGot\n");
    printf("Size of name %d\n", cmdLenght);

    int _j;
    for(int i=0; i<cmdLenght; i++)
    {
        try
        {
            _j = jointMap.at(inputMsg.names[i]);
        }
        catch (const std::out_of_range & oor)
        {
            yError() << "Non existing joint " << inputMsg.names[i] << " found at index " << i << " of the input ROS msg";
            continue;
        }

        printf("Mode %d\n", inputMsg.referenceType[i]);
        printf("Name %s  --[%d]\n", inputMsg.names[i].c_str(), _j);
        printf("Comm %f\n", inputMsg.reference[_j]);
        stream_IPosCtrl2->positionMove(_j, inputMsg.reference[i] * 180/3.14);
    }

    return true;
}


bool ROSCmdMessagesParser::initialize(ControlBoardWrapper *x)
{
    stream_IPosCtrl2    = dynamic_cast<yarp::dev::IPositionControl2 *> (x);
    stream_IPosDirect   = dynamic_cast<yarp::dev::IPositionDirect *> (x);
    stream_IVel2        = dynamic_cast<yarp::dev::IVelocityControl2 *> (x);
    stream_IOpenLoop    = dynamic_cast<yarp::dev::IOpenLoopControl *> (x);
    stream_ITorque      = dynamic_cast<yarp::dev::ITorqueControl *> (x);

    if( ! (stream_IPosCtrl2 && stream_IVel2 && stream_IPosDirect && stream_IOpenLoop && stream_ITorque))
    {
      yError() << "Internal error while opening ControlBoardWrapper device. \n\t"\
                   "Adv: ROSCmdMessagesParser initialize(...) failed to get the required interfaces.";
      return false;
    }
    // so far so good
    if(! stream_IPosCtrl2->getAxes(&joint_num))
    {
        if(joint_num <= 0)
            yError() << "Internal error while opening ControlBoardWrapper device. \n\t" \
                        "Adv: ROSCmdMessagesParser initialize(...) failed to get the number of joints.";
        return false;
    }

    std::pair<std::map<std::string, int>::iterator,bool> ret;

    int joint_num;
    x->getAxes(&joint_num);
    ConstString name;

    yError() << "joint num :" << joint_num;
    for(int _j=0; _j<joint_num; _j++)
    {
        x->getAxisName(_j, name);
        ret = jointMap.insert(std::pair<std::string, int>(name, _j) );
        if (ret.second == false)
        {
            yError() << "element " << name <<  " already existed";
        }
        else
            yError() << "added element " << name <<  " at index " << _j;
    }
    return true;
}


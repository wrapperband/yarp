// This is an automatically generated file.
// Generated from this robotology_msgs_controlBoardMsg.msg definition:
//   # Reference types
//   int32 POSITION_TARGET=1
//   int32 POSITION_DIRECT=2
//   int32 POSITION_RELATIVE=3
//   int32 VELOCITY_CMD=4
//   int32 TORQUE_CMD=5
//   
//   # Standard ROS msg header
//   Header header
//   
//   # All fields must have the same size of joint names.
//   # Optional fileds must either be missing or same size.
//   
//   # Mandatory
//   string[]  names
//   
//   # Mandatory field, it must be one value from the above list of 'Reference types'
//   int32[] referenceType
//   
//   # Mandatory: this is the main reference value of the type specified
//   float64[] reference
//   
//   # Optional: this is the derivative of the main reference, for example if
//   # cmd type is a position, this will be the velocity, while if the command
//   # is velocity this will be reference for the acceleration. It is not defined
//   # for POSITION_DIRECT and TORQUE_CMD
//   float64[] reference_dot
//   
//   # Do we need the second derivative to send acceleration references in position
//   # mode? The ROS msg trajectory_msgs/JointTrajectoryPoint do takes into consideration
//   # acceleration values for each 'step target' in the trajectory.
//   # float64[] reference_dot_dot
//   
//   # Optional: Some control type may accept a torque feedforward value.
//   float64[] torque_offset
//   
//   # TBD: find a way to define gains in such a way to accomodate
//   # at least a few possible different combination of gains used
//   # and YARP way of handling them.
//   
//   # Gains[] gains_joint
//   #
//   # Where Gains is
//   # Kp
//   # Ki
//   # Kd
//   # stiffness
//   # damping
//   #
//   # custom   --> map as <string, value(s)>
//   #
//   #
//   # The first part is quite standard and can be mapped into YARP
//   # intrefaces. The only doubt is about which PID shall be set?
//   # Position, Vel or Torque? Can it be choosen by looking at cmdType?
//   # The three version of position command will change the same PID,
//   # is it clear or may the user expect different behaviour?
//   #
//   # The custom part could go into a separated interface and passed to
//   # the low-level device untouched (just converting data into a Bottle
//   # or Property type) and let the hw device handle them.
//   #
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_robotology_msgs_controlBoardMsg
#define YARPMSG_TYPE_robotology_msgs_controlBoardMsg

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "TickTime.h"
#include "std_msgs_Header.h"

class robotology_msgs_controlBoardMsg : public yarp::os::idl::WirePortable {
public:
  static const yarp::os::NetInt32 POSITION_TARGET = 1;
  static const yarp::os::NetInt32 POSITION_DIRECT = 2;
  static const yarp::os::NetInt32 POSITION_RELATIVE = 3;
  static const yarp::os::NetInt32 VELOCITY_CMD = 4;
  static const yarp::os::NetInt32 TORQUE_CMD = 5;
  std_msgs_Header header;
  std::vector<std::string> names;
  std::vector<yarp::os::NetInt32> referenceType;
  std::vector<yarp::os::NetFloat64> reference;
  std::vector<yarp::os::NetFloat64> reference_dot;
  std::vector<yarp::os::NetFloat64> torque_offset;

  robotology_msgs_controlBoardMsg() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** header ***
    if (!header.read(connection)) return false;

    // *** names ***
    int len = connection.expectInt();
    names.resize(len);
    for (int i=0; i<len; i++) {
      int len2 = connection.expectInt();
      names[i].resize(len2);
      if (!connection.expectBlock((char*)names[i].c_str(),len2)) return false;
    }

    // *** referenceType ***
    len = connection.expectInt();
    referenceType.resize(len);
    if (!connection.expectBlock((char*)&referenceType[0],sizeof(yarp::os::NetInt32)*len)) return false;

    // *** reference ***
    len = connection.expectInt();
    reference.resize(len);
    if (!connection.expectBlock((char*)&reference[0],sizeof(yarp::os::NetFloat64)*len)) return false;

    // *** reference_dot ***
    len = connection.expectInt();
    reference_dot.resize(len);
    if (!connection.expectBlock((char*)&reference_dot[0],sizeof(yarp::os::NetFloat64)*len)) return false;

    // *** torque_offset ***
    len = connection.expectInt();
    torque_offset.resize(len);
    if (!connection.expectBlock((char*)&torque_offset[0],sizeof(yarp::os::NetFloat64)*len)) return false;
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(11)) return false;

    // *** header ***
    if (!header.read(connection)) return false;

    // *** names ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_STRING)) return false;
    int len = connection.expectInt();
    names.resize(len);
    for (int i=0; i<len; i++) {
      int len2 = connection.expectInt();
      names[i].resize(len2);
      if (!connection.expectBlock((char*)names[i].c_str(),len2)) return false;
    }

    // *** referenceType ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_INT)) return false;
    len = connection.expectInt();
    referenceType.resize(len);
    for (int i=0; i<len; i++) {
      referenceType[i] = (yarp::os::NetInt32)connection.expectInt();
    }

    // *** reference ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE)) return false;
    len = connection.expectInt();
    reference.resize(len);
    for (int i=0; i<len; i++) {
      reference[i] = (yarp::os::NetFloat64)connection.expectDouble();
    }

    // *** reference_dot ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE)) return false;
    len = connection.expectInt();
    reference_dot.resize(len);
    for (int i=0; i<len; i++) {
      reference_dot[i] = (yarp::os::NetFloat64)connection.expectDouble();
    }

    // *** torque_offset ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE)) return false;
    len = connection.expectInt();
    torque_offset.resize(len);
    for (int i=0; i<len; i++) {
      torque_offset[i] = (yarp::os::NetFloat64)connection.expectDouble();
    }
    return !connection.isError();
  }

  using yarp::os::idl::WirePortable::read;
  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** header ***
    if (!header.write(connection)) return false;

    // *** names ***
    connection.appendInt(names.size());
    for (size_t i=0; i<names.size(); i++) {
      connection.appendInt(names[i].length());
      connection.appendExternalBlock((char*)names[i].c_str(),names[i].length());
    }

    // *** referenceType ***
    connection.appendInt(referenceType.size());
    connection.appendExternalBlock((char*)&referenceType[0],sizeof(yarp::os::NetInt32)*referenceType.size());

    // *** reference ***
    connection.appendInt(reference.size());
    connection.appendExternalBlock((char*)&reference[0],sizeof(yarp::os::NetFloat64)*reference.size());

    // *** reference_dot ***
    connection.appendInt(reference_dot.size());
    connection.appendExternalBlock((char*)&reference_dot[0],sizeof(yarp::os::NetFloat64)*reference_dot.size());

    // *** torque_offset ***
    connection.appendInt(torque_offset.size());
    connection.appendExternalBlock((char*)&torque_offset[0],sizeof(yarp::os::NetFloat64)*torque_offset.size());
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(11);

    // *** header ***
    if (!header.write(connection)) return false;

    // *** names ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_STRING);
    connection.appendInt(names.size());
    for (size_t i=0; i<names.size(); i++) {
      connection.appendInt(names[i].length());
      connection.appendExternalBlock((char*)names[i].c_str(),names[i].length());
    }

    // *** referenceType ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_INT);
    connection.appendInt(referenceType.size());
    for (size_t i=0; i<referenceType.size(); i++) {
      connection.appendInt((int)referenceType[i]);
    }

    // *** reference ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE);
    connection.appendInt(reference.size());
    for (size_t i=0; i<reference.size(); i++) {
      connection.appendDouble((double)reference[i]);
    }

    // *** reference_dot ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE);
    connection.appendInt(reference_dot.size());
    for (size_t i=0; i<reference_dot.size(); i++) {
      connection.appendDouble((double)reference_dot[i]);
    }

    // *** torque_offset ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE);
    connection.appendInt(torque_offset.size());
    for (size_t i=0; i<torque_offset.size(); i++) {
      connection.appendDouble((double)torque_offset[i]);
    }
    connection.convertTextMode();
    return !connection.isError();
  }

  using yarp::os::idl::WirePortable::write;
  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<robotology_msgs_controlBoardMsg> rosStyle;
  typedef yarp::os::idl::BottleStyle<robotology_msgs_controlBoardMsg> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "# Reference types\n\
int32 POSITION_TARGET=1\n\
int32 POSITION_DIRECT=2\n\
int32 POSITION_RELATIVE=3\n\
int32 VELOCITY_CMD=4\n\
int32 TORQUE_CMD=5\n\
\n\
# Standard ROS msg header\n\
Header header\n\
\n\
# All fields must have the same size of joint names.\n\
# Optional fileds must either be missing or same size.\n\
\n\
# Mandatory\n\
string[]  names\n\
\n\
# Mandatory field, it must be one value from the above list of 'Reference types'\n\
int32[] referenceType\n\
\n\
# Mandatory: this is the main reference value of the type specified\n\
float64[] reference\n\
\n\
# Optional: this is the derivative of the main reference, for example if\n\
# cmd type is a position, this will be the velocity, while if the command\n\
# is velocity this will be reference for the acceleration. It is not defined\n\
# for POSITION_DIRECT and TORQUE_CMD\n\
float64[] reference_dot\n\
\n\
# Do we need the second derivative to send acceleration references in position\n\
# mode? The ROS msg trajectory_msgs/JointTrajectoryPoint do takes into consideration\n\
# acceleration values for each 'step target' in the trajectory.\n\
# float64[] reference_dot_dot\n\
\n\
# Optional: Some control type may accept a torque feedforward value.\n\
float64[] torque_offset\n\
\n\
# TBD: find a way to define gains in such a way to accomodate\n\
# at least a few possible different combination of gains used\n\
# and YARP way of handling them.\n\
\n\
# Gains[] gains_joint\n\
#\n\
# Where Gains is\n\
# Kp\n\
# Ki\n\
# Kd\n\
# stiffness\n\
# damping\n\
#\n\
# custom   --> map as <string, value(s)>\n\
#\n\
#\n\
# The first part is quite standard and can be mapped into YARP\n\
# intrefaces. The only doubt is about which PID shall be set?\n\
# Position, Vel or Torque? Can it be choosen by looking at cmdType?\n\
# The three version of position command will change the same PID,\n\
# is it clear or may the user expect different behaviour?\n\
#\n\
# The custom part could go into a separated interface and passed to\n\
# the low-level device untouched (just converting data into a Bottle\n\
# or Property type) and let the hw device handle them.\n\
#\n================================================================================\n\
MSG: std_msgs/Header\n\
[std_msgs/Header]:\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data\n\
# in a particular coordinate frame.\n\
#\n\
# sequence ID: consecutively increasing ID\n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("robotology_msgs/controlBoardMsg","robotology_msgs/controlBoardMsg");
    typ.addProperty("md5sum",yarp::os::Value("031b5c241460e256ce875fb257ad61e4"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif

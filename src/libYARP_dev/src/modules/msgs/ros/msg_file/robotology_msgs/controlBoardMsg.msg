# Reference types
int32 POSITION_TARGET=1
int32 POSITION_DIRECT=2
int32 POSITION_RELATIVE=3
int32 VELOCITY_CMD=4
int32 TORQUE_CMD=5

# Standard ROS msg header
Header header

# All fields must have the same size of joint names.
# Optional fileds must either be missing or same size.

# Mandatory
string[]  names

# Mandatory field, it must be one value from the above list of 'Reference types'
int32[] referenceType

# Mandatory: this is the main reference value of the type specified
float64[] reference

# Optional: this is the derivative of the main reference, for example if
# cmd type is a position, this will be the velocity, while if the command
# is velocity this will be reference for the acceleration. It is not defined
# for POSITION_DIRECT and TORQUE_CMD
float64[] reference_dot

# Do we need the second derivative to send acceleration references in position
# mode? The ROS msg trajectory_msgs/JointTrajectoryPoint do takes into consideration
# acceleration values for each 'step target' in the trajectory.
# float64[] reference_dot_dot

# Optional: Some control type may accept a torque feedforward value.
float64[] torque_offset

# TBD: find a way to define gains in such a way to accomodate
# at least a few possible different combination of gains used
# and YARP way of handling them.

# Gains[] gains_joint
#
# Where Gains is
# Kp
# Ki
# Kd
# stiffness
# damping
#
# custom   --> map as <string, value(s)>
#
#
# The first part is quite standard and can be mapped into YARP
# intrefaces. The only doubt is about which PID shall be set?
# Position, Vel or Torque? Can it be choosen by looking at cmdType?
# The three version of position command will change the same PID,
# is it clear or may the user expect different behaviour?
#
# The custom part could go into a separated interface and passed to
# the low-level device untouched (just converting data into a Bottle
# or Property type) and let the hw device handle them.
#

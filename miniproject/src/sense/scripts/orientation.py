#!/usr/bin/env python

import roslib
import rospy
import geometry_msgs.msg
from nav_msgs.msg import Odometry
from std_msgs.msg import Float32
from geometry_msgs.msg import PointStamped
z=0
w=0
command=PointStamped()

pub = rospy.Publisher('xy_position_data', PointStamped, queue_size=10)
def orientation ():
	
	
	rospy.init_node("orientation")
	rate=rospy.Rate(10)
	rospy.Subscriber("/odom", Odometry, Callback)
		

	rospy.spin()

def Callback (data):
	global left
	global right
	z=float(data.pose.pose.position.x)
	w=float(data.pose.pose.position.y)
	rospy.loginfo("Orientation_sensor_1= %s", z)
	rospy.loginfo("Orientation_sensor_2= %s", w)
	command.point.x=w
	command.point.y=z
	command.header.stamp=rospy.Time.now()
	pub.publish(command)

if __name__=='__main__':
	orientation()

#!/usr/bin/env python

import roslib
import rospy
import geometry_msgs.msg
from sensor_msgs.msg import LaserScan
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32
from geometry_msgs.msg import PointStamped
import math
x=1
n=float('nan')
command = PointStamped()
pub = rospy.Publisher('kinect_data', PointStamped, queue_size=10)

def obstacle ():

	rospy.init_node("obstacle")
	rospy.Subscriber("/scan", LaserScan, Callback)
	
	rospy.spin()

def Callback (data):
	l=data.ranges
	obstacol=0
	rospy.loginfo("stanga= %s", l[40])
	rospy.loginfo("centru= %s", l[20])
	rospy.loginfo("dreapta= %s", l[0])
	command.point.x=l[0]
	command.point.y=l[20]
	command.point.z=l[40]
	command.header.stamp=rospy.Time.now()
	pub.publish(command)

if __name__=='__main__':
	obstacle()

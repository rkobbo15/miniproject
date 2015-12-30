#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Twist

angular=0
linear=0
move_cmd=Twist()
cmd_vel=rospy.Publisher('cmd_vel_mux/input/navi', Twist, queue_size=1)
def lamove ():

	global linear
	global angular

	rospy.init_node('lamove', anonymous=True)
	
	

	

	

	rospy.Subscriber("move_data", Float32MultiArray, callback)
		
	

	rospy.loginfo ("Linear_speed= %s", str(linear))
	rospy.loginfo ("Angular_speed= %s", str(angular))	
	
	rospy.spin ()
	
def callback (data):
	

	r=rospy.Rate(10)
	global linear
	global angular
	i=data.data
	rospy.loginfo ("Linear_speed= %s", str(data.data))
	linear=i[0]
	angular=i[1]
	move_cmd.linear.x=linear
	move_cmd.angular.z=angular
	cmd_vel.publish(move_cmd)
	r.sleep()

if __name__=='__main__':
	lamove()

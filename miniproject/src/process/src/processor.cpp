#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include "geometry_msgs/PointStamped.h"
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace std;
using namespace message_filters;
using namespace geometry_msgs;


std_msgs::Float32MultiArray mot;
ros::Subscriber sub;
ros::Publisher pub;

float detect, angular, linear, left1, center1, right1, t, x, lefti, centeri, righti;
int  init=0, position=1, step=0;
bool moving=true;


void move (float lin, float ang)
{
	mot.data.clear();
	mot.data.push_back(lin);
	mot.data.push_back(ang);
	pub.publish(mot);
}

void callback (const geometry_msgs::PointStamped::ConstPtr& orient_data, const geometry_msgs::PointStamped::ConstPtr& obst_data)
{
	ros::Rate r(5);
	ros::Rate l(5);
	
	right1=obst_data->point.x;
	center1=obst_data->point.y;
	left1=obst_data->point.z;
	
	

	if (orient_data->point.x<9.1)
	{
		if (init==0)
		{	
			step=0;
			init=1;
			lefti=left1;
			righti=right1;
			centeri=center1;
		}


		if (left1<1 )
		{	
			step=0;	
			move (0.2, 13*(lefti-left1));
			x=t;
			cout << "Runing along the wall!" << endl;
		}
	
		else 
		{
			move (0.2, x*(lefti-left1));
			x=x+0.01;
			step++;
			cout << "Turning!" << endl;
			if (step>400)
			{
				cout << "Turning fast!" << endl;
				x=x+0.5;
			}
			if (step >500)
			{
				x=x+0.7;
				cout << "Turning very fast!!!" << endl;
			}
		}
	}
	else
	{
		move (0, 0);
		cout << "Out of the maze!" << endl;
	}			
	
}
int main (int argc, char **argv)
{
	
	
	t=0.05;
	ros::init(argc, argv, "processor");
	ros::NodeHandle n;
	pub = n.advertise < std_msgs::Float32MultiArray>("move_data", 10);

	message_filters::Subscriber<geometry_msgs::PointStamped> position (n, "xy_position_data", 1);
	message_filters::Subscriber<geometry_msgs::PointStamped> wall (n, "kinect_data", 1);

	typedef sync_policies::ApproximateTime<PointStamped, PointStamped> MySyncPolicy;
        Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), position, wall);
        sync.registerCallback(boost::bind(&callback, _1, _2));
	
	ros::spin(); 
	return 0;

}

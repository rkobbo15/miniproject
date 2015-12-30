# miniproject

1) start up the stage program (turtlebot simulator, you will use the window which has the question mark as an icon, rviz is not working well) with the command: roslaunch turtlebot_stage turtlebot_in_stage.launch (more info here: http://wiki.ros.org/turtlebot_simulator )
2) let the simulator load all the files
3) start the mazesolver program (I don’t know for sure if these are still the names, they are the same with the P1, put them more suggestive names):
rosrun sense orientation.py (will open the node which will publish the location of the robot, when it will hit the value 9 on the y axis, it means that it solved the maze)
rosrun sense obstacle.py (will open the node which will publish the some data received from the kinect. This node receives an array from the kinect, but it only needs to publish the elements 0, 20 and 40. I did this to keep it simple, we don’t need 2d scanning, we want only the distance between the robot and the wall)
rosrun move lamove.py (will open the node in charge with movement, same as P1)
rosrun process processor (will open the processor node)
4) That’s it, the robot will solve the maze.

# RT_1-ASSIGNMENT_2 
Presented by Furqan Ansari, Masters student of the Robotics in universty of genoa
Email:furqan.ali7861@gmail.com

This second assignment of research_track_1 and is about the use of a robot simulator in ROS, in this project a simple robot autonomously travels a track of the Monza racing circuit without hiting the walls of the track.


## **_THE GIVEN ENVIROMENT TO THE ROBOT_**

this the track given to robot in which to robot have to move and complete the track  without tocuhing the walls of the track.

![Capture](https://user-images.githubusercontent.com/105802251/169619130-c667bb44-42b0-4946-af01-1dd7def4a5cf.PNG)


in the track there are some sharp turns that the robot have to cover those turns, and those turns and detacted by the safety distance ( **float d_th = 1.0** ) .

 
 ## Installing And Running 
 The simulator requires ROS ( Robot Operating System ),Once you have installed ROS and created your workspace you have to download the package **second_assignment** in the **src** folder of your workspace. 
 Then run the launch file that:**roslaunch second_assignment second_assignment.launch** 
 the launch file will run the multiple node and same time for the user to make the thnig easer. 

## Implimation of the ASSIGNMENT( NODES )
In this Assignment two nodes are used ( controller.cpp & interface.cpp ) and server along with the  stage_ros simulator(Which was provided by the professor).

**stageros node (stage_ros package)**

The stageros node wraps the Stage 2-D multi-robot simulator, via libstage. Stage simulates a world as defined in a .world file. This file tells stage everything about the world, from obstacles (usually represented via a bitmap to be used as a kind of background), to robots and other objects. The nodes has the following properties:

__Subscriptions__

 * The node subscribes to the cmd_vel (geometry_msgs/Twist) topic, to manage the velocity of the robot.

__Publishing__

* odom (nav_msgs/Odometry): odometry data of the model.
* base_scan (sensor_msgs/LaserScan): scans from the laser model. We will use this one.
* base_pose_ground_truth (nav_msgs/Odometry): the ground truth pose. We will use this one.
* image (sensor_msgs/Image): visual camera image.
* depth (sensor_msgs/Image): depth camera image.
* camera_info (sensor_msgs/CameraInfo): camera calibration info.

The odom topic gives simulated odometry, which is affected by settings in the .world file, which can change its origin and noise model see the Stage documentation for details on changing this behavior. The base_pose_ground_truth topic always provides a perfect, globally referenced pose for the robot in the simulation, independent of .world file settings. The base_pose_ground_truth data is intended for testing purposes; it should not be used in robot control loops (because it's unrealistic).

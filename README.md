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

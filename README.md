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

## Controller

__controller_node__: it is created to Drive the robot without hitting itself into the walls of the track. It communicates with world through messages: it sends messages to impose the right speed on the robot and receives information regarding the position of the walls provided by the laser scanners with which the robot is equipped. In addition, it also offers a service that can change the speed of the robot according to the command received.

__Subscriptions__
base_scan (sensor_msgs/Laser_scan) 
which provides data about the laser that scans the surroundings of the robot to detect the wall and leter help  to make decision for the robot to avoid the wall.  
__Publishing__
cmd_vel geometry_msgs/Twist
which is the topic to change the linear and angular velocity's values of the robot.

**when the wall comes in the rage of front_minimum_distance,left_minimum_distance or right_minimum_distace the robot will make the decision to turn itself to avoid the walll and this is done by** :

float dist_min_right, dist_min_left, dist_min_front;	
	// array wich will be filled with the elements of ranges
	float scanner[721];
	
	// thanks to this loop scanner array is filled with the element of ranges
	for(int i = 0; i < 722; i++){
		scanner[i] = msg->ranges[i];
	}
	
	// Call at the Distance function to calculate the minimum
	// distance from the obstacles on robot front, right and left
	dist_min_right = dist(scanner, 0, 100);
	dist_min_left = dist(scanner, 620, 720);
	dist_min_front = dist(scanner, 300, 420);
	
	// As in the first assignment here is checked if we are close
	// to an obstacle on robot front and if so, we check if we are close
	// on the right or on the left, in order to turn the robot in the right
	// way
	if(dist_min_front < 1.5){
		if(dist_min_left > dist_min_right){
			vel.angular.z = 1.0;
			vel.linear.x = 0.3;
		}
		else if(dist_min_right > dist_min_left){
			vel.angular.z = -1.0;
			vel.linear.x = 0.3;
		}
	}
	
 
 **If there are no obstacles on robot front it continues straight**
	
 else{
		vel.linear.x = 1.0+acceleration;
		vel.angular.z = 0.0;
	}
	if(vel.linear.x <= 0){
		vel.linear.x = 0.0;
	}
		
	// here the velocity is published on 
		pub.publish(vel);
}

**the node also implementing  the  Server to receive the client request from the UI node**.
the controller node also the speed of the robot via the server 
It also implements the Service.srv: taking a command from the user, it decides what will be the velocity of the robot, taking in account min and max velocities.

bool serviceCallback (second_assignment::Service::Request &req, second_assignment::Service::Response &res)
{
	// Read actual velocity
	if(req.command == 'w' && velocity < max_vel)
	{
		// Increase velocity if velocity isn't maximal
		velocity += 1.0;
	}
	else if(req.command == 's' && velocity > min_vel)
	{
		// Decrease velocity if velocity isn't minimal
		velocity -= 1.0;
	}
	else if(req.command == 'r')
	{
		// Reset velocity to 1
		velocity = 1;
	}
        // Set service's output
	res.intial_velocity = velocity;

	return true;
}

This function also creates the server's response to the client's request; in particular, the response consists of the float containing the value of acceleration (the value of the global variable wich increment velocity).

## Interface
This  node represent the iterface of the project to user
 it communicates with both the nodes, server and controller. It get the input by the terminal and sends a request to the server, which will provide a response still to the UI node
 
   char key = 'r'; // Initialize the variable key

   //While the roscore is running, execute the loop
   while (ros::ok()) {

      scanf(" %c", &key); // Read command
      
      if(key == 'q')
      {
      	ros::shutdown();
      }
      else if ( key == 'w' || key == 's' || key == 'r') 
      {
         // Valid command received
         // Send a request to the service
         server_srv.request.command = key;
	 client_srv.waitForExistence();

         if ( client_srv.call(server_srv) ) 
         {

            if ( key == 'r' ) 
            {
            	// Reset invoked
               client_res.waitForExistence();
               client_res.call(server_res);
               printf("RESET\n");
            }
	    
	  __MANU__  
* w : increase speed
* s : decrease speed
* r : reset robot position
* q : quit

## SERVICE

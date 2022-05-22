/* Run with: $ roslaunch second_assignment second_assignment.launch */
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "second_assignment/Service.h"


ros::Publisher pub;

// Safety distance
float d_th = 1.0;
// Initial velocity
float velocity = 1.0;
// Set min and max values
float max_vel = 20;
float min_vel = 0;
// Define velocities for the curves
float angular_velocity = 1.5;
float linear_velocity = 0.5;
float acceleration = 1;

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
		// Increase velocity if velocity isn't minimal
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

float dist(float scan[], int min_sen, int max_sen)
{
	float min_dist = 100;
	for(int i= min_sen; i < max_sen; i++)
	{
		if(scan[i] < min_dist)
		{
			min_dist = scan[i];
		}
	}
	return min_dist;
}

void robotCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	geometry_msgs::Twist vel;


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
	
	// If there are no obstacles on robot front it continues straight
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


int main(int argc, char ** argv)
{
	ros::init(argc, argv, "robot_controller");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("/base_scan", 100, robotCallback);
	ros::ServiceServer service = n.advertiseService("/service", serviceCallback);

	pub = n.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);

	ros::spin();
	return 0;

}

#ifndef DRONE_VISION_H
#define DRONE_VISION_H

#include <ros/ros.h>

// ROS image
#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

// OpenCV
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sensor_msgs/Image.h>

#include <string>
#include <math.h>
#include <cmath>


static const std::string OPENCV_WINDOW = {"Image Callback"};
static const std::string OPENCV_TRES_WINDOW = {"Threshold Callback"};



class ImageConverter{

public:

	ImageConverter();

	~ImageConverter();

	// image callback from drone
	void imageCallback(const sensor_msgs::ImageConstPtr& source);



private:

		ros::NodeHandle nh_;

		// ROS publishers
    image_transport::ImageTransport it_;
		image_transport::Publisher image_pub_;
		// ROS subscribers
    image_transport::Subscriber image_sub_;

		// image callback
		cv_bridge::CvImagePtr cv_ptr;

};

#endif /* DRONE_VISION_H */

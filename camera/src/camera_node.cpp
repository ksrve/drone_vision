#include <ros/ros.h>

#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer

int main(int argc, char** argv)
{
  std::string file_path = "/home/ksrve/Downloads/polygon.png";
  // Check if video source has been passed as a parameter
  if((argv[2] == NULL) || (argv[2] == NULL)){
    std::cout << "Insert arguements" << std::endl;
    return 1;

  }

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh_;
  image_transport::ImageTransport it(nh_);
  image_transport::Publisher pub = it.advertise("camera/image_raw", 1);

  sensor_msgs::ImagePtr msg;
  cv::Mat frame;
  cv::Mat image;
  cv::VideoCapture capture;

  // Convert the passed as command line parameter index
  std::istringstream video_sourceCmd(argv[1]);
  std::istringstream typeCmd(argv[2]);
  int video_source;
  int type;
  // Check if it is indeed a number
  if(!(video_sourceCmd >> video_source)) return 1;
  if(!(typeCmd >> type)) return 1;


  ros::Rate loop_rate(50);

  if (type == 1){
    capture.open(video_source);
    // Check if video device can be opened with the given index
    if (capture.isOpened()){
      while (ros::ok()) {
        capture >> frame;
        // Check if grabbed frame is actually full with some content
        if(!frame.empty()) {
          msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
          pub.publish(msg);
          cv::waitKey(1);
        }
        ros::spinOnce();
        loop_rate.sleep();
      }
    }else{
        ROS_ERROR_STREAM("Cannot open camera: " << video_source);
        exit(0);
      }
    }

  if (type == 2){
    image = cv::imread(file_path);
    while (ros::ok()) {
      if(!image.empty()) {
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        pub.publish(msg);
        cv::waitKey(1);
      }else{
        ROS_ERROR_STREAM("Cannot open image: ");
        exit(0);
      }
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
}

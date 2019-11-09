#include <drone_vision.h>


using namespace std;

ImageConverter::ImageConverter():it_(nh_)
{
  // Subscrive to input video feed
  image_sub_ = it_.subscribe("/camera/image_raw", 1, &ImageConverter::imageCallback, this);
  cv::namedWindow(OPENCV_WINDOW);
}

ImageConverter::~ImageConverter()
{
  cv::destroyWindow(OPENCV_WINDOW);
}

void ImageConverter::imageCallback(const sensor_msgs::ImageConstPtr& source)
{

  try
  {
    cv_ptr = cv_bridge::toCvCopy(source, sensor_msgs::image_encodings::BGR8);
    cv::waitKey (30);
  } catch (cv_bridge::Exception& e)
  {

    std::cerr << "Could not convert image %s: " <<  e.what() << std::endl;
    return;
  }
  cv::imshow(OPENCV_WINDOW, cv_ptr->image);
  cv::waitKey(3);

}

#include <drone_vision.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "drone_vision");
  std::cout.flush();

  std::cout << "Starting Drone Vision Node..." << std::endl;

  ImageConverter ic;
  ros::spin();

  return 0;
}

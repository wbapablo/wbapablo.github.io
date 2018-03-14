
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

int main(int argc, char** argv){
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle n;
  image_transport::ImageTransport  it(n);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  VideoCapture cap(0);
  ros::Rate loop_rate(20);
  while (n.ok()) {
    Mat image;
    cap >> image;

    std::cout << image.size() << std::endl;
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(
                    std_msgs::Header(), "bgr8", image).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}

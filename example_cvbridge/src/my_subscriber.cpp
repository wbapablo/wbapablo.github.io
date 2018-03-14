
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <vector>

int  height = 376;
int width = 672;
cv::Mat kk;



int from_to[] = { 0,0 };



using namespace cv;

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
  try {

    kk = cv_bridge::toCvShare(msg, "bgr8")->image;

    cv::imshow("view", kk);
    cv::waitKey(1);

  }
  catch (cv_bridge::Exception& e) {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}
int main(int argc, char **argv){
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle n;
  cv::namedWindow("view");
  cv::startWindowThread();
  image_transport::ImageTransport it(n);
  image_transport::Subscriber sub = it.subscribe("/camera/image",1,imageCallback);
  ros::spin();
  cv::destroyWindow("view");
}

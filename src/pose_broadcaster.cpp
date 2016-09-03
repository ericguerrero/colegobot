#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


using namespace std;

class PoseTfBroadcaster
{
public:
    PoseTfBroadcaster(ros::NodeHandle nh);

protected:
    void odomCallback(const nav_msgs::OdometryConstPtr& odom);

private:
    // Handlers
    ros::NodeHandle nh_;

    //Subscribers
    ros::Subscriber sub_odom_;
    ros::Publisher pub_cameraPose_;

    // Operational variables
    bool tf_catched_;
    tf::TransformListener tf_listener_;
    tf::TransformBroadcaster tf_broadcaster_;

    // Node parameters
    string robot_frame_id_;
    string odom_frame_id_;
    string map_frame_id_;
    string camera_frame_id_;
    string camera_origin_frame_id_;

    // Static transforms
    tf::StampedTransform T_rob_cam_;
    tf::StampedTransform T_camO_cam_;
    tf::Transform T_map_camO_;
};

PoseTfBroadcaster::PoseTfBroadcaster(ros::NodeHandle nh) : tf_catched_(false)
{
    // Get params
    nh.param("frames/base_link", robot_frame_id_, string("colegobot"));
    nh.param("frames/odom", odom_frame_id_, string("odom"));
    nh.param("frames/map", map_frame_id_, string("map"));
    nh.param("frames/sensors/camera", camera_frame_id_, string("camera"));
    nh.param("frames/sensors/camera_origin", camera_origin_frame_id_, string("camera_pose"));

    // Subscriber
    sub_odom_ = nh_.subscribe("/odom", 1, &PoseTfBroadcaster::odomCallback, this);

    pub_cameraPose_ = nh_.advertise<nav_msgs::Odometry>("camera_pose", 1);
}


void PoseTfBroadcaster::odomCallback(const nav_msgs::OdometryConstPtr& odom)
{
    // Broadcast odom frame
    tf::Vector3 p(odom->pose.pose.position.x,odom->pose.pose.position.y,odom->pose.pose.position.z);
    tf::Quaternion q(odom->pose.pose.orientation.x, odom->pose.pose.orientation.y, odom->pose.pose.orientation.z, odom->pose.pose.orientation.w);
    tf::Transform T_map_odom_(q,p);   
    tf_broadcaster_.sendTransform(tf::StampedTransform(T_map_odom_,
                                                       odom->header.stamp,
                                                       map_frame_id_,
                                                       odom_frame_id_));

    if (!tf_catched_)
    {
        // Wait until a camera pose is found
        try
        {
          tf_listener_.lookupTransform(robot_frame_id_,
              camera_frame_id_,
              ros::Time(0),
              T_rob_cam_);


          tf_listener_.lookupTransform(camera_origin_frame_id_,
              camera_frame_id_,
              ros::Time(0),
              T_camO_cam_);
        }
        catch (tf::TransformException ex)
        {
          ROS_WARN_STREAM("[" << ros::this_node::getName() << "]: " << ex.what());
          // ros::Time::sleep(1.0);
          return;
        }

        tf_catched_ = true;

        // First camera pose position 
        T_map_camO_ = T_map_odom_ * T_rob_cam_;   
    }
    else
    {
        // Broadcast camera origin frame
        
        tf_broadcaster_.sendTransform(tf::StampedTransform(T_map_camO_,
                                                           odom->header.stamp,
                                                           map_frame_id_,
                                                           camera_origin_frame_id_));

        // Listen for camera pose transform
        try
        {
          tf_listener_.lookupTransform(camera_origin_frame_id_,
              camera_frame_id_,
              ros::Time(0),
              T_camO_cam_);
        }
        catch (tf::TransformException ex)
        {
          ROS_WARN_STREAM("[" << ros::this_node::getName() << "]: " << ex.what());
          return;
        }

        nav_msgs::Odometry camera_pose;
        camera_pose.header.stamp = odom->header.stamp;
        camera_pose.header.frame_id = camera_origin_frame_id_;
        camera_pose.pose.pose.position.x = T_camO_cam_.getOrigin().x();
        camera_pose.pose.pose.position.y = T_camO_cam_.getOrigin().y();
        camera_pose.pose.pose.position.z = T_camO_cam_.getOrigin().z();
        camera_pose.pose.pose.orientation.x = T_camO_cam_.getRotation().x();
        camera_pose.pose.pose.orientation.y = T_camO_cam_.getRotation().y();
        camera_pose.pose.pose.orientation.z = T_camO_cam_.getRotation().z();
        camera_pose.pose.pose.orientation.w = T_camO_cam_.getRotation().w();
        pub_cameraPose_.publish(camera_pose);
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_tf_broadcaster");

    ros::NodeHandle nh;
    PoseTfBroadcaster node(nh);

    ros::spin();

    ros::shutdown();

    return 0;
}
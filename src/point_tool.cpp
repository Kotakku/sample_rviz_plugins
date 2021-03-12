#include "point_tool.hpp"
// #include <OGRE/OgreSceneNode.h>
// #include <OGRE/OgreSceneManager.h>
// #include <OGRE/OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include <rviz_rendering/objects/shape.hpp>

// #include <ros/ros.h>

// #include <rviz/viewport_mouse_event.h>
// #include <rviz/visualization_manager.h>
// #include <rviz/geometry.h>
// #include <rviz/ogre_helpers/shape.h>
// #include <rviz/frame_manager.h>

#include <rviz_common/viewport_mouse_event.hpp>
#include <rviz_common/display_context.hpp>
#include <rviz_common/interaction/view_picker_iface.hpp>
#include <rviz_common/render_panel.hpp>

// #include <geometry_msgs/PointStamped.h>
// #include <pluginlib/class_list_macros.h>

namespace sample_rviz_plugins
{
PointTool::PointTool() 
    : rviz_common::Tool() //: nh_()
{
    shortcut_key_ = 'm';
}

PointTool::~PointTool()
{
}

void PointTool::onInitialize()
{
    vis_shape_.reset(new rviz_rendering::Shape(rviz_rendering::Shape::Cylinder, scene_manager_));
    Ogre::Vector3 shape_pos(0, 2, 0);
    vis_shape_->setPosition(shape_pos);
    Ogre::Quaternion shape_q(0.7, 0.7, 0, 0);
    vis_shape_->setOrientation(shape_q);
    vis_shape_->setColor(0, 0, 1, 1);
    vis_shape_->getRootNode()->setVisible(false);

    projection_finder_ = std::make_shared<rviz_rendering::ViewportProjectionFinder>();
    nh_ = context_->getRosNodeAbstraction().lock()->get_raw_node();
    // point_pub_ = nh_.advertise<geometry_msgs::PointStamped>("point", 10);
    point_pub_ = nh_->create_publisher<geometry_msgs::msg::PointStamped>("point", rclcpp::QoS(10));
}

void PointTool::activate()
{
    vis_shape_->setColor(0, 0, 1, 1);
    vis_shape_->getRootNode()->setVisible(true);
}

void PointTool::deactivate()
{
    vis_shape_->setColor(0.5, 0.5, 0.5, 1);
}

int PointTool::processMouseEvent(rviz_common::ViewportMouseEvent& event)
{
    //   Ogre::Vector3 intersection;
    //   Ogre::Plane ground_plane(Ogre::Vector3::UNIT_Z, 0.0f);

    //   if (rviz_common::getPointOnPlaneFromWindowXY(event.viewport, ground_plane, event.x, event.y, intersection))
    //   {
    //     vis_shape_->setPosition(intersection);
    //     if (event.leftDown())
    //     {
    //     //   geometry_msgs::PointStamped point_msg;
    //     //   point_msg.header.frame_id = context_->getFrameManager()->getFixedFrame();
    //     //   point_msg.header.stamp = ros::Time::now();
    //     //   point_msg.point.x = intersection.x;
    //     //   point_msg.point.y = intersection.y;
    //     //   point_msg.point.z = intersection.z;
    //     //   point_pub_.publish(point_msg);
    //       return Render | Finished;
    //     }
    //   }

    auto point_projection_on_xy_plane = projection_finder_->getViewportPointProjectionOnXYPlane(event.panel->getRenderWindow(), event.x, event.y);
    Ogre::Vector3 intersection = point_projection_on_xy_plane.second;
    if (point_projection_on_xy_plane.first)
    {
        vis_shape_->setPosition(intersection);

        if (event.leftDown())
        {
            auto point_msg = std::make_shared<geometry_msgs::msg::PointStamped>();
            point_msg->header.frame_id = context_->getFrameManager()->getFixedFrame();
            point_msg->header.stamp = nh_->now();
            point_msg->point.x = intersection.x;
            point_msg->point.y = intersection.y;
            point_msg->point.z = intersection.z;
            point_pub_->publish(*point_msg);
            return Render | Finished;
        }
    }

    return Render;
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(sample_rviz_plugins::PointTool, rviz_common::Tool)
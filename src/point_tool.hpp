#ifndef SAMPLE_RVIZ_PLUGINS_POINT_TOOL_HPP
#define SAMPLE_RVIZ_PLUGINS_POINT_TOOL_HPP

// #include <ros/ros.h>
// #include <rviz/tool.h>
// #include <rviz/ogre_helpers/shape.h>
#include <rclcpp/rclcpp.hpp>
#include <rviz_common/tool.hpp>
#include <rviz_rendering/viewport_projection_finder.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include <memory>

// namespace Ogre
// {
// class SceneNode;
// class Vector3;
// }  // namespace Ogre

// namespace rviz
// {
// class VectorProperty;
// class VisualizationManager;
// class ViewportMouseEvent;
// }  // namespace rviz

namespace rviz_rendering
{
    class Shape;
}

namespace sample_rviz_plugins
{

class PointTool : public rviz_common::Tool
{
    Q_OBJECT
public:
    PointTool();
    ~PointTool();

    virtual void onInitialize();
    virtual void activate();
    virtual void deactivate();
    virtual int processMouseEvent(rviz_common::ViewportMouseEvent &event);

    std::shared_ptr<rviz_rendering::Shape> vis_shape_;
    std::shared_ptr<rviz_rendering::ViewportProjectionFinder> projection_finder_;

    // ros::NodeHandle nh_;
    // ros::Publisher point_pub_;
    rclcpp::Node::SharedPtr nh_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_pub_;
};

}

#endif // SAMPLE_RVIZ_PLUGINS_POINT_TOOL_HPP
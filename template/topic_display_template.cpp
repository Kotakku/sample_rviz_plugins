#include "topic_display_template.hpp"

#include <rviz_common/display_context.hpp>

namespace sample_rviz_plugins
{

TopicDisplayTemplate::TopicDisplayTemplate()
{
}

TopicDisplayTemplate::~TopicDisplayTemplate()
{
}

void TopicDisplayTemplate::onInitialize()
{
    MFDClass::onInitialize();
}

void TopicDisplayTemplate::update(float wall_dt, float ros_dt)
{
    (void)dt;
    (void)ros_dt;
    
}

void TopicDisplayTemplate::processMessage(std_msgs::msg::Float32::ConstSharedPtr msg)
{
    std::lock_guard<std::mutex> lock(mutex_);
    
}

void TopicDisplayTemplate::reset()
{
    MFDClass::reset();
}

void TopicDisplayTemplate::onEnable()
{
    subscribe();
}

void TopicDisplayTemplate::onDisable()
{
    unsubscribe();
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS( sample_rviz_plugins::TopicDisplayTemplate, rviz_common::Display )
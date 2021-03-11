#include "display_template.hpp"

#include <rviz_common/display_context.hpp>

namespace rviz_default_plugins
{

DisplayTemplate::DisplayTemplate()
    : Display()
{
}

DisplayTemplate::~DisplayTemplate() = default;

void DisplayTemplate::onInitialize()
{
}

void DisplayTemplate::onEnable()
{
}

void DisplayTemplate::onDisable()
{
}

void DisplayTemplate::update(float dt, float ros_dt)
{
    (void)dt;
    (void)ros_dt;
    
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(sample_rviz_plugins::DisplayTemplate, rviz_common::Display)

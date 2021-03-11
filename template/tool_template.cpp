#include <rclcpp/rclcpp.hpp>
#include <rviz_common/tool.hpp>

#include "tool_template.hpp"

namespace sample_rviz_plugins
{

ToolTemplate::ToolTemplate()
    : rviz_common::Tool()
{
}

ToolTemplate::~ToolTemplate()
{
}

void ToolTemplate::onInitialize()
{
}

void ToolTemplate::activate()
{
}

void ToolTemplate::deactivate()
{
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS( sample_rviz_plugins::ToolTemplate, rviz_common::Tool )
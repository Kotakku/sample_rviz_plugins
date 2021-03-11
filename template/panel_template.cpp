#include "panel_template.hpp"

#include <rviz_common/config.hpp>

// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QSignalMapper>
// #include <rviz_common/display_context.hpp>

namespace sample_rviz_plugins
{

PanelTemplate::PanelTemplate(QWidget *parent)
    : rviz_common::Panel(parent)
{
}

void PanelTemplate::onInitialize()
{
}

void PanelTemplate::save(rviz_common::Config config) const
{
    rviz_common::Panel::save(config);
}

void PanelTemplate::load(const rviz_common::Config &config)
{
    rviz_common::Panel::load(config);
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(sample_rviz_plugins::PanelTemplate, rviz_common::Panel)
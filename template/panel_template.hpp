#ifndef SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP
#define SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>
#include <QtWidgets>
#endif

namespace sample_rviz_plugins
{

class PanelTemplate : public rviz_common::Panel
{
    Q_OBJECT
public:
    PanelTemplate(QWidget *parent = nullptr);

    virtual void onInitialize();
    virtual void load(const rviz_common::Config &config);
    virtual void save(rviz_common::Config config) const;

protected:
    QHBoxLayout *layout_;
    // QPushButton* button_;
};

}

#endif // SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP
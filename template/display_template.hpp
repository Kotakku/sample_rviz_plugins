#ifndef SAMPLE_RVIZ_PLUGINS_DISPLAY_TEMPLATE_HPP
#define SAMPLE_RVIZ_PLUGINS_DISPLAY_TEMPLATE_HPP

#include <rviz_common/display.hpp>

namespace sample_rviz_plugins
{

class DisplayTemplate : public rviz_common::Display
{
    Q_OBJECT
public:
    DisplayTemplate();

    ~DisplayTemplate() override;

    void onInitialize() override;
    void update(float dt, float ros_dt) override;

protected:
    void onEnable() override;
    void onDisable() override;

private Q_SLOTS:
    // void updateShape();

private:
};

}

#endif // SAMPLE_RVIZ_PLUGINS_DISPLAY_TEMPLATE_HPP

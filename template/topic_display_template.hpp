#ifndef SAMPLE_RVIZ_PLUGINS_TOPIC_DISPLAY_TEMPLATE_HPP
#define SAMPLE_RVIZ_PLUGINS_TOPIC_DISPLAY_TEMPLATE_HPP

#include <std_msgs/msg/float32.hpp>
#include <rviz_common/ros_topic_display.hpp>
#include <mutex>

namespace sample_rviz_plugins
{

class TopicDisplayTemplate
    : public rviz_common::RosTopicDisplay<std_msgs::msg::Float32>
{
    Q_OBJECT
public:
    TopicDisplayTemplate();
    ~TopicDisplayTemplate() override;

protected:
    void onEnable() override;
    void onDisable() override;
    void onInitialize() override;
    void processMessage(std_msgs::msg::Float32::ConstSharedPtr msg) override;
    void update(float wall_dt, float ros_dt) override;
    void reset() override;

    std::mutex mutex_;
private:
};

}

#endif // SAMPLE_RVIZ_PLUGINS_TOPIC_DISPLAY_TEMPLATE_HPP
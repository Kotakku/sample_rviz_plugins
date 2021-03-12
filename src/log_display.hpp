#ifndef SAMPLE_RVIZ_PLUGINS_LOG_DISPLAY_HPP
#define SAMPLE_RVIZ_PLUGINS_LOG_DISPLAY_HPP

#ifndef Q_MOC_RUN
// #include <rviz/display.h>
// #include <rviz/properties/int_property.h>
// #include <rosgraph_msgs/Log.h>
// #include <OGRE/Overlay/OgreTextAreaOverlayElement.h>

#include <rviz_common/ros_topic_display.hpp>
#include <rviz_common/properties/int_property.hpp>
#include <rcl_interfaces/msg/log.hpp>
#include <Overlay/OgreTextAreaOverlayElement.h>

#endif

namespace sample_rviz_plugins
{
class LogDisplay : public rviz_common::RosTopicDisplay<rcl_interfaces::msg::Log>
{
    Q_OBJECT
public:
    LogDisplay();
    virtual ~LogDisplay();

    virtual void onInitialize();
    virtual void reset();
    virtual void load(const rviz_common::Config &config);
    virtual void save(rviz_common::Config config) const;

private Q_SLOTS:
    void renderOverlay();

private:
    void processMessage(rcl_interfaces::msg::Log::ConstSharedPtr msg) override;
    //void processMessage(const rcl_interfaces::msg::Log &msg);
    rviz_common::properties::IntProperty *height_property_;
    rviz_common::properties::IntProperty *width_property_;
    rviz_common::properties::IntProperty *size_property_;

    Ogre::TextAreaOverlayElement *createTextElement(int index);
    void createMaterial(std::string mat_name);
    void destroyMaterial(std::string mat_name);

    //   ros::NodeHandle nh_;
    //   ros::Subscriber log_sub_;
    std::deque<rcl_interfaces::msg::Log> log_msgs_;

    Ogre::Overlay *overlay_;
    Ogre::OverlayContainer *panel_;
    std::vector<Ogre::TextAreaOverlayElement *> text_elements_;
    Ogre::OverlayElement *mat_element_;
};

}

#endif  // SAMPLE_RVIZ_PLUGINS_LOG_DISPLAY_HPP
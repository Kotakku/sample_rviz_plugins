#ifndef SAMPLE_RVIZ_PLUGINS_POINT_DISPLAY_HPP
#define SAMPLE_RVIZ_PLUGINS_POINT_DISPLAY_HPP

#ifndef Q_MOC_RUN
// #include <boost/circular_buffer.hpp>
// #include <rviz/message_filter_display.h>
// #include <rviz/ogre_helpers/arrow.h>
// #include <geometry_msgs/PointStamped.h>

#include <rviz_common/message_filter_display.hpp>
// #include <rviz_common/properties/color_property.hpp>
// #include <rviz_common/properties/float_property.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <memory>
#endif

namespace Ogre
{
class SceneNode;
}

namespace rviz_common
{
namespace properties
{
class ColorProperty;
class FloatProperty;
}
}

namespace rviz_rendering
{
class Arrow;
}

namespace sample_rviz_plugins
{
class PointDisplay : public rviz_common::MessageFilterDisplay<geometry_msgs::msg::PointStamped>
{
    Q_OBJECT
public:
    PointDisplay();
    virtual ~PointDisplay();

    virtual void onInitialize();
    virtual void reset();

private Q_SLOTS:
    void updateColorAndAlpha();
    void updateHistoryLength();

private:
    // void processMessage(const geometry_msgs::msg::PointStamped::ConstPtr &msg);
    void processMessage(geometry_msgs::msg::PointStamped::ConstSharedPtr msg) override;
    Ogre::SceneNode *frame_node_;
    //boost::shared_ptr<rviz::Arrow> vis_arrow_;
    std::shared_ptr<rviz_rendering::Arrow> vis_arrow_;
    rviz_common::properties::ColorProperty *color_property_;
    rviz_common::properties::FloatProperty *alpha_property_;
};

}  // namespace sample_rviz_plugins

#endif  // SAMPLE_RVIZ_PLUGINS_POINT_DISPLAY_HPP
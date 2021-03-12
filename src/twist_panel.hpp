#ifndef SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP
#define SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>
#include <QtWidgets>
#endif
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>

namespace sample_rviz_plugins
{

// https://github.com/project-srs/ros_lecture/blob/master/plugin_lecture/src/rviz/panel/qt_touch.h
class TouchWidget : public QWidget
{
    Q_OBJECT
public:
    TouchWidget(QWidget *parent = 0);

    // property
    bool grayout;
    float x_value;
    float y_value;
    int hcen;
    int vcen;
    int rsize;

    // event
    virtual void setEnabled(bool enable);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void leaveEvent(QEvent *event);
    void set_value(float x, float y);

public Q_SLOTS:
    void checkGrayout(int state);
Q_SIGNALS:
    void modifyPosition(QString);
};


// https://github.com/project-srs/ros_lecture/blob/master/plugin_lecture/src/rviz/panel/twist_panel.h
class TwistPanel : public rviz_common::Panel
{
    Q_OBJECT
public:
    TwistPanel(QWidget *parent = nullptr);

    virtual void onInitialize();
    virtual void load(const rviz_common::Config &config);
    virtual void save(rviz_common::Config config) const;

public Q_SLOTS:
    void tick();

protected:
    // The ROS node handle.
    // ros::NodeHandle nh_;
    rclcpp::Node::SharedPtr nh_;

    // The ROS publisher for the command velocity.
    // ros::Publisher twist_publisher_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_stamped_publisher_;

    QCheckBox* enable_check_;
    QLineEdit* topic_edit_;

    QCheckBox* stamped_check_;
    QLineEdit* frame_edit_;

    QRadioButton* radio1_;
    QRadioButton* radio2_;

    QLineEdit* max1_edit_;
    QLineEdit* max2_edit_;
    QLineEdit* max3_edit_;

    TouchWidget* touch_;

    bool pub_stamped_;
    std::string pub_frame_;
};

}

#endif // SAMPLE_RVIZ_PLUGINS_PANEL_TEMPLATE_HPP
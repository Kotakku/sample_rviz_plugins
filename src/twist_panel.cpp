#include "twist_panel.hpp"

#include <rviz_common/config.hpp>
#include <rviz_common/display_context.hpp>

// #include <string>
// #include <sstream>
// #include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>

// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QSignalMapper>


namespace sample_rviz_plugins
{


TouchWidget::TouchWidget(QWidget* parent): QWidget( parent )
{
  setMinimumSize(100,100);
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
  grayout=false;
}

void TouchWidget::setEnabled( bool enable ){
  grayout=!enable;
  update();
}

void TouchWidget::paintEvent( QPaintEvent* event )
{
  int w = width();
  int h = height();
  int size = (( w > h ) ? h : w) - 1;
  int hpad = ( w - size ) / 2;
  int vpad = ( h - size ) / 2;
  hcen = hpad + size/2;
  vcen = vpad + size/2;
  rsize=size/2;

  QColor background;
  QColor crosshair;
  if(!grayout){
    background = Qt::white;
    crosshair  = Qt::black;;
  }
  else{
    background = Qt::lightGray;
    crosshair = Qt::darkGray;
  }
  QPainter painter( this );
  painter.setBrush( background );
  painter.setPen( crosshair );

  painter.drawRect( QRect( hpad, vpad, size, size ));
  int rline=size/2;
  painter.drawLine( hcen, vcen-rline, hcen, vcen+rline );
  painter.drawLine( hcen-rline, vcen, hcen+rline, vcen );

  if(!grayout){
    QPen arrow;
    arrow.setWidth( size/20 );
    arrow.setColor( Qt::black );
    arrow.setCapStyle( Qt::RoundCap );
    arrow.setJoinStyle( Qt::RoundJoin );
    painter.setPen( arrow );

    const int step_count = 2;
    QPointF arrows[ step_count ];
    arrows[0].setX(hcen);
    arrows[0].setY(vcen);
    arrows[1].setX((int)(hcen+x_value*rsize));
    arrows[1].setY((int)(vcen+y_value*rsize));
    painter.drawPolyline( arrows, 2 );
  }
}

void TouchWidget::mouseMoveEvent( QMouseEvent* event )
{
  float tmp_x=1.0*(event->x()-hcen)/rsize;
  float tmp_y=1.0*(event->y()-vcen)/rsize;
  if(tmp_x<-1.0)tmp_x=-1.0;
  else if(tmp_x>1.0)tmp_x=1.0;
  if(tmp_y<-1.0)tmp_y=-1.0;
  else if(tmp_y>1.0)tmp_y=1.0;
  set_value(tmp_x, tmp_y);
  update();
}

void TouchWidget::mousePressEvent( QMouseEvent* event )
{
  float tmp_x=1.0*(event->x()-hcen)/rsize;
  float tmp_y=1.0*(event->y()-vcen)/rsize;
  if(tmp_x<-1.0)tmp_x=-1.0;
  else if(tmp_x>1.0)tmp_x=1.0;
  if(tmp_y<-1.0)tmp_y=-1.0;
  else if(tmp_y>1.0)tmp_y=1.0;
  set_value(tmp_x, tmp_y);
  update();
}

void TouchWidget::leaveEvent( QEvent* event )
{
  set_value(0, 0);
  update();
}

void TouchWidget::mouseReleaseEvent( QMouseEvent* event )
{
  set_value(0, 0);
  update();
}

void TouchWidget::set_value(float x, float y){
  x_value=x;
  y_value=y;
  std::ostringstream stm ;
  stm << x << ","<<y;
  QString text=QString::fromStdString(stm.str());
  Q_EMIT modifyPosition(text);
}

TwistPanel::TwistPanel(QWidget *parent)
    : rviz_common::Panel(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* layout_1st = new QHBoxLayout;
    enable_check_ = new QCheckBox("Enable");
    layout_1st->addWidget(enable_check_);
    layout_1st->addWidget(new QLabel("Topic:"));
    topic_edit_ = new QLineEdit("");
    layout_1st->addWidget(topic_edit_);
    layout->addLayout(layout_1st);

    QHBoxLayout* layout_2nd = new QHBoxLayout;
    stamped_check_ = new QCheckBox("Stamped");
    layout_2nd->addWidget(stamped_check_);
    layout_2nd->addWidget(new QLabel("Frame:"));
    frame_edit_ = new QLineEdit("");
    layout_2nd->addWidget(frame_edit_);
    layout->addLayout(layout_2nd);

    QHBoxLayout* layout_3rd = new QHBoxLayout;
    radio1_ = new QRadioButton("X-Y");
    layout_3rd->addWidget(radio1_);
    layout_3rd->addWidget(new QLabel("X max:"));
    max1_edit_ = new QLineEdit("");
    layout_3rd->addWidget(max1_edit_);
    layout_3rd->addWidget(new QLabel("Y max:"));
    max2_edit_ = new QLineEdit("");
    layout_3rd->addWidget(max2_edit_);
    layout->addLayout(layout_3rd);

    QHBoxLayout* layout_4th = new QHBoxLayout;
    radio2_ = new QRadioButton("X-Yaw");
    layout_4th->addWidget(radio2_);
    layout_4th->addWidget(new QLabel("Yaw max:"));
    max3_edit_ = new QLineEdit("");
    layout_4th->addWidget(max3_edit_);
    layout->addLayout(layout_4th);

    QButtonGroup* group1 = new QButtonGroup();
    group1->addButton(radio1_);
    group1->addButton(radio2_);

    touch_ = new TouchWidget();
    layout->addWidget(touch_);

    setLayout(layout);

    QTimer* output_timer = new QTimer(this);
    connect(output_timer, SIGNAL(timeout()), this, SLOT(tick()));
    output_timer->start(100);

    touch_->setEnabled(false);
    touch_->update();
}

void TwistPanel::onInitialize()
{
    nh_ = this->getDisplayContext()->getRosNodeAbstraction().lock()->get_raw_node();
    // nh_ = std::make_shared<rclcpp::Node>("twist_panel", "sample_rviz_plugin");
}

void TwistPanel::tick()
{
    if (enable_check_->isChecked())
    {
        if (twist_publisher_ || twist_stamped_publisher_)
        {
            float vel_max1 = max1_edit_->text().toFloat();
            float vel_max2 = max2_edit_->text().toFloat();
            float vel_max3 = max3_edit_->text().toFloat();

            auto msg = std::make_shared<geometry_msgs::msg::TwistStamped>();
            msg->header.frame_id = pub_frame_;
            // msg->header.stamp = ros::Time::now();
            msg->header.stamp = nh_->now();
            if (radio1_->isChecked())
            {
                msg->twist.linear.x = -1 * vel_max1 * (touch_->y_value);
                msg->twist.linear.y = -1 * vel_max2 * (touch_->x_value);
            }
            else if (radio2_->isChecked())
            {
                msg->twist.linear.x = -1 * vel_max1 * (touch_->y_value);
                msg->twist.angular.z = -1 * vel_max3 * (touch_->x_value);
            }
            if (pub_stamped_)
                twist_stamped_publisher_->publish(*msg);
            else
                twist_publisher_->publish(msg->twist);
        }
        else
        {
            std::string topic_name = topic_edit_->text().toStdString();
            if (topic_name != "")
            {
                if (stamped_check_->isChecked())
                {
                    std::string frame_name = frame_edit_->text().toStdString();
                    if (frame_name != "")
                    {
                        // twist_publisher_ = nh_.advertise<geometry_msgs::TwistStamped>(topic_name, 10);
                        twist_stamped_publisher_ = nh_->create_publisher<geometry_msgs::msg::TwistStamped>(topic_name, rclcpp::QoS(10));
                        pub_stamped_ = true;
                        pub_frame_ = frame_name;
                        // gray to process
                        topic_edit_->setEnabled(false);
                        stamped_check_->setEnabled(false);
                        frame_edit_->setEnabled(false);
                        touch_->setEnabled(true);
                    }
                }
                else
                {
                    // twist_publisher_ = nh_.advertise<geometry_msgs::Twist>(topic_name, 10);
                    twist_publisher_ = nh_->create_publisher<geometry_msgs::msg::Twist>(topic_name, rclcpp::QoS(10));
                    pub_stamped_ = false;
                    // gray to process
                    topic_edit_->setEnabled(false);
                    stamped_check_->setEnabled(false);
                    frame_edit_->setEnabled(false);
                    touch_->setEnabled(true);
                }
            }
        }
    }
    else
    { // Not checked
        if (twist_publisher_ || twist_stamped_publisher_)
        {
            //twist_publisher_.shutdown();
            twist_publisher_.reset();
            twist_stamped_publisher_.reset();

            // gray to not process
            topic_edit_->setEnabled(true);
            stamped_check_->setEnabled(true);
            frame_edit_->setEnabled(true);
            touch_->setEnabled(false);
        }
    }
}

void TwistPanel::save(rviz_common::Config config) const
{
    rviz_common::Panel::save(config);
}

void TwistPanel::load(const rviz_common::Config &config)
{
    rviz_common::Panel::load(config);
}

}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(sample_rviz_plugins::TwistPanel, rviz_common::Panel)
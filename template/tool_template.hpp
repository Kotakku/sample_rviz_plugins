#ifndef SAMPLE_RVIZ_PLUGINS_TOOL_TEMPLATE_HPP
#define SAMPLE_RVIZ_PLUGINS_TOOL_TEMPLATE_HPP

#include <rviz_common/tool.hpp>

namespace sample_rviz_plugins
{

class ToolTemplate : public rviz_common::Tool
{
public:
    ToolTemplate();
    virtual ~ToolTemplate();
    virtual void onInitialize();
    virtual void activate();
    virtual void deactivate();

protected:
private:
};

}
#endif // SAMPLE_RVIZ_PLUGINS_TOOL_TEMPLATE_HPP
#ifndef SAMPLE_RVIZ_PLUGINS_CLOSE_ALL_TOOL_HPP
#define SAMPLE_RVIZ_PLUGINS_CLOSE_ALL_TOOL_HPP

#include <rviz_common/tool.hpp>
#include <rviz_common/properties/property.hpp>
#include <rviz_common/properties/property_tree_model.hpp>

namespace sample_rviz_plugins
{

class CloseAllTool : public rviz_common::Tool
{
public:
    CloseAllTool();
    virtual ~CloseAllTool();
    virtual void onInitialize();
    virtual void activate();
    virtual void deactivate();

protected:
    virtual void closeProperty(rviz_common::properties::Property *property);

private:
};

}
#endif // SAMPLE_RVIZ_PLUGINS_CLOSE_ALL_TOOL_HPP
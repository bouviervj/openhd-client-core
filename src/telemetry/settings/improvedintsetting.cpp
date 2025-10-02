#include "improvedintsetting.h"


ImprovedIntSetting::ImprovedIntSetting(int min_value_int, int max_value_int, std::vector<Item> values_enum1):
    min_value_int(min_value_int),max_value_int(max_value_int),
    values_enum(values_enum1){
}

ImprovedIntSetting::ImprovedIntSetting(const ImprovedIntSetting &other):
    min_value_int(other.min_value_int),max_value_int(other.max_value_int),values_enum(other.values_enum)
{
}

std::vector<ImprovedIntSetting::Item> ImprovedIntSetting::convert_to_default_items(const std::vector<std::string> &values){
    std::vector<Item> ret{};
    for(size_t i=0;i<values.size();i++){
        ret.push_back(Item{values[i],(int) i});
    }
    return ret;
}

ImprovedIntSetting ImprovedIntSetting::createRangeOnly(int min_value, int max_value){
    return ImprovedIntSetting(min_value,max_value,{});
}

ImprovedIntSetting ImprovedIntSetting::createEnum(std::vector<std::string> values){
    // single enum would make no sense ?!
    assert(values.size()>1);
    return ImprovedIntSetting(0,values.size()-1,convert_to_default_items(values));
}

ImprovedIntSetting ImprovedIntSetting::createEnumEnableDisable(){
    std::vector<std::string> values{};
    values.push_back("Disable"); // False == disabled == 0
    values.push_back("Enable"); // 1==enabled
    return createEnum(values);
}

ImprovedIntSetting ImprovedIntSetting::createEnumSimple(std::vector<std::pair<std::string, int>> elements){
    std::vector<Item> items{};
    for(const auto& el:elements){
        items.push_back(Item{el.first,el.second});
    }
    // TODO fix min max
    return ImprovedIntSetting(0,100,items);
}

std::string ImprovedIntSetting::value_to_string(int value) const{
    for(const auto& item:values_enum){
        if(item.value==value)return item.name;
    }
    std::stringstream ss;
    ss<<"?{"<<value<<"}?";
    return ss.str();
}

std::vector<std::string> ImprovedIntSetting::int_enum_keys() const{
    std::vector<std::string> ret{};
    for(const auto& item:values_enum){
        ret.push_back(item.name);
    }
    return ret;
}

std::vector<int> ImprovedIntSetting::int_enum_values() const{
    std::vector<int> ret;
    for(const auto& item:values_enum){
        ret.push_back(item.value);
    }
    return ret;
}

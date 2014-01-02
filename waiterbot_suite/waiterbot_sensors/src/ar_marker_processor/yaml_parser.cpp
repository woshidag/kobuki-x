/*
   AR marker yaml parser

   LICENSE : BSD - https://raw.github.com/yujinrobot/yujin_ocs/license/LICENSE

   Author : Jihoon Lee
   Date   : Dec 2013
 */

#include "waiterbot_sensors/yaml_parser_ar_markers.hpp"

namespace waiterbot {

  bool loadAlvarMarkersFromYaml(const std::string& filename,ar_track_alvar::AlvarMarkers& ams)
  {

    ams.markers.clear(); 

    // Yaml File Parsing
    try
    {
      YAML::Node doc;

      getYamlNode(filename, doc);
      parseMarkers(doc, ams);
    }
    catch(YAML::ParserException& e)
    {
      ROS_ERROR("Parse AR markers file failed: %s", e.what());
      return false;
    }
    catch(YAML::RepresentationException& e)
    {
      ROS_ERROR("Parse AR Markers file failed: %s", e.what());
      return false;
    }
    catch(std::string& e) {
      ROS_ERROR("Parse AR Markers file failed: %s",e.c_str());
      return false;
    }
    return true;
  }

  void getYamlNode(const std::string& filename, YAML::Node& node) 
  {
    std::ifstream ifs(filename.c_str(), std::ifstream::in);
    if (ifs.good() == false)
    {                                                            
      throw std::string("file not found");
    }

    YAML::Parser parser(ifs);
    parser.GetNextDocument(node);
  }

  void parseMarkers(const YAML::Node& node, ar_track_alvar::AlvarMarkers& ams) 
  {
    unsigned int i;

    for(i = 0; i < node.size(); i++) 
    {
        // Parse AlvarMarker entries on YAML
        ar_track_alvar::AlvarMarker m;

        node[i]["id"] >> m.id;
        node[i]["frame_id"] >> m.header.frame_id;
        node[i]["frame_id"] >> m.pose.header.frame_id;
        node[i]["confidence"] >> m.confidence;
        node[i]["pose"]["position"]["x"] >> m.pose.pose.position.x;
        node[i]["pose"]["position"]["y"] >> m.pose.pose.position.y;
        node[i]["pose"]["position"]["z"] >> m.pose.pose.position.z;
        node[i]["pose"]["orientation"]["x"] >> m.pose.pose.orientation.x;
        node[i]["pose"]["orientation"]["y"] >> m.pose.pose.orientation.y;
        node[i]["pose"]["orientation"]["z"] >> m.pose.pose.orientation.z;
        node[i]["pose"]["orientation"]["w"] >> m.pose.pose.orientation.w;

        ams.markers.push_back(m);
    }
  }
}
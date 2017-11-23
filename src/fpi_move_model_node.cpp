#include <fpi_move_model/fpi_model.hpp>

#include <ros/ros.h>
#include <gazebo_msgs/ModelState.h>

int main( int argc, char** argv )
{
    ros::init( argc, argv, "fpi_move_model_node" );
    ros::NodeHandle nodeHandle;
    
    std::vector<FpiModel::pose_t> waypoints;
    waypoints.push_back( {10, 10, 2} );
    waypoints.push_back( {20, 10, 2} );
    waypoints.push_back( {20, 15, 2} );
    waypoints.push_back( {30, 15, 2} );
    
    
    ros::Rate loop_rate( 60 );
    
    FpiModel irisFpiModel( nodeHandle, 60.0,  0.2 );
    irisFpiModel.addWaypoints( waypoints );
    
    while( ros::ok() )
    {
        irisFpiModel.run();
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}

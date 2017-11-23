#include <fpi_move_model/fpi_model.hpp>

FpiModel::FpiModel( ros::NodeHandle& _nh, const float _rosTicks , const float _speed  )
{
    //this->m_statePublisher  = std::make_shared< ros::Publisher >();
    //this->m_statePublisher = _nh.advertise<gazebo_msgs::ModelState>( "gazebo/set_model_state", 100 );
    this->m_poseClient     = _nh.serviceClient<gazebo_msgs::SetModelState>( "gazebo/set_model_state" );
    this->m_speed          = _speed;
    this->m_rosTicks       = _rosTicks;
    
    
}

FpiModel::~FpiModel()
{
    this->m_statePublisher.shutdown();
    this->m_poseClient.shutdown();
}

void FpiModel::run()
{
    if( this->m_waypoints.empty() )
    {
        ROS_INFO( "Done" );
        return;
    }
    
    FpiModel::pose_t pose = this->m_waypoints.front();
    this->m_waypoints.pop();
    
    
    gazebo_msgs::ModelState message;
    message.model_name = "iris1";
    message.reference_frame = "world";
    
    message.pose.position.x     = pose.x;
    message.pose.position.y     = pose.y;
    message.pose.position.z     = pose.z;
    message.pose.orientation.x  = 0.0;
    message.pose.orientation.y  = 0.0;
    message.pose.orientation.z  = 0.0;
    
    message.twist.linear.x      = 1.0;
    message.twist.linear.y      = 0.0;
    message.twist.linear.z      = 0.0;
    message.twist.angular.x     = 0.0;
    message.twist.angular.y     = 0.0;
    message.twist.angular.z     = 0.0;
    
    gazebo_msgs::SetModelState modelStateMsg;
    modelStateMsg.request.model_state = message;
    
    this->m_poseClient.call( modelStateMsg );
    
    //this->m_statePublisher.publish( message );
    
}

void FpiModel::addWaypoints( std::vector<FpiModel::pose_t> _poseVector )
{
    float speedPerTick = (float)this->m_speed / (float)this->m_rosTicks;
    
    //this->m_waypoints.push( _poseVector.front() );
    
    for( std::vector<FpiModel::pose_t>::iterator it = _poseVector.begin() + 1
       ; it != _poseVector.end()
       ; ++it)
    {
         float speedPerTickX = ( ( *it ).x - ( *std::prev( it ) ).x  ) * speedPerTick; 
         float speedPerTickY = ( ( *it ).y - ( *std::prev( it ) ).y  ) * speedPerTick;
         float speedPerTickZ = ( ( *it ).z - ( *std::prev( it ) ).z  ) * speedPerTick;
            
         ROS_INFO( "OK" );
         
         pose_t currentPose = *std::prev(it);
         
         ROS_INFO( "%f", speedPerTick );
         
         ROS_INFO( "%f", speedPerTickX );
         ROS_INFO( "%f", speedPerTickY );
         ROS_INFO( "%f", speedPerTickZ );
         
         ROS_INFO( "%f", currentPose.x );
         ROS_INFO( "%f", currentPose.y );
         ROS_INFO( "%f", currentPose.z );
         
         ROS_INFO( "%f", (*it).x );
         ROS_INFO( "%f", (*it).y );
         ROS_INFO( "%f", (*it).z );
         
         while(  currentPose.x < (*it).x
              || currentPose.y < (*it).y
              || currentPose.z < (*it).z )
         {
            this->m_waypoints.push( currentPose );
            
            currentPose.x += speedPerTickX;
            currentPose.y += speedPerTickY;
            currentPose.z += speedPerTickZ;
            
            ROS_INFO( "%f", currentPose.x );
            ROS_INFO( "%f", currentPose.y );
            ROS_INFO( "%f", currentPose.z );
         
            
            ROS_INFO( "OK" );
        }
        
        ROS_INFO( "Finish" );
    }
    
    
    /*
    while( !this->m_waypoints.empty() )
    {
        std::cout << "x: " << this->m_waypoints.front().x << std::endl;
        std::cout << "y: " << this->m_waypoints.front().y << std::endl;
        std::cout << "z: " << this->m_waypoints.front().z << std::endl;
        std::cout << std::endl;
        
        this->m_waypoints.pop();
    }*/
    
}

void FpiModel::move( const int32_t _x, const int32_t _y, const int32_t _z )
{
    
}

#ifndef FP_MDL_HPP
#define FP_MDL_HPP

#include <ros/ros.h>
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/SetModelState.h>

#include <string>
#include <queue>

class FpiModel
{
    public:
        
        typedef struct pose_t
        {
            float x;
            float y;
            float z;
            
            bool operator<=( const pose_t& rhs ) const
            {
                return rhs.x <= this->x && rhs.y <= this->y && rhs.z <= this->z;
            }
        }pose;
        
        const std::string FPI_MODEL_NAME = "iris1";
        
        FpiModel( ros::NodeHandle& _nh, const float _rosTicks = 60, const float _speed = 1 );
        ~FpiModel();
        
        void run();
        
        void addWaypoints( std::vector<pose_t> _waypoints );
        
        void move( const int32_t _x, const int32_t _y, const int32_t _z = 2 );
    
    private:
        ros::Publisher         m_statePublisher;
        ros::ServiceClient     m_poseClient;
        
        std::string            m_modelName;
        float                  m_speed;
        float                  m_rosTicks;
        
        pose_t                 m_modelPose;

        std::queue<pose_t>     m_waypoints;
};

#endif

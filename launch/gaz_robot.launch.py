from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription,DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command, LaunchConfiguration
import os

def generate_launch_description():

        # needs to be updated
    package_name = "tank"

    bridge_params = os.path.join(
    get_package_share_directory(package_name),
    'params',
    'gaz_brigde.yaml'
    )

    start_gazebo_ros_bridge_cmd = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            '--ros-args',
            '-p',
            f'config_file:={bridge_params}',
        ],
        output='screen',
    )

    default_world = os.path.join(
        get_package_share_directory(package_name),
        'worlds',
        'empty.world'
    )
    
    world = LaunchConfiguration('world')

    world_arg = DeclareLaunchArgument(
        'world',
        default_value=default_world,
        description='world to load'
    )

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('ros_gz_sim'), 'launch', 'gz_sim.launch.py')]),
                launch_arguments={'gz_args':['-r -v4 ',world],'on_exit_shutdown': 'true'}.items()
        )
    
    # Run the spawner node from the ros_gz_sim package. The entity name doesn't really matter if you only have a single robot.
    spawn_entity = Node(package='ros_gz_sim', executable='create',
                        arguments=['-topic', 'robot_description',
                                   '-name', 'tank',
                                   "-z","0.3"],
                        output='screen')

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': True,
            'robot_description': Command(['xacro ', os.path.join(
                get_package_share_directory(package_name),
                'description', 'tank.urdf.xacro'
            )])
        }]
    )

    return LaunchDescription([
        start_gazebo_ros_bridge_cmd,
        # start_gazebo_ros_image_bridge_cmd
        world_arg,
        spawn_entity,
        gazebo,
        robot_state_publisher,
    ])
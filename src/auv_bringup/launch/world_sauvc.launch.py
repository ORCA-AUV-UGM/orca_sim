"""Generate one seeded SAUVC layout, run Gazebo Harmonic, and spawn ORCA_V3.

Randomizes flare positions (and the blue bucket slot) per launch, unless a fixed
seed is given. Spawns the ORCA_V3 robot at the starting zone and bridges its
pose/imu/camera topics.
"""
import os
from pathlib import Path
import secrets
import shlex
import shutil
import subprocess
import sys
import tempfile

from ament_index_python.packages import get_package_share_directory, get_package_prefix
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, IncludeLaunchDescription,
    LogInfo, OpaqueFunction, RegisterEventHandler, SetEnvironmentVariable)
from launch.event_handlers import OnShutdown
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def setup(context):
    pkg = Path(get_package_share_directory('auv_bringup'))
    text_seed = LaunchConfiguration('seed').perform(context)
    seed = secrets.randbits(31) if text_seed == 'random' else int(text_seed)

    temp = Path(tempfile.mkdtemp(prefix='orca_sauvc_v6_'))
    world = temp / 'world_sauvc_v6.sdf'
    try:
        generated = subprocess.run([
            sys.executable, str(pkg / 'scripts/generate_sauvc.py'),
            '--config', str(pkg / 'config/sauvc_pool.json'),
            '--template', str(pkg / 'worlds/world_sauvc.sdf'),
            '--output', str(world), '--seed', str(seed),
        ], check=True, capture_output=True, text=True)
    except subprocess.CalledProcessError as exc:
        shutil.rmtree(temp, ignore_errors=True)
        raise RuntimeError('SAUVC layout generation failed: ' + exc.stderr) from exc
    except Exception:
        shutil.rmtree(temp, ignore_errors=True)
        raise

    def cleanup(_context):
        shutil.rmtree(temp, ignore_errors=True)
        return []

    plugin_lib = str(Path(get_package_prefix('auv_bringup')) / 'lib')
    auv_desc = Path(get_package_share_directory('auv_description'))
    urdf_path = str(auv_desc / 'urdf' / 'auv.urdf.xacro')
    rviz_path = str(auv_desc / 'rviz' / 'urdf_config.rviz')
    robot_description = ParameterValue(Command(['xacro ', urdf_path]), value_type=str)
    return [
        LogInfo(msg='ORCA SAUVC V6: ' + generated.stdout.strip()),
        LogInfo(msg=f'seed={seed}; layout={world.with_suffix(".layout.json")}'),
        RegisterEventHandler(OnShutdown(on_shutdown=[OpaqueFunction(function=cleanup)])),
        SetEnvironmentVariable('GZ_SIM_SYSTEM_PLUGIN_PATH',
            plugin_lib + ':' + os.environ.get('GZ_SIM_SYSTEM_PLUGIN_PATH', '')),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                str(Path(get_package_share_directory('ros_gz_sim')) / 'launch/gz_sim.launch.py')),
            launch_arguments={'gz_version': '8', 'gz_args': '-r ' + shlex.quote(str(world))}.items()),
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             parameters=[{'robot_description': robot_description}]),
        Node(package='ros_gz_sim', executable='create',
             arguments=['-topic', 'robot_description']),
        Node(package='ros_gz_bridge', executable='parameter_bridge',
             arguments=['/model/ORCA_V3/pose@geometry_msgs/msg/Pose[gz.msgs.Pose']),
        Node(package='ros_gz_bridge', executable='parameter_bridge',
             arguments=['/world/empty/model/ORCA_V3/link/base_footprint/sensor/imu_sensor/imu@sensor_msgs/msg/Imu[gz.msgs.IMU']),
        Node(package='ros_gz_bridge', executable='parameter_bridge',
             arguments=['/camera/image_raw@sensor_msgs/msg/Image@gz.msgs.Image']),
        Node(package='ros_gz_bridge', executable='parameter_bridge',
             arguments=['/camera/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo']),
        Node(package='rviz2', executable='rviz2', output='screen', arguments=['-d', rviz_path]),
    ]


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('seed', default_value='random'),
        OpaqueFunction(function=setup),
    ])

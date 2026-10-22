from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'mavpy_sim'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'models'), glob('mavpy_sim/models/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jetson',
    maintainer_email='jetson@todo.todo',
    description='ORCA sensor, control bridge, teleop, and mission nodes',
    license='Proprietary',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'test_control = mavpy_sim.test_control:main',
            'test_keyboard = mavpy_sim.test_keyboard:main',

            'camera_sim_qualification = mavpy_sim.camera_sim_qualification:main',
            'camera_sim_final = mavpy_sim.camera_sim_final:main',

            'attitude_node = mavpy_sim.attitude_node:main',
            'control_bridge = mavpy_sim.control_bridge:main',
            'keyboard = mavpy_sim.keyboard:main',
        ],
    },
)

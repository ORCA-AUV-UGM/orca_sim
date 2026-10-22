from setuptools import find_packages
from setuptools import setup

setup(
    name='orca_msgs_sim',
    version='0.0.0',
    packages=find_packages(
        include=('orca_msgs_sim', 'orca_msgs_sim.*')),
)

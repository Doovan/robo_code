#include "preTreat.h"
#include <pcl/io/ply_io.h>
#include <iostream>

int main() {
    // 读取点云数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPLYFile<pcl::PointXYZ>("/home/kong/catkin_ws/robo_code/sourceFile/in.ply", *cloud);

    // 预处理点云数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr processedCloud(new pcl::PointCloud<pcl::PointXYZ>);
    processedCloud = preprocessPointCloud(cloud);

    // 显示处理后的点云数据
    displayPointCloud(processedCloud);
    
    return 0;
}
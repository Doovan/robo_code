#include "preTreat.h"
#include <iostream>

void displayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
    // 创建PCL可视化对象
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Point Cloud Viewer"));
    // 设置背景颜色
    viewer->setBackgroundColor(0, 0, 0);
    // 添加点云数据
    viewer->addPointCloud(cloud, "sample cloud");
    // 显示点云
    while (!viewer->wasStopped())
    {
        viewer->spinOnce();
    }
}

pcl::PointCloud<pcl::PointXYZ>::Ptr preprocessPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloud)
{
    // 计算法向量
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud(inputCloud);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    ne.setSearchMethod(tree);
    pcl::PointCloud<pcl::Normal>::Ptr cloudNormals(new pcl::PointCloud<pcl::Normal>);
    ne.setRadiusSearch(0.03);  // 设置法向量估计的搜索半径
    ne.compute(*cloudNormals);

    // 计算曲率
    pcl::PrincipalCurvaturesEstimation<pcl::PointXYZ, pcl::Normal, pcl::PrincipalCurvatures> principalCurvaturesEstimation;
    principalCurvaturesEstimation.setInputCloud(inputCloud);
    principalCurvaturesEstimation.setInputNormals(cloudNormals);
    principalCurvaturesEstimation.setSearchMethod(tree);
    principalCurvaturesEstimation.setRadiusSearch(0.05); // 设置曲率估计的搜索半径
    pcl::PointCloud<pcl::PrincipalCurvatures>::Ptr principalCurvatures(new pcl::PointCloud<pcl::PrincipalCurvatures>);
    principalCurvaturesEstimation.compute(*principalCurvatures);

    // 去除离群点
    pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud(inputCloud);
    sor.setMeanK(50);  // 设置临近点个数
    sor.setStddevMulThresh(1.0);  // 设置标准差倍数阈值
    sor.filter(*filteredCloud);

    std::cout << "去除离群点前点云大小: " << inputCloud->size() << std::endl;
    std::cout << "去除离群点后点云大小: " << filteredCloud->size() << std::endl;
    std::cout << "去除了点个数: " << inputCloud->size() - filteredCloud->size() << std::endl;

    return filteredCloud;
}

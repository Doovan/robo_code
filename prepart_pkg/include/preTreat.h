#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/principal_curvatures.h>
#include <pcl/filters/statistical_outlier_removal.h>

extern void displayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);
extern pcl::PointCloud<pcl::PointXYZ>::Ptr preprocessPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloud);
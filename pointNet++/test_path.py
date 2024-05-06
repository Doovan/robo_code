import os
import glob
import numpy as np

# 文件夹路径
folder_path = "/home/kong-vb/pointnet2/Pointnet_Pointnet2_pytorch/data/pointData_use1"

# 使用 glob 模块获取所有txt文件的路径
txt_files = glob.glob(os.path.join(folder_path, "*.txt"))

point_cloud_data = np.loadtxt(txt_files[0]).astype(np.float32)

choice = np.random.choice(10, 5, replace=True) 
point_set = point_cloud_data[choice,:]
for data in point_set:
    print (data[0], data[1], data[2],data[6])




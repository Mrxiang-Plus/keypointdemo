//
// Created by xiang on 2019/10/22.
//
//
// Created by xiang on 2019/9/23.
//

///使用特定的图片集，
///测试提取所花时间与点数多少的关系   版本三
///计算时间优化，只计算取点所花时间
///Fast角点

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <fstream>

using namespace std;

int main(int argc, char ** argv){

    if (argc != 2) {
        cout << "wrong input\nusage : keypoint  path_dataset" << endl;
        return 1;
    }

    string file_path = argv[1];
    string file = file_path + "/file.txt";

    int maxpoints[9] = {10,50,100,200,400,600,800,1000,0};

    for (int i = 0; i <= 8; ++i) {
        int points_num = 0;//特征点总数
        ifstream fin(file);//读取文件
        double time=0; //取点所花的总时间


        //进行处理
        while(true){
            string image_path;//当前图片路径
            cv::Mat image ;
            vector<cv::KeyPoint> points_fast;//存放角点
            double time_Fast; //取点所花的总时间

            fin >> image_path;
            if (fin.eof())  break;

            image = cv::imread(image_path);//读取图片
            //cv::cvtColor(image,image_gray,cv::COLOR_BGR2GRAY);//转化为灰度图
            //用Fast检测器检测角点
            //cv::namedWindow("Fast",cv::WINDOW_AUTOSIZE);
            //cv::resizeWindow("Fast",640,480);
            double start_Fast = cv::getTickCount();// 检测开始时
            cv::Ptr<cv::GFTTDetector> fastDetector = cv::GFTTDetector::create(maxpoints[i],0.01,10,3, false,0.04);
            fastDetector -> detect(image,points_fast);
            time_Fast = (cv::getTickCount() - start_Fast) / (double)cv::getTickFrequency();//检测所花的时间
            //cv::drawKeypoints(image, points_fast, image, cv::Scalar(255, 0, 0), cv::DrawMatchesFlags::DEFAULT);
            //cv::imshow("Fast", image);
            points_num += points_fast.size();
            time += time_Fast;
            //cout << "fast point number: " << points_fast.size() << endl;
            //cv::waitKey(-1);
        }

        cout <<"\ntimes"<< i <<"\npoints amount :"<< points_num <<"\nusing time " << time <<"s"<<endl;
    }


    return 0;
}



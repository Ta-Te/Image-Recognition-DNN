//
// A demonstration program to show image recognition using DNN
//
// Ta-Te Lin
// National Taiwan University
// 2017/07/13
//
// Reference websits:
// https://github.com/opencv/opencv_contrib/issues/1100
// http://docs.opencv.org/3.2.0/d6/d0f/group__dnn.html
// http://docs.opencv.org/3.2.0/d5/de7/tutorial_dnn_googlenet.html
// http://docs.opencv.org/trunk/d5/de7/tutorial_dnn_googlenet.html
// http://www.coldvision.io/2016/07/29/image-classification-deep-learning-cnn-caffe-opencv-3-x-cuda/
//

#include "deeplearning.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeepLearning w;
    w.show();

    return a.exec();
}

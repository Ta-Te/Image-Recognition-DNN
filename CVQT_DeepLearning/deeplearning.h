#ifndef DEEPLEARNING_H
#define DEEPLEARNING_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextEdit>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/core/cvdef.h>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <functional>

using namespace std;
using namespace cv;
using namespace cv::dnn;

namespace Ui {
class DeepLearning;
}


class DeepLearning : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeepLearning(QWidget *parent = 0);
    ~DeepLearning();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionRecognize_triggered();

private:
    Ui::DeepLearning *ui;
};

#endif // DEEPLEARNING_H

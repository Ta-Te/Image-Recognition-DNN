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
#include "ui_deeplearning.h"

// Global Variables
cv::Mat image;
cv::Mat image1;
cv::Mat image2;
cv::Mat image3;
QString message;
QString object_label;


/////////////////////////////////////////////////////////////////////////////////////////
//
// This function extracts best matches from the DNN
//
/////////////////////////////////////////////////////////////////////////////////////////
void getBestMatches( cv::dnn::Blob &probBlob, std::vector < pair<double , int> >& bestMatches )
{
    // reshape the blob to 1x1000 matrix
    Mat probMat = probBlob.matRefConst().reshape(1, 1);

    // build a map of {probability, classId} in decreasing order, highest probability first
    std::multimap<double, int, greater<double> > map;
    std::multimap<double, int, greater<double> >::iterator mapIt;
    for(int i=0; i<probMat.cols; ++i)
    {
        int classId = i; // position in the array represents the classId
        double classProb = (double) probMat.at<float>(0, i); // the probMat stores its elements as float
        map.insert ( std::pair<double, int>(classProb, classId) );
    }

    // select the best matches, which are in the first positions in the sorted map
    int index = 0;
    for( mapIt = map.begin(); mapIt!=map.end(); mapIt++ )
    {
        bestMatches[index] = *mapIt; // the map and the vector have the same type: pair<double, int>
        if( ++index == bestMatches.size() )
        {
            break; // stop when first bestMatches are copied
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// This function loads the class IDs and names from the file system.
//
// @see http://docs.opencv.org/trunk/d5/de7/tutorial_dnn_googlenet.html
/////////////////////////////////////////////////////////////////////////////////////////
void readClassNames(const std::string fileName, std::vector<string>& classNames)
{
    std::ifstream fp(fileName.c_str());
    if (!fp.is_open())
    {
        std::cerr << "File with classes labels not found: " << fileName << std::endl;
        exit(-1);
    }
    std::string className;
    while (!fp.eof())
    {
        std::getline(fp, className);
        if (className.length())
        {
            classNames.push_back( className.substr(className.find(' ')+1) );
        }
    }
    fp.close();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// This function loads DNN model and layers into the net and sets connections between them
//
/////////////////////////////////////////////////////////////////////////////////////////
void loadCaffeNet(const string & modelTxt, const string & modelBin, dnn::Net & net)
{
    // try to import the Caffe model
    Ptr<dnn::Importer> importer;
    try
    {
        importer = dnn::createCaffeImporter(modelTxt, modelBin);
    }
    catch (const cv::Exception& err) //Importer can throw errors, we will catch them
    {
        std::cerr << err.msg << std::endl;
    }

    // check if errors occurred while creating the importer from the file
    if (!importer)
    {
        std::cerr << "Can't load network by using the following files: " << std::endl;
        std::cerr << "prototxt:   " << modelTxt << std::endl;
        std::cerr << "caffemodel: " << modelBin << std::endl;
        std::cerr << "bvlc_googlenet.caffemodel can be downloaded here:" << std::endl;
        std::cerr << "http://dl.caffe.berkeleyvision.org/bvlc_googlenet.caffemodel"	<< std::endl;
        exit(-1);
    }
    // Adds loaded layers into the net and sets connections between them.
    importer->populateNet(net);
    importer.release(); //We don't need importer anymore
}




DeepLearning::DeepLearning(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeepLearning)
{
    ui->setupUi(this);
}

DeepLearning::~DeepLearning()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Exit the program
/////////////////////////////////////////////////////////////////////////////////////////
void DeepLearning::on_actionExit_triggered()
{
    close();
}

/////////////////////////////////////////////////////////////////////////////////////////
// Open image file
/////////////////////////////////////////////////////////////////////////////////////////
void DeepLearning::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), ".",
        tr("Image Files (*.png *.jpg *.jpeg *.bmp"));

    if(fileName != NULL)
    {
        image = cv::imread(fileName.toStdString().data());
        image1 = image.clone();
        cvtColor(image, image2, 4 );  // 4 for original CV_BGR2RGB

        // Resize the image to fit the display screen
        cv::resize(image2, image2, Size(ui->label->width(), ui->label->height()));

        // Qt image
        QImage img = QImage((const unsigned char*) (image2.data),
                            image2.cols, image2.rows, QImage::Format_RGB888);

        // Display on label
        ui->label->setPixmap(QPixmap::fromImage(img));

        message = "<< Image file " + QString::fromUtf8(fileName.toStdString().data()) + " successfully loaded >>";
        ui->textEdit->append(message);

    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Image recognition
/////////////////////////////////////////////////////////////////////////////////////////
void DeepLearning::on_actionRecognize_triggered()
{
    string modelTxt = "bvlc_googlenet.prototxt";
    string modelBin = "bvlc_googlenet.caffemodel";
    string classFile = "synset_words.txt";

    cv::dnn::initModule();

    // load the DNN model
    cv::dnn::Net net;
    loadCaffeNet(modelTxt, modelBin, net);
    ui->textEdit->append("<< Deep learning network successfully loaded >>");

    // load the class IDs and names
    std::vector<string> classNames;
    readClassNames(classFile,classNames);

    //GoogLeNet accepts only 224x224 RGB-images
    cv::resize(image, image, Size(224, 224)); //GoogLeNet accepts only 224x224 RGB-images

    dnn::Blob inputBlob = dnn::Blob::fromImages(image);   //Convert Mat to dnn::Blob batch of images
    net.setBlob(".data", inputBlob);          //set the network input

    // classify the image by applying the blob on the net
    net.forward(); //compute output

    dnn::Blob prob = net.getBlob("prob");   //gather output of "prob" layer


    // find the best 5 matches and their probabilities
    dnn::Blob probability = net.getBlob("prob"); //gather output of "prob" layer

    int numberOfMatches = 5; // find top best matches
    vector < pair<double , int> > bestMatches (numberOfMatches);
    vector < pair<double , int> >::iterator matchIt;
    getBestMatches(probability, bestMatches); //find the best class

    // print the best matches
    ui->textEdit->append("<< Recognition results >>");
    for( matchIt = bestMatches.begin(); matchIt!=bestMatches.end(); matchIt++ )
    {
        double classProb = (*matchIt).first;
        int classId = (*matchIt).second;

        if(matchIt == bestMatches.begin())
        {
            object_label = QString::fromStdString(classNames.at(classId));
        }
        message = "Probability : " + QString::number(classProb*100,'f',2) + "% - ID: " + QString::number(classId)
                   + " - " + QString::fromStdString(classNames.at(classId)) + "'";
        ui->textEdit->append(message);

        std::cout << std::fixed << std::setprecision(4) << classProb * 100 << "% - \"#" << classId
                << " " << classNames.at(classId) << "\"" << std::endl;
    }
    ui->textEdit->append("   ");

    // Put the most probable guess label on the image
    cvtColor(image1, image3, 4 );  // 4 for original CV_BGR2RGB
    cv::resize(image3, image3, Size(ui->label->width(), ui->label->height()));
    cv::putText(image3, object_label.toStdString(), Point(50,50), FONT_HERSHEY_DUPLEX , 1.0, cv::Scalar(0,255,0));
    QImage img = QImage((const unsigned char*) (image3.data), image3.cols, image3.rows, QImage::Format_RGB888);
    // Display on label
    ui->label->setPixmap(QPixmap::fromImage(img));

}

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;


int main()
{
    cv::Mat image = cv::imread("new.jpg");      //  Считываем файл surface.jpg
    if (!image.data)                                //  Проверяем, удалось ли его  открыть
        return -1;                                  //  Если нет - оставшуюся часть выполнять не будем

    cv::imshow("Test", image);                      //  Выведем результат на экран
    cv::waitKey();                                  //  И подождём нажатия на кнопку
    std::vector<cv::Mat> planes;                    //  Теперь я сформирую вектор из отделных матриц
    cv::split (image, planes);                      //  И разделю исходный файл на отдельные каналы
                                                    //  Каналы соответствуют цвету - blue, green, red
    for (int i=0; i<planes.size(); i++)             //  А теперь выведем их на экран по отдельности
    {
        std::string name;
        switch (i)                                  //  Переключатель case - несколько удобнее, чем
        {                                           //  несколько if
            case 2 :
                name = "red";
                break;
            case 1 :
                name = "green";
                break;
            case 0 :
                name = "blue";
        }
        imshow (name, planes[i]);
    }
    cv::waitKey();

    int histSize = 256;                             //  У меня в каждом канале 8-битная кодировка цвета
    float range[]= {0, 255};                        //  т.е. кодируется 2^8^3 = 16 777 216 цветов
    const float* pRange = range;
    int channels[] = {0};

    cv::Mat rHist, bHist, gHist;
    //calcHist (указатель на входные данные ,число каналов, массив номеров каналов, cv::Mat(),
    //  результат, число каналов  результатата, размер гистограмы, диапазон);
    cv::calcHist(&planes[0],1,(int*)channels,cv::Mat(), bHist, 1, &histSize, &(pRange));
    cv::calcHist(&planes[1],1,(int*)channels,cv::Mat(), gHist, 1, &histSize, &(pRange));
    cv::calcHist(&planes[2],1,(int*)channels,cv::Mat(), rHist, 1, &histSize, &(pRange));

    int hist_w = 512, hist_h=400;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0,0,0));
    //  Теперь приведём все гистограмы к одному масштабу
    normalize(bHist, bHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(gHist, gHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(rHist, rHist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i=1; i<histSize; i++)
    {
        //  Нарисуем все гисторграмы элементами линий
        cv::line (histImage, cv::Point(bin_w*(i-1), hist_h-cvRound(bHist.at<float>(i-1)) ),
                  cv::Point(bin_w*(i), hist_h-cvRound(bHist.at<float>(i)) ),
                  cv::Scalar(255,0,0), 2,8,0);
        cv::line (histImage, cv::Point(bin_w*(i-1), hist_h-cvRound(gHist.at<float>(i-1)) ),
                  cv::Point(bin_w*(i), hist_h-cvRound(gHist.at<float>(i)) ),
                  cv::Scalar(0,255,0), 2,8,0);
        cv::line (histImage, cv::Point(bin_w*(i-1), hist_h-cvRound(rHist.at<float>(i-1)) ),
                  cv::Point(bin_w*(i), hist_h-cvRound(rHist.at<float>(i)) ),
                  cv::Scalar(0,0,255), 2,8,0);
    }

    cv::imshow ("hist",histImage);
    cv::waitKey();


    return 0;
}


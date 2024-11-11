#include <iostream>
#include <vector>
#include <opencv2/core.hpp> // core section, as here are defined the basic building blocks of the library
#include <opencv2/highgui.hpp> // highgui module, as this contains the functions to show an image in a window
#include <opencv2/imgcodecs.hpp> // imgcodecs module, which provides functions for reading and writing
#include <opencv2/objdetect/aruco_detector.hpp>
#include<opencv2/imgproc/imgproc.hpp>

// using namespace cv;
using namespace std;

cv::Point2f middle_point(cv::Point2f point1, cv::Point2f point2){
    // Initialize return vector 
    cv::Point2f mdl_point;
    // x coord
    mdl_point.x = ((point2.x+point1.x) / 2); 
    mdl_point.y = ((point2.y+point1.y) / 2); 

    return mdl_point;
}

int main(){
    // Initiate image 
    cv::Mat markerImage;
    // List of each detected marker  
    std::vector<int> markerIds;
    // list of corners of the markers detected (clockwise startig top left)
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    
    // Initiate the detector parameters
    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    // Initiate predefined aruco dictionary
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    // Initiate aruco detector    
    cv::aruco::ArucoDetector detector(dictionary, detectorParams);

    // Read input image 
    markerImage = cv::imread("../aruco_test.jpeg");
    // Run detector
    detector.detectMarkers(markerImage, markerCorners, markerIds, rejectedCandidates);
    // Draw detections  
    cv::Mat outputImage = markerImage.clone();
    cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);

    // Define interest id 
    int search_id = 124;

    // Define detected state
    bool detected = 0;

    // Store detected corners
    std::vector<cv::Point2f> detected_aruco;

    // Get the corners of the marker with a specific id 
    for (int i=0; i < markerIds.size();i++){
        if (markerIds[i] == search_id ){
            detected_aruco = markerCorners[i];
            detected = 1;
        }
    }


    if (detected){
        // compute center
        cv::Point2f center;
        center = middle_point(detected_aruco[0],detected_aruco[2]);
        cv::circle(outputImage, center,7, cv::Scalar(255, 0, 0), 2);

        std::cout << "aruco with id: " << search_id << " was detected on: (" << center.x << "," << center.y << ")" << std::endl;
    }

    cv::imwrite("../out.jpg", outputImage);


    // std::cout << "id: " << markerIds[0] << std::endl;

    return 0;
}
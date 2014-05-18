//
//  smootour.h
//  smootour-test
//
//  Created by Dustin Freeman on 17-05-14.
//  Copyright (c) 2014 dustinfreeman. All rights reserved.
//

#ifndef smootour_test_smootour_h
#define smootour_test_smootour_h

#include <vector>
#include <opencv2/opencv.hpp>

#define SMOO_DEFAULT_SMOOTH_AMOUNT 0.2

class Smootour {
protected:
    float smooth_amount;

    cv::Mat implicit_image;
    //from which we get the implicit surface
    
public:
    Smootour(int rows, int cols);
    
    void update(cv::Mat thresholded_image);
    
    std::vector<std::vector<cv::Point> > get_contours();
    
    cv::Mat get_implicit_image();
};

#endif

Smootour::Smootour(int rows, int cols) {
    smooth_amount = SMOO_DEFAULT_SMOOTH_AMOUNT;
    
    implicit_image = cv::Mat::zeros(rows, cols, CV_8UC1);
}

void Smootour::update(cv::Mat thresholded_image) {
    //smoothly add the thresholded_image to our implicit image
    //this assumes our thresholded_image is 0 or 1.
    
    implicit_image = thresholded_image.clone();
}

std::vector<std::vector<cv::Point> > Smootour::get_contours() {
    //do thresholding on implicit_image, return contours on either
    //side of 0.5
    
    cv::Mat thresholded_implicit_image;
    cv::threshold(implicit_image, thresholded_implicit_image, 0.5f, 1, cv::THRESH_BINARY);
    
    std::vector<std::vector<cv::Point> > smooth_contours;
    cv::findContours(thresholded_implicit_image, smooth_contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE );
    
    return smooth_contours;
}

cv::Mat Smootour::get_implicit_image() {
    return implicit_image;
}



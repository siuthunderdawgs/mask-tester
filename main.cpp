/*
 * main.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: steven
 */

#include <cv.h>
#include <highgui.h>

#include <iostream>

#include "MaskConsistencyChecker.h"

int main(int argc, char** argv)
{
	const char* filename_truth;
	const char* filename_test;

	if(argc >= 3)
	{
		filename_truth = argv[1];
		filename_test = argv[2];
	}
	else
	{
		filename_truth = "truth.jpg";
		filename_test = "test.jpg";
	}

	cv::Mat image_truth = cv::imread(filename_truth);
	cv::Mat image_test = cv::imread(filename_test);


	if(image_truth.empty())
	{
	 std::cout << "ERROR: Cannot open " << filename_truth << std::endl;
	 return -1;
	}

	if(image_test.empty())
	{
		 std::cout << "ERROR: Cannot open " << filename_test << std::endl;
		 return -1;
	}

	MaskConsistencyChecker checker;
	checker.SetMaskTruth(image_truth);
	checker.SetMaskTest(image_test);

	if(!checker.CheckMaskSizes())
	{
		std::cout << "Error: Masks sizes do not match!\n";
		return 1;
	}

	checker.CheckMaskConsistency();

	cv::Mat mask_result = checker.GetMaskResult();

	cv::namedWindow("Mask Image");
	cv::imshow("Mask Image", mask_result);

	std::cout << "Correct: " << checker.GetPercentCorrect()*100 << " %" << std::endl;
	std::cout << "False Pos: " << checker.GetPercentFalsePositive()*100 << " %" << std::endl;
	std::cout << "False Neg: " << checker.GetPercentFalseNegative()*100 << " %" << std::endl;

	while(char(cv::waitKey(1)) != 'q'){}

	return 0;
}

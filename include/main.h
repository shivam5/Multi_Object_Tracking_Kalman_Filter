#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include "utils.h"
#include "kalman.h"
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
using namespace std;
// using namespace cv;

#define SIZE 3
#define euc_threshold 0.0001 //Safe threshold below which two objects can be associated
#define safe_IOU_threshold 0.45 //Safe IOU thresholg below which two object can be associated
#define state_size 8
#define observation_size 4

//Function to read the current input_file, and update the current observation (observations[0])
map <int, Matrix <float> > readframe(string input_file, map <int, Matrix <float> > previous_state);

#endif
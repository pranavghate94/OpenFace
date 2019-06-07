#pragma once

#include <dlib/image_processing/frontal_face_detector.h>

#include "LandmarkCoreIncludes.h"

#include <FaceAnalyser.h>
#include <GazeEstimation.h>

#include <ImageCapture.h>
#include <Visualizer.h>
#include <VisualizationUtils.h>
#include <RecorderOpenFace.h>
#include <RecorderOpenFaceParameters.h>
#include <string>
#include "Base64.h"

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 

#ifndef CONFIG_DIR
#define CONFIG_DIR "~"
#endif

class LandmarkExtractor {
public:
	LandmarkExtractor();
	~LandmarkExtractor();
	void SetupExtractor();
	void SetImage(std::string base64);
	void ExtractFeatures();
private:
	LandmarkDetector::FaceModelParameters *det_parameters;
	LandmarkDetector::CLNF *face_model;
	FaceAnalysis::FaceAnalyserParameters *face_analysis_params;
	FaceAnalysis::FaceAnalyser *face_analyser;
	cv::Mat rgb_image;
	cv::Mat_<uchar> grey_image;
};
#include "LandmarkExtractor.h"

LandmarkExtractor::LandmarkExtractor() {
	
}

void LandmarkExtractor::SetupExtractor() {
	det_parameters = new LandmarkDetector::FaceModelParameters;
	face_model = new LandmarkDetector::CLNF;
	face_analysis_params = new FaceAnalysis::FaceAnalyserParameters;
	face_analyser = new FaceAnalysis::FaceAnalyser(*face_analysis_params);
	face_analysis_params->OptimizeForImages();
	std::cout << "Openface Landmark Extractor set up!" << std::endl;
}

LandmarkExtractor::~LandmarkExtractor() {
	delete face_analyser;
	delete face_analysis_params;
	delete face_model;
	delete det_parameters;
}
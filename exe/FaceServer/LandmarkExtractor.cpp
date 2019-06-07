#include "LandmarkExtractor.h"



LandmarkExtractor::LandmarkExtractor() {
	
}

void LandmarkExtractor::SetupExtractor() {
	det_parameters = new LandmarkDetector::FaceModelParameters;
	face_model = new LandmarkDetector::CLNF(det_parameters->model_location);
	face_analysis_params = new FaceAnalysis::FaceAnalyserParameters;
	face_analyser = new FaceAnalysis::FaceAnalyser(*face_analysis_params);
	face_analysis_params->OptimizeForImages();
	LOG("Openface Landmark Extractor set up!");
}

void LandmarkExtractor::SetImage(std::string encoded_string) {
	auto decoded_string = base64_decode(encoded_string);
	std::vector<uchar> data(decoded_string.begin(), decoded_string.end());
	rgb_image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
	cv::cvtColor(rgb_image, grey_image, cv::COLOR_BGR2GRAY);
	LOG("Converted from Base64!");
}

//Just for Test TBH!
void LandmarkExtractor::ExtractFeatures() {
	LOG("Hello!");
	bool success = LandmarkDetector::DetectLandmarksInImage(rgb_image, *face_model, *det_parameters, grey_image);
	if (success) {
		//Print AU Confidences
		face_analyser->PredictStaticAUsAndComputeFeatures(rgb_image, face_model->detected_landmarks);
		auto aus_intensity = face_analyser->GetCurrentAUsReg();
		auto aus_presence = face_analyser->GetCurrentAUsClass();
		LOG("Extracted Feature!");
	}
	else {
		LOG("Could not Detect Any Landmarks!");
	}
}

LandmarkExtractor::~LandmarkExtractor() {
	delete face_analyser;
	delete face_analysis_params;
	delete face_model;
	delete det_parameters;
}
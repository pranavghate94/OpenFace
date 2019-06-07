#pragma once

#include <vector>

class FacePacket {
public:
	FacePacket();
	~FacePacket();
	void setConfidences(std::vector<float> confidences);
	std::vector<float> confidences;
};
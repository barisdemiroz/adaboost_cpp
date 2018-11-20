#pragma once
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

class Classifier
{
public:
	explicit Classifier(const std::string& filepath);
	void classify(const cv::Mat1d& featureVals, std::vector<double>& scores) const;

	const cv::Mat1i& getFids() {
		return fids;
	}

private:
	int depth, nWeak, nNodes;
	cv::Mat1i fids;
	cv::Mat1d thresholds;
	cv::Mat1d logL;

	static void read(std::ifstream& in, cv::Mat& m)
	{
		in.read(reinterpret_cast<char*>(m.data), m.total() * m.elemSize());
	}
};


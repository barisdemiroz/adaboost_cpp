#pragma once

#include <fstream>

namespace cv {
	class Mat;
}

template<typename T>
void write_primitive(std::ostream& stream, const T& value)
{
	stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}


template<typename T>
void read_primitive(std::istream& stream, T& value)
{
	stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}


void write(std::ostream& out, const cv::Mat& m);
void read(std::istream& in, cv::Mat& m);
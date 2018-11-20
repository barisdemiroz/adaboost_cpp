#pragma once

#include <opencv2/opencv.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>

inline double pow2(double x)
{
	return x*x;
}

inline double norm(double x, double y)
{
	return std::sqrt(x*x + y*y);
}

inline double norm(int x, int y)
{
	return norm(double(x), double(y));
}

inline double atan2pos(double y, double x)
{
	return cv::fastAtan2(y, x) * M_PI / 180;
}

inline float sigmoid(float x) {
	return 1 / (1 + std::exp(-x));
}

inline cv::Point2d polarToCart(double radius, double angle)
{
	return cv::Point2d(radius * cos(angle), radius * sin(angle));
}

inline void cartToPolar(double x, double y, double& r, double& angle)
{
	r = std::sqrt(x*x + y*y);
	angle = atan2pos(y, x);
}

inline void cartToPolar(const cv::Point2d& p, double& r, double& angle)
{
	cartToPolar(p.x, p.y, r, angle);
}

static bool endsWith(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


inline void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
		elems.push_back(item);
}

inline std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


inline std::string stripFileExtension(const std::string& filepath)
{
	auto i = filepath.find_last_of('.');
	return filepath.substr(0, i);
}


template<typename T>
inline void append(const std::vector<T>& src, std::vector<T>& dst)
{
	dst.reserve(dst.size() + src.size());
	dst.insert(dst.end(), src.begin(), src.end());
}

inline void checkState(bool condition, const std::string& message)
{
	if (!condition) {
		std::cerr << message << std::endl;
		throw std::runtime_error(message);
	}
}

inline void dumpCsv(const std::string& filepath, const std::vector<double>& vals)
{
	std::ofstream out(filepath);
	for (double v : vals)
		out << v << ", ";
	out.close();
}
#include "persistence.h"

#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



void write(ostream& out, const Mat& m)
{
	write_primitive(out, m.rows);
	write_primitive(out, m.cols);
	write_primitive(out, m.type());
	const size_t bytes = m.cols * m.elemSize();
	for (int i = 0; i < m.rows; i++)
		out.write(reinterpret_cast<const char*>(m.ptr(i, 0)), bytes);
}


void read(istream& in, Mat& m)
{
	int rows, cols, type;
	read_primitive(in, rows);
	read_primitive(in, cols);
	read_primitive(in, type);
	m.create(rows, cols, type);
	const size_t bytes = m.cols * m.elemSize();
	for (int i = 0; i < m.rows; i++)
		in.read(reinterpret_cast<char*>(m.ptr(i, 0)), bytes);
}
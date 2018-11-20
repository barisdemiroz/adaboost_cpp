#include "Classifier.h"

#include "persistence.h"
#include "util.h"
#include <fstream>
#include <numeric>

using namespace std;
using namespace cv;

Classifier::Classifier(const std::string& filepath)
{
	ifstream in(filepath, ios::binary);
	checkState(bool(in), "Can't load classifier from: " + filepath);

	cout << "Classifier: Reading " << filepath << endl;

	read_primitive(in, depth);
	cout << "WARNING: using fixed depth=2 due to variable .treeDepth field.\n";
	depth = 2;

	read_primitive(in, nWeak);

	// 2^n == (1 << n)
	nNodes = (1 << depth) - 1;
	int nLeaves = 1 << depth;

	fids.create(nWeak, nNodes);
	thresholds.create(nWeak, nNodes);
	logL.create(nWeak, nLeaves);

	read(in, fids);
	read(in, thresholds);
	read(in, logL);
}


void Classifier::classify(const cv::Mat1d& featureVals, vector<double>& scores) const
{
	scores.resize(featureVals.rows);


#pragma omp parallel for
	for (int i = 0; i < featureVals.rows; ++i)
	{
		vector<double> likelihoods(nWeak);

		for (int n = 0; n < nWeak; ++n)
		{
			int ix = 0;
			for (int d = 0; d < depth; ++d)
			{
				if (featureVals(i, fids(n, ix)) < thresholds(n, ix))
					ix = 2 * ix + 1; // left
				else
					ix = 2 * ix + 2; // right
			}

			likelihoods[n] = logL(n, ix-nNodes);
		}

		scores[i] = std::accumulate(likelihoods.begin(), likelihoods.end(), 0.0);
	}
}

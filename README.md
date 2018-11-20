Why?
====
During my PhD studies I needed to use the Adaboost classifier in the [Piotr's toolbox](https://github.com/pdollar/toolbox/) from C++. It is extremely fast, thanks to the ingenious work by Ron Appel and others [1]. But I was too lazy to implement the training part. So, instead I train in MATLAB using their  `adaBoostTrain()` function and use the resulting classifier in C++.

Usage
=====

First train your model with `adaBoostTrain()` function in the Piotr's Computer Vision Matlab Toolbox. Then convert it to the binary format with `convertClassifier()` function.

```matlab
model = adaBoostTrain(trainNeg, trainPos, params);
convertClassifier(model, 'model.bin');
```

Then in C++ you can load that file and do classification:
```cpp
Classifier classifier("model.bin");
Mat1d features(m, n);
// ... load the data into features
vector<double> scores;
classifier.classify(features, scores);
```
At the end, you will end up with a score for each row of feature `scores`


Remarks
-------
I have extracted these files from a project, so it contains some cruft. The dependencies are:
-  Piotr's Computer Vision Matlab Toolbox (you need this to train the classifier)
-  OpenCV 2.4+
-  OpenMP (optional, for parallel evaluation of features)


[1] R. Appel, T. Fuchs, P. Dollár, P. Perona; "Quickly Boosting Decision Trees – Pruning Underachieving Features Early," ICML 2013.
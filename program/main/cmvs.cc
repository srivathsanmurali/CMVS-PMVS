#include <iostream>
#include <vector>
#include <list>
#include "../base/cmvs/bundle.h"


using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " prefix maximage[=100] CPU[=4]" << endl
         << endl
         << "You should choose maximage based on the amount of memory in your machine." << endl
         << "CPU should be the number of (virtual) CPUs or cores in your machine." << endl
         << "If you want more control of the program, look into the comments inside program/main/cmvs.cc" << endl;
    exit (1);
  }

  int iNumForScore = 10;
  if (3 <= argc)
    iNumForScore = atoi(argv[2]);

  int maximage = 100;
  if (4 <= argc)
    maximage = atoi(argv[3]);

  //----------------------------------------------------------------------
  // If you want more control of the program, you can also change the
  // following two parameters.
  // scoreRatioThreshold, and coverageThreshold correspond to
  // \\lambda and \\delta in our CVPR 2010 paper.
  // Please refer to the paper for their definitions. The following are
  // brief explanations.
  //
  // CMVS tries to make sure that multi-view stereo (MVS)
  // reconstruction accuracy will be more than a certain threshold at
  // Structure-from-Motion (SfM) points. scoreRatioThreshold is this
  // threshold on the reconstruction accuracy [0, 1.0]. CMVS makes
  // sure that the ratio of "satisfied" SfM points is more than
  // coverageThreshold [0 1.0].
  //
  // Intuitively, increasing these parameters lead to more images and
  // clusters in the output.
  float scoreRatioThreshold = 0.9f;
  if (5 <= argc)
    scoreRatioThreshold = atof(argv[4]);

  float coverageThreshold = 0.7f;
  if (6 <= argc)
    coverageThreshold = atof(argv[5]);

  int CPU = 4;
  if (7 <= argc)
    CPU = atoi(argv[6]);

  bool removeImages = 0;
  if (8 <= argc)
    if(atoi(argv[7]) == 0)
      removeImages = false;
    else
      removeImages = true;

  const int pnumThreshold = 0;
  CMVS::Cbundle bundle;
  bundle.run(argv[1], maximage, iNumForScore,
             scoreRatioThreshold, coverageThreshold,
             pnumThreshold, CPU, removeImages);
}

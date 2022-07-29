
// File:        compare.cpp
// Author:      cheeren
// Date:        2018-02-25
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "qtcount.h"
#include "qtvar.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main(int argc, char *argv[])
{
    int prune = 10000;
    if (argc < 4)
    {
        fprintf(stdout, "QuadTree PNG Lossy Image Compression (compare stanley).\n");
        fprintf(stdout, "Usage:\n");
        fprintf(stdout, " %s in.png comp-count-stanley.png comp-var-stanley.png [prune]\n", argv[0]);
        fprintf(stdout, "Options:\n");
        fprintf(stdout, " prune - select level prune, default = %d\n", prune);
    }
    else
    {
        if (argc > 4)
            prune = atoi(argv[4]);
        prune = (prune > 0) ? prune : 10000;

        // read in image
        PNG origIm;
        origIm.readFromFile(argv[1]);

        // comparisons
        // count stanley
        qtcount countcomp(origIm);
        countcomp.prune(countcomp.idealPrune(prune));
        PNG countpng = countcomp.render();
        countpng.writeToFile(argv[2]);
        // var stanley
        qtvar varcomp(origIm);
        varcomp.prune(varcomp.idealPrune(prune));
        PNG varpng = varcomp.render();
        varpng.writeToFile(argv[3]);
    }

    return 0;
}


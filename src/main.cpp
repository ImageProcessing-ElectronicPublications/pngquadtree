
// File:        main.cpp
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
    char* test = "leaf";
    int prune = 1000, t, t0 = (int)test[0];
    if (argc < 3)
    {
        fprintf(stdout, "QuadTree PNG Lossy Image Compression.\n");
        fprintf(stdout, "Usage:\n");
        fprintf(stdout, " %s in.png out.png [test] [prune]\n", argv[0]);
        fprintf(stdout, "Options:\n");
        fprintf(stdout, " test - select test {leaf,var}, default = %s\n", test);
        fprintf(stdout, " prune - select level prune, default = %d\n", prune);
    }
    else
    {
        if (argc > 3)
            test = argv[3];
        if (argc > 4)
            prune = atoi(argv[4]);
        prune = (prune > 0) ? prune : 1000;

        // read in image
        PNG origIm;
        origIm.readFromFile(argv[1]);

        t = (int)test[0];
        if (t == t0)
        {
            fprintf(stdout, "test: leaf.\n");

            // use it to build a quadtree
            qtcount ti(origIm);
            qtcount tCopy(ti);

            // prune the quadtree
            tCopy.prune(prune);

            // render the quadtree
            PNG ppic = tCopy.render();
            ppic.writeToFile(argv[2]);
        }
        else
        {
            fprintf(stdout, "test: var.\n");

            // use it to build a quadtree
            qtvar vi(origIm);
            qtvar vCopy(vi);

            // prune the quadtree
            vCopy.prune(prune);

            // render the quadtree
            PNG vpic = vCopy.render();
            vpic.writeToFile(argv[2]);
        }
    }

    return 0;
}


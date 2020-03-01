

/* 
 * File:   main.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 27 February 2020, 18:34
 */

#include "volimage.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

/*
 * This is a volumetric image tool which can load a stack of 2d images
 * and manipulate them as a group.
 * 
 * Detailed information on how to invoke the application can  be found in the
 * attached READ ME file.  
 */
int main(int argc, char** argv) {
    MKHSIN035::VolImage obj;
    
    string imageBase = string(argv[1]);
    if (obj.readImages(imageBase)){
        if(argc > 2){

            string op = string(argv[2]);
            if(op == "-d"){
                int i,j;
                string outputfilename;
                istringstream (string(argv[3])) >> i;
                istringstream (string(argv[4])) >> j;
                outputfilename = string(argv[5]);
                obj.diffmap(i, j, outputfilename);
                cout<<"Number of images: "<<obj.getnumOfImages()<<endl;
                cout<<"Number of bytes required: "<<obj.volImageSize()<<endl;
                cout<<"Difference map between images "<< i <<" and "<<j<<" completed "
                        "successfully. Output written to file: "<<outputfilename<<".raw"<<endl;

            }
            else if(op == "-x"){
                int i;
                istringstream(string(argv[3])) >> i;
                string outputfilename = string(argv[4]);
                obj.extract(i, outputfilename);
                cout<<"Number of images: "<<obj.getnumOfImages()<<endl;
                cout<<"Number of bytes required: "<<obj.volImageSize()<<endl;
                cout<<"Slice extracted and written to file: "<<outputfilename<<".raw"<<endl;
            }

        }
        else{
            cout<<"Number of images: "<<obj.getnumOfImages()<<endl;
            cout<<"Number of bytes required: "<<obj.volImageSize()<<endl;

        }
    }
    return 0;
}


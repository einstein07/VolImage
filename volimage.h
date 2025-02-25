

/* 
 * File:   volimage.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 27 February 2020, 18:35
 */

#ifndef VOLIMAGE_H
#define VOLIMAGE_H
#include <vector>
#include <string>
namespace MKHSIN035{
    class VolImage{
    private: //private members
        int width, height; //width and height of image stack
        std::vector<unsigned char**> slices; //data for each slice, in order
        
    public: //public members
        VolImage(); //default constructor
        ~VolImage(); //destructor
        
        //populate the object with images in stack and
        //set member variables 
        bool readImages(std::string baseName);
        
        //compute difference map and write out
        void diffmap(int sliceI, int sliceJ, std::string output_prefix);
        
        //extract sliceId and write to output
        void extract(int sliceId, std::string output_prefix);
        
        //extracts an image along row i of the volume, accross all slices
        //and writes this out to an output file
        void extractRow(int i, std::string output_prefix);
        
        //number of bytes used to store image data bytes
        //and pointers 
        int volImageSize(void);
        
        //returns total number of images
        int getnumOfImages(void);
        
    };
}

#endif /* VOLIMAGE_H */


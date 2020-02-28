/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "volimage.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cstring>

using namespace std;
MKHSIN035::VolImage::VolImage(){
    this->height = 0;
    this->width = 0;
}

MKHSIN035::VolImage::~VolImage(){
    
}

bool MKHSIN035::VolImage::readImages(std::string baseName){
    std::string headerfile = "brain_mri_raws/"+baseName+".data";
    std::string filename = "brain_mri_raws/"+baseName;
    ifstream in(headerfile.c_str());
    string line;
    unsigned char** arr;
    
    if(!in){
        std::cout<<"Could not open "<<headerfile<<endl;
    }
    else{
        std::cout<<"File opened"<<endl;
        while(getline(in, line)){
            istringstream iss(line);
            vector<string> results(istream_iterator<string>{iss}, 
                    istream_iterator<string>());
            int numimages;
            
            istringstream(results[0])>>VolImage::width;
            istringstream(results[1])>>VolImage::height;
            istringstream(results[2])>>numimages;
            cout<<"Number of files: "<<numimages<<" Number of rows: "<<VolImage::height<<" Number of columns: "<<VolImage::width<<endl;
            
            for (int i = 0; i < numimages; i++){
                arr = new unsigned char*[VolImage::height];
                    
                for (int c = 0; c < VolImage::height; c++){
                    arr[c] = new unsigned char[VolImage::width];
                }
                string num; //stores the file number, in string format
                stringstream ss;
                ss<<i;
                num = ss.str();
                std::string slicefile = filename+""+num+".raw";
                ifstream slicein(slicefile.c_str(), ios::binary);
                if (!slicein){
                    cout<<"Could not open "<<slicefile<<endl;
                }
                else{
                    int row = 0;
                    while(getline(in, line)){
                        
                        istringstream isss(line);
                        vector<unsigned char> sliceresults(istream_iterator<unsigned char>{isss},
                                 istream_iterator<unsigned char>());
                        for(int k = 0; k < VolImage::width; k++){
                            arr[row][k] = sliceresults[k];
                        }
                        row++;
                    }
            
                }
                slices.push_back(arr);
                
            }
            
        }
        cout<<"Read "<<slices.size()<<" slices"<<endl;
        
    }
    
    
    
    
}

void MKHSIN035::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
    
}

void MKHSIN035::VolImage::extract(int sliceId, std::string output_prefix){
    
}

int MKHSIN035::VolImage::volImageSize(void){
    
}




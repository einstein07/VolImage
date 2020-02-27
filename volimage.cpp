/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "volimage.h"
#include <string>
#include <fstream>
#include <iterator>

using namespace MKHSIN035;
using namespace std;
VolImage::VolImage(){
    this->height = 0;
    this->width = 0;
}

VolImage::~VolImage(){
    
}

bool VolImage::readImages(std::string baseName){
    std::string headerfile = "brain_mri_raws/"+baseName+".data";
    
    ifstream in(headerfile.c_str());
    string line;
    if(!in){
        cout<<"Could not open "<<headerfile<<endl;
    }
    else{
        cout<<"File opened"<<endl;
        while(getline(in, line)){
            istringstream iss(line);
            vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
            int width, height, numimages;
            
            istringstream(results[0])>>width;
            istringstream(results[1])>>height;
            istringstream(results[2])>>numimages;
            
            for (int i = 0; i < numimages; i++){
                
            }
            
        }
    }
    
    
    
    
}

void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
    
}

void VolImage::extract(int sliceId, std::string output_prefix){
    
}

int VolImage::volImageSize(void){
    
}




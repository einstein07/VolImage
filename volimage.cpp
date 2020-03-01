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
        return false;
    }
    else{
        int numimages;

        while(getline(in, line)){
            istringstream iss(line);
            vector<string> results(istream_iterator<string>{iss}, 
                    istream_iterator<string>());
            
            istringstream(results[0])>>VolImage::width;
            istringstream(results[1])>>VolImage::height;
            istringstream(results[2])>>numimages;
        }
            for (int i = 0; i < numimages; i++){
                arr = new unsigned char*[VolImage::height];
                    
                for (int c = 0; c < VolImage::height; c++){
                    arr[c] = new unsigned char[VolImage::width];
                }
                string num; //stores the file number, in string format
                stringstream ss;
                ss<<i;
                num = ss.str();
                std::string slicefile = filename+num+".raw";
                ifstream slicein(slicefile.c_str(), ios::binary);
                if (!slicein){
                    cout<<"Could not open "<<slicefile<<endl;
                    return false;
                }
                else{

                    int row = 0, col = 0;
                    
                    unsigned char value;
                    char buf[sizeof(unsigned char)];
                    while(slicein.read(buf,sizeof(buf))){
                        memcpy(&value, buf, sizeof(value));
                        arr[row][col] = value;

                        if(col == (width-1)){
                            col = 0;
                            row++;
                        }
                        else{
                            col++;    

                        }

                    }
                    slicein.close();
                    slices.push_back(arr);
                    
                }
                
            }
            
        
        return true;
    }
    
    
    
    
}

void MKHSIN035::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
    unsigned char** arr = new unsigned char*[VolImage::height];
    int sliceId = slices.size();
    for(int i = 0; i < height; i++){
        
        arr[i] = new unsigned char[width];
        
        for(int j = 0; j < width; j++){
            arr[i][j] = (unsigned char)(abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
            
        }
          
    }
    slices.push_back(arr);
    string filename = output_prefix;
    extract(sliceId, filename);
    slices.erase(slices.begin()+sliceId); //remove the last element which represents the difference between two slices.
    
}

void MKHSIN035::VolImage::extract(int sliceId, std::string output_prefix){
    

    /*
     * The following block of code writes to the width, height and number of 
     * slices, which is 1 in this case, in that order to the header file.
     */
    string header = output_prefix+".data"; 
    ofstream outheader(header.c_str());

    string line; //line to write
    if(!outheader){
        cout<<"Could not open "<<header<<endl;
    }
    else{
        string w, h;
        stringstream ssw;
        ssw<<VolImage::width;
        w = ssw.str();
        stringstream ssh;
        ssh<<VolImage::height;
        h = ssh.str();
        line = w +" "+ h +" 1";
        outheader<<line;
        outheader.close();
    }
    string outputfile = output_prefix+".raw";
    ofstream output(outputfile.c_str(), ios::binary);
    if(!output){
        cout<<"Could not open "<<outputfile<<endl;
    }
    else{
        for(int j = 0; j < VolImage::height; j++ ){
            for(int k = 0; k < VolImage::width; k++){
                output.write(reinterpret_cast<char*>(&slices[sliceId][j][k]), sizeof(slices[sliceId][j][k]));
            }

        }
        output.close();
    }
    
    
}

void MKHSIN035::VolImage::extractRow(int i, string output_prefix){
    
    string outputfile = output_prefix+".raw";
    ofstream output(outputfile.c_str(), ios::binary);
    if(!output){
        cout<<"Could not open "<<outputfile<<endl;
    }
    else{
        for(int j = 0; j < slices.size(); j++){
                for(int l = 0; l < width; l++){
                    output.write(reinterpret_cast<char*>(&slices[j][i][l]), sizeof(slices[j][i][l]));
                }
            
        }
    }
    output.close();
     /*
     * The following block of code writes to the width, height and number of 
     * slices, which is 1 in this case, in that order to the header file.
     */
    string header = output_prefix+".data"; 
    ofstream outheader(header.c_str());

    string line; //line to write
    if(!outheader){
        cout<<"Could not open "<<header<<endl;
    }
    else{
        string w, h;
        stringstream ssw;
        ssw<<VolImage::width;
        w = ssw.str();
        stringstream ssh;
        ssh<<VolImage::height;
        h = ssh.str();
        line = w +" "+ slices.size() +" 1";
        outheader<<line;
        outheader.close();
    }
 }
    


int MKHSIN035::VolImage::volImageSize(void){
    int bytes = slices.size() * (height * width * sizeof(char) + height * sizeof(char*))
    +slices.size() * sizeof(char*);
    return bytes;
}

int MKHSIN035::VolImage::getnumOfImages(){
    return slices.size(); //the number of images corresponds to the number of slices
}




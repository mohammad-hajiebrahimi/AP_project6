#include <bits/stdc++.h>
using namespace std;
#define sep ' '
#define endl '\n'
#define tab '\t'
const string BLUR = "-B";
const string SHARPEN = "-S";
const string EMBOSS = "-E";
const string INVERT = "-I";
const string GRAYSCALE = "-G";
const string DELIMITER = ":";
#include "src/bmp.cpp"
#include "src/Filters.cpp"
#include "src/ColorFilter.cpp"
#include "src/KernelFilter.cpp"
vector<pair<string,string>> input_filters(string input_bmp,int argc, char **argv){
    Bmp image;
    read(image,input_bmp);
    vector<pair<string,string>> filters;
    for (int i=1;i<argc;i++){
        string input;
        if (strcmp(argv[i], "-B") == 0){
            input = "-B";
        }
        else if (strcmp(argv[i], "-S") == 0){
            input = "-S";
        }
        else if (strcmp(argv[i], "-E") == 0){
            input = "-E";
        }
        else if (strcmp(argv[i], "-I") == 0){
            input = "-I";
        }
        else if (strcmp(argv[i], "-G") == 0){
            input = "-G";
        }
        if (i!=argc-1){
            string str(argv[i+1]);
            if(str.find(DELIMITER)<str.length()){
                filters.push_back(make_pair(input,str));
            }
            else if( input[0]=='-' ){
                str = "0:0:"+to_string(image.infoHdr.width)+":"+to_string(image.infoHdr.height);
                filters.push_back(make_pair(input,str));
            }
        }
        else if(input[0]=='-'){
            string str = "0:0:"+to_string(image.infoHdr.width)+":"+to_string(image.infoHdr.height);
            filters.push_back(make_pair(input,str));
        }
    }
    return filters;
}
void do_filters(string input_bmp,string output_bmp,vector<pair<string,string>> filters){
    Bmp image;
    read(image, input_bmp);
    for(int i =0;i<filters.size();i++){
        string input;
        if (filters[i].first== "-B"){
            Gaussian gaussian(image,filters[i].second);
            gaussian.apply_filter();
            image = gaussian.get_result();
        }
        else if (filters[i].first== "-S"){
            Sharpen sharpen(image,filters[i].second);
            sharpen.apply_filter();
            image = sharpen.get_result();
        }
        else if (filters[i].first== "-E"){
            Emboss emboss(image,filters[i].second);
            emboss.apply_filter();
            image = emboss.get_result();
        }
        else if (filters[i].first== "-I"){
            Invert invert(image,filters[i].second);
            invert.apply_filter();
            image = invert.get_result();
        }
        else if (filters[i].first== "-G"){
            Grayscale gray(image,filters[i].second);
            gray.apply_filter();
            image = gray.get_result();
        }
    }
    write(image,output_bmp);
}
int main(int argc, char **argv) {
    string inputfile,outputfile;
    vector<pair<string,string>> filters;
    while(cin>>inputfile>>outputfile){
        filters = input_filters(inputfile,argc,argv);
        do_filters(inputfile,outputfile,filters);
    }
    return 0;
}

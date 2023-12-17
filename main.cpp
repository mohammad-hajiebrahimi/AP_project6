#include <bits/stdc++.h>

#include "src/bmp.cpp"

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


/*
To work with BMP files, first include the header and create an instance of the Bmp struct.
Now there are 3 functions we are interested in: create, read, write
These functions take the Bmp struct instance as the first argument.

To read a BMP file: read(bmp, "file.bmp");
To write the modified in-memory BMP to a file: write(bmp, "out.bmp");
To create a new BMP file: create(bmp, width, height);

We can view images as 2D vectors of Pixel structs.
The Pixel struct is just a red-green-blue tuple.

The structure we work with is the 'data' field of 'struct Bmp'
bmp.data[0][0].red // returns a value between 0 and 255
The (0, 0) pixel is the top-left corner of the image.
So we have data[row][column]
The bottom-right pixel is: bmp.data[bmp.infoHdr.height - 1][bmp.infoHdr.width - 1]
*/
#include "src/Filters.cpp"
#include "src/ColorFilter.cpp"

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
                cout<<input<<sep<<str<<endl;
                filters.push_back(make_pair(input,str));
            }
            else if( input[0]=='-' ){
                str = "0:0:"+to_string(image.infoHdr.width)+":"+to_string(image.infoHdr.height);
                cout<<input<<sep<<str<<endl;
                filters.push_back(make_pair(input,str));
            }
        }
        else if(input[0]=='-'){
            string str = "0:0:"+to_string(image.infoHdr.width)+":"+to_string(image.infoHdr.height);
            cout<<input<<sep<<str<<endl;
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
            input = BLUR;
        }
        else if (filters[i].first== "-S"){
            input = SHARPEN;
        }
        else if (filters[i].first== "-E"){
            input = EMBOSS;
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
        cout<<inputfile<<sep<<outputfile<<endl;
        filters = input_filters(inputfile,argc,argv);
        do_filters(inputfile,outputfile,filters);
    }
    return 0;
}

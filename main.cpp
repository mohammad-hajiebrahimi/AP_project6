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
class Filter{
public:
    Filter(string bmpfile,string view);
    void init_filter(string bmpfile,string view);
private:
    Bmp input_bmp;
    int x_view;
    int y_view;
    int h_view;
    int w_view;
};
void Filter::init_filter(string bmpfile,string view){
    vector<string> v;
    stringstream ss(view);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ':');
        v.push_back(substr);
    }
    x_view = stoi(v[0]);
    y_view = stoi(v[1]);
    w_view = stoi(v[2]);
    h_view = stoi(v[3]);
    read(input_bmp, bmpfile);
}
Filter::Filter(string bmpfile, string view){
    init_filter(bmpfile,view);
}
void do_filters(int argc, char **argv){
    for (int i=0;i<argc;i++){
        string input;
        if (strcmp(argv[i], "-B") == 0){
            input = BLUR;
        }
        else if (strcmp(argv[i], "-S") == 0){
            input = SHARPEN;
        }
        else if (strcmp(argv[i], "-E") == 0){
            input = EMBOSS;
        }
        else if (strcmp(argv[i], "-I") == 0){
            input = INVERT;
        }
        else if (strcmp(argv[i], "-G") == 0){
            input = GRAYSCALE;
        }
        if (i!=argc-1){
            string str(argv[i+1]);
            if(str.find(DELIMITER)<str.length()){
                //go and filter
                cout<<input<<sep<<str;
            }
            else{cout<<input<<endl;}
        }
        else{
            cout<<input<<endl;
        }
    }
}
int main(int argc, char **argv) {
    string inputfile,outputfile;
    while(cin>>inputfile>>outputfile){
        cout<<inputfile<<sep<<outputfile;
        do_filters(argc,argv);
    }
    return 0;
}

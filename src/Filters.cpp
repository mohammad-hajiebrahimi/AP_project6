#include "Filters.hpp"

void Filter::init_filter(Bmp bmpfile,string view){
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
    input_bmp = bmpfile;
}
Filter::Filter(Bmp bmpfile, string view){
    init_filter(bmpfile,view);
}

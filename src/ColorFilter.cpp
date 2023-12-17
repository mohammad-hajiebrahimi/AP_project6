#include "ColorFilter.hpp"
ColorFilter::ColorFilter(Bmp bmpfile,string view)
           :Filter(bmpfile,view)
{
    create(result_filter,input_bmp.infoHdr.width,input_bmp.infoHdr.height);
    for(int i=0;i<input_bmp.infoHdr.width;i++){
        for(int j=0;j<input_bmp.infoHdr.height;j++){
            result_filter.data[j][i] = input_bmp.data[j][i];
        }
    }
}
void ColorFilter::apply_filter(){
    for(int i=x_view;i<x_view+w_view;i++){
        for(int j=y_view;j<y_view+h_view;j++){
            result_filter.data[j][i]=set_cell(j,i);
        }
    }
}
class Grayscale:public ColorFilter{
public:
    Grayscale(Bmp bmpfile,string view);
    virtual Pixel set_cell(int row, int col){
        int gray = (input_bmp.data[row][col].red + input_bmp.data[row][col].grn + input_bmp.data[row][col].blu)/3;
        return Pixel(gray,gray,gray);
    }
    Bmp get_result(){return result_filter;}
};
Grayscale::Grayscale(Bmp bmpfile,string view)
      :ColorFilter(bmpfile,view)
{
}
class Invert:public ColorFilter{
public:
    Invert(Bmp bmpfile,string view);
    virtual Pixel set_cell(int row, int col){
        return Pixel(255-input_bmp.data[row][col].red,255-input_bmp.data[row][col].grn,255-input_bmp.data[row][col].blu);
    }
    Bmp get_result(){return result_filter;}
};
Invert::Invert(Bmp bmpfile,string view)
      :ColorFilter(bmpfile,view)
{
}

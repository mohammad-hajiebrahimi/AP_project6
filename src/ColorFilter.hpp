#ifndef COLORFILTER_HPP_INCLUDE
#define COLORFILTER_HPP_INCLUDE
class ColorFilter:public Filter{
public:
    ColorFilter(Bmp bmpfile,string view);
    virtual Pixel set_cell(int row,int col)=0;
    virtual void apply_filter();
protected:
    Bmp result_filter;
};
#endif

#ifndef FILTER_HPP_INCLUDE
#define FILTER_HPP_INCLUDE
class Filter{
public:
    Filter(Bmp bmpfile,string view);
    void init_filter(Bmp bmpfile,string view);
    int get_x_view(){return x_view;}
    int get_y_view(){return y_view;}
    int get_h_view(){return h_view;}
    int get_w_view(){return w_view;}
protected:
    Bmp input_bmp;
    int x_view;
    int y_view;
    int h_view;
    int w_view;
};
#endif

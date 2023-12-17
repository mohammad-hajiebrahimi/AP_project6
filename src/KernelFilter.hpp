#ifndef KERNELFILTER_HPP_INCLUDE
#define KERNELFILTER_HPP_INCLUDE
class KernelFilter: public Filter{
public:
    KernelFilter(Bmp bmpfile,string view);
    virtual void set_filter_kernel() = 0;
    virtual void apply_filter();
    Bmp get_result(){return result_filter;}
protected:
    vector<vector<int>> kernel_matrix;
    float normal_factor;
    Bmp result_filter;
};

class Gaussian:public KernelFilter{
public:
    Gaussian(Bmp bmpfile,string view);
    void set_filter_kernel(){
        kernel_matrix = {{1,2,1},{2,4,2},{1,2,1}};
        normal_factor = 16;

    }
};
Gaussian::Gaussian(Bmp bmpfile,string view)
        :KernelFilter(bmpfile,view)
{
}
class Sharpen:public KernelFilter{
public:
    Sharpen(Bmp bmpfile,string view);
    void set_filter_kernel(){
        kernel_matrix = {{0,-1,0},{-1,5,-1},{0,-1,0}};
        normal_factor = 1;
    }
};
Sharpen::Sharpen(Bmp bmpfile,string view)
        :KernelFilter(bmpfile,view)
{
}
class Emboss:public KernelFilter{
public:
    Emboss(Bmp bmpfile,string view);
    void set_filter_kernel(){
        kernel_matrix = {{-2,-1,0},{-1,1,1},{0,1,2}};
        normal_factor = 1;
    }
};
Emboss::Emboss(Bmp bmpfile,string view)
        :KernelFilter(bmpfile,view)
{
}
#endif

#include "KernelFilter.hpp"
int apply_kernel_to_cell(vector<vector<int>>& image, vector<vector<int>>& kernel, int row, int col) {
    int sum = 0;
    int kernelSize = kernel.size();
    int halfKernelSize = kernelSize / 2;

    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            int r = row + i - halfKernelSize;
            int c = col + j - halfKernelSize;

            if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size()) {
                sum += kernel[i][j] * image[row][col];
            } else {
                sum += kernel[i][j] * image[r][c];
            }
        }
    }

    return sum;
}

vector<vector<int>> apply_kernel_to_matrix(vector<vector<int>>& image, vector<vector<int>>& kernels,int normal_factor) {
    int numRows = image.size();
    int numCols = image[0].size();

    vector<vector<int>> result(numRows, vector<int>(numCols, 0));

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int newValue = apply_kernel_to_cell(image, kernels, i, j);
            result[i][j] += min(max(0,(int)(newValue/normal_factor)),255);
        }
    }

    return result;
}
KernelFilter::KernelFilter(Bmp bmpfile,string view)
            :Filter(bmpfile,view)
{

    create(result_filter,input_bmp.infoHdr.width,input_bmp.infoHdr.height);
    for(int i=0;i<input_bmp.infoHdr.width;i++){
        for(int j=0;j<input_bmp.infoHdr.height;j++){
            result_filter.data[j][i] = input_bmp.data[j][i];
        }
    }
}



void KernelFilter::apply_filter(){
    set_filter_kernel();
    vector<vector<int>> red_val,grn_val,blu_val,result_red_val,result_grn_val,result_blu_val;
    for(int i=0;i<input_bmp.infoHdr.height;i++){
        vector<int> red_val_row,grn_val_row,blu_val_row;
        for(int j=0;j<input_bmp.infoHdr.width;j++){
            red_val_row.push_back( input_bmp.data[i][j].red);
            grn_val_row.push_back( input_bmp.data[i][j].grn);
            blu_val_row.push_back( input_bmp.data[i][j].blu);
        }
        red_val.push_back(red_val_row);
        grn_val.push_back(grn_val_row);
        blu_val.push_back(blu_val_row);
    }
    result_red_val = apply_kernel_to_matrix(red_val,kernel_matrix,normal_factor);
    result_grn_val = apply_kernel_to_matrix(grn_val,kernel_matrix,normal_factor);
    result_blu_val = apply_kernel_to_matrix(blu_val,kernel_matrix,normal_factor);
    for(int i=y_view;i<y_view+h_view;i++){
        for(int j=x_view;j<x_view+w_view;j++){
            result_filter.data[i][j].red = result_red_val[i][j];
            result_filter.data[i][j].grn = result_grn_val[i][j];
            result_filter.data[i][j].blu = result_blu_val[i][j];
        }
    }
}

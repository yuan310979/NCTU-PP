#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <CL/cl.h>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    /**
     *  OpenCL Initialization
     */
    cl_uint num_platform, num_device;
    cl_platform_id pid;
    cl_device_id did;
    cl_int err_platform, err_device, err_context, err_cmdq;
    err_platform = clGetPlatformIDs(1, &pid, &num_platform);
    err_device = clGetDeviceIDs(pid, CL_DEVICE_TYPE_GPU, 1, &did, &num_device);
    cl_context ctx = clCreateContext(NULL, 1, &did, 0, 0, &err_context);
    cl_command_queue cmd_queue = clCreateCommandQueueWithProperties(ctx, did, 0, &err_cmdq);

#ifdef DEBUG
    if(err_platform == CL_SUCCESS &&
       err_device == CL_SUCCESS &&
       err_context == CL_SUCCESS &&
       err_cmdq == CL_SUCCESS){
        std::cout << "Initialize without error!" << std::endl;
    }
    else{
        std::cerr << "[Error] Initialize fail!" << std::endl;
        return 0;
    }
#endif

    unsigned int * histogram_results;
    unsigned int i=0, a, input_size;
    std::fstream inFile("input", std::ios_base::in);
    std::ofstream outFile("0756031.out", std::ios_base::out);

    inFile >> input_size;
    unsigned int *image = new unsigned int[input_size];
    while( inFile >> a ) {
        image[i++] = a;
    }

    cl_int err_buf;
    cl_mem cl_args_result = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, 768 * sizeof(unsigned int), 0, &err_buf);
    if(err_buf != CL_SUCCESS) std::cerr << "[Error] clCreateBuffer" << std::endl;
    cl_mem cl_args_image = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, input_size * sizeof(unsigned int), image, &err_buf);
    if(err_buf != CL_SUCCESS) std::cerr << "[Error] clCreateBuffer" << std::endl;
    cl_mem cl_args_size = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(unsigned int), &input_size, &err_buf);
    if(err_buf != CL_SUCCESS) std::cerr << "[Error] clCreateBuffer" << std::endl;

    // Load cl program from file to string
    std::fstream histogram_cl("./histogram.cl", std::ios_base::in);
    std::stringstream ss;
    std::string histogram_str;
    ss << histogram_cl.rdbuf();
    histogram_str = ss.str();
    const char* histogram_cstr = histogram_str.c_str();
    size_t histogram_len = histogram_str.size();

    // program setting
    cl_int err_program, err_build, err_kernel, err_args;
    cl_program program = clCreateProgramWithSource(ctx, 1, &histogram_cstr, &histogram_len, &err_program);
    if(err_program != CL_SUCCESS) std::cerr << "[Error] clCreateProgramWithSource" << std::endl;
    err_build = clBuildProgram(program, 1, &did, "-Werror", 0, 0);
    if(err_build != CL_SUCCESS){
        std::cerr << "[Error] clBuildProgram" << std::endl;   
        size_t len = 0;
        cl_int ret = CL_SUCCESS;
        ret = clGetProgramBuildInfo(program, did, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
        char *buffer = new char[len];
        ret = clGetProgramBuildInfo(program, did, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
        std::cerr << buffer << std::endl;
    }

    // kernel setting
    cl_kernel kernel = clCreateKernel(program, "histogram", &err_kernel);
    if(err_kernel != CL_SUCCESS) std::cerr << "[Error] clCreateKernel" << std::endl;
    err_args = clSetKernelArg(kernel, 0, sizeof(cl_args_result), &cl_args_result);
    if(err_args != CL_SUCCESS) std::cerr << "[Error] clSetKernelArg" << std::endl;
    err_args = clSetKernelArg(kernel, 1, sizeof(cl_args_image), &cl_args_image);
    if(err_args != CL_SUCCESS) std::cerr << "[Error] clSetKernelArg" << std::endl;
    err_args = clSetKernelArg(kernel, 2, sizeof(cl_args_size), &cl_args_size);
    if(err_args != CL_SUCCESS) std::cerr << "[Error] clSetKernelArg" << std::endl;

    // Enqueue kernel to device command queue
    cl_int err_enqueue;
    size_t global_work_size = 100;
    err_enqueue = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, 0, &global_work_size, 0, 0, 0, 0);
    if(err_enqueue != CL_SUCCESS) std::cerr << "[Error] clEnqueueNDRangeKernel" << std::endl;

    // Read result from device
    cl_int err_readbuffer;
    histogram_results = (unsigned int*) malloc(sizeof(unsigned int) * 768);
    err_readbuffer = clEnqueueReadBuffer(cmd_queue, cl_args_result, CL_TRUE, 0, 768 * sizeof(unsigned int), histogram_results, 0, 0, 0);
    if(err_readbuffer != CL_SUCCESS) std::cerr << "[Error] clEnqueueReadBuffer" << std::endl;

    // Free Memory
    cl_int err;
    err = clReleaseProgram(program);
    if(err != CL_SUCCESS) std::cerr << "[Error] Release memory" << std::endl;
    err = clReleaseKernel(kernel);
    if(err != CL_SUCCESS) std::cerr << "[Error] Release memory" << std::endl;
    err = clReleaseMemObject(cl_args_result);
    if(err != CL_SUCCESS) std::cerr << "[Error] Release memory" << std::endl;
    err = clReleaseMemObject(cl_args_image);
    if(err != CL_SUCCESS) std::cerr << "[Error] Release memory" << std::endl;
    err = clReleaseMemObject(cl_args_size);
    if(err != CL_SUCCESS) std::cerr << "[Error] Release memory" << std::endl;

    for(unsigned int i = 0; i < 256 * 3; ++i) {
        if (i % 256 == 0 && i != 0)
            outFile << std::endl;
        outFile << histogram_results[i]<< ' ';
    }

	inFile.close();
	outFile.close();

	return 0;
}

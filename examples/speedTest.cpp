
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <oclm/oclm.hpp>
#include <oclm/util/high_resolution_timer.hpp>
#include <oclm/kernelUtil/readCL.hpp>

void runFunction(const int& numThreads, const oclm::program& p, const std::string& function)
{
        // Select a kernel
        oclm::kernel k(p, function);

        // build a function object out of the kernel
        oclm::function f = k[oclm::global(numThreads), oclm::local(1)];

        std::vector<int> A(numThreads, 1);
        std::vector<int> B(numThreads, 2);
        std::vector<int> C(numThreads, 0);
        
        // create a command queue with a device type and a platform ... context and
        // platform etc is selected in the background ... this will be managed as
        // global state
        oclm::command_queue queue(oclm::device::default_);


        // asynchronously fire the opencl function on the command queue, the
        // std::vector's will get copied back and forth transparantly, policy classes
        // to come ...
        oclm::event e1 = async(queue, f(A, B, C));

        // wait until everything is completed ...
        e1.get();
}

int main()
{
    

    oclm::get_platform();
    //Open oclm/kernelUtil/kernels/speedTest.cl
    const std::string src = readCLFile("/kernels/speedTest.cl");

    // create a program from source ... possibly a vector of sources ...
    oclm::program p(src);
    
    std::ofstream fout;
    fout.open("log.txt");


    for (int i = 0; i < 24; i++)
    {
        int numThreads = (int)std::pow((double)2, (double)i);

        //assignLocal

        std::string function = "assignLocal";
        oclm::util::high_resolution_timer t;
        runFunction(numThreads, p, function);
        // get the time elapsed before outputting to avoid including the output operation in the performance time
        double elapsed = t.elapsed();
        std::cout << "\n--------\nBasic local memory integer assignment operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";
        fout << "\n--------\nBasic local memory integer assignment operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";
        //assignGlobal

        function = "assignGlobal";
        t.restart();
        runFunction(numThreads, p, function);
        // get the time elapsed before outputting to avoid including the output operation in the performance time
        elapsed = t.elapsed();
        std::cout << "\n--------\nBasic global memory integer assignment operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";
        
        fout << "\n--------\nBasic global memory integer assignment operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";

        //vecAdd

        function = "vecAdd";
        t.restart();
        runFunction(numThreads, p, function);
        // get the time elapsed before outputting to avoid including the output operation in the performance time
        elapsed = t.elapsed();
        std::cout << "\n--------\nBasic global memory vector addition operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";

        fout << "\n--------\nBasic global memory vector addition operation with: 2^" << i << " or "
            << numThreads << " threads completed in:\n" << elapsed << "s.\n--------\n";

    }
    fout.close();
    std::cout << "Performance information output to log.txt\n";
    //check if we're using Windows
    #if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
        //if so, pause because the console usually closes at the end of execution
        system("Pause");
    #endif
}

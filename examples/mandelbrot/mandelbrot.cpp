// Local Dependencies
#include "chlorine.hpp"

// Standard Library Headers
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

// Computes the Mandelbrot Set to N Iterations
void solve_mandelbrot(std::vector<float> const & real,
                      std::vector<float> const & imag,
                      int iterations,
                      std::vector<int> & result)
{
    for(unsigned int i = 0; i < real.size(); i++)
    {
        float x = real[i]; // Real Component
        float y = imag[i]; // Imaginary Component
        int   n = 0;       // Tracks Color Information

        // Compute the Mandelbrot Set
        while ((x * x + y * y <= 2 * 2) && n < iterations)
        {
            float xtemp = x * x - y * y + real[i];
            y = 2 * x * y + imag[i];
            x = xtemp;
            n++;
        }

        // Write Results to Output Arrays
        result[i] = x * x + y * y <= 2 * 2 ? -1 : n;
    }
}

// Draws a Portable Pixel Map (PPM/PBM) of the Given Mandelbrot Set
void ppm_draw(std::string const & filename,
              std::vector<std::vector<int>> const & grid)
{
    // Declare Local Variables
    std::ofstream fd(filename);
    unsigned int iterations = 50;

    // Write the PPM Header
    fd << "P6"
       << " " << grid[0].size()
       << " " << grid.size()
       << " " << 255
       << std::endl;

    // Determine Pixel Color at Index
    for(auto &i : grid)
    for(auto &j : i)
    {
        unsigned char r, g, b;
        if(j == -1) { r = 0; g = 0; b = 0; }
        else
        {
            r = (j * 255 / iterations);
            g = r;
            b = 255;
        }

        // Write Colors to File
        fd << r << g << b;
    }
}

int main()
{
    // Define Mandelbrot Settings
    int iterations = 2000;
    float x_min  = -2;
    float x_max  =  2;
    float y_min  = -1.5f;
    float y_max  =  1.5f;
    float x_step = .002f;
    float y_step = .002f;

    // Create Linear Vector of Coordinates
    std::vector<float> reals;
    std::vector<float> imags;
    for(float y = y_min; y < y_max; y += y_step)
    for(float x = x_min; x < x_max; x += x_step)
    {
        reals.push_back(x);
        imags.push_back(y);
    }

    // Compute Stride to Avoid Floating Point Errors
    unsigned int stride = 0;
    for(float x = x_min; x < x_max; x += x_step)
        stride++;

    // Compute the Mandelbrot Set on the CPU
    std::vector<int> cpu_ans(reals.size());
    clock_t cpu_begin = clock();
    solve_mandelbrot(reals, imags, iterations, cpu_ans);
    clock_t cpu_end = clock();

    // Compute the Mandelbrot Set Using Chlorine
    std::vector<int> cl_ans(reals.size());
    ch::Worker benoit("mandelbrot.cl");
    clock_t cl_begin = clock();
    benoit.call("solve_mandelbrot", reals, imags, iterations, cl_ans);
    clock_t cl_end = clock();

    // Compare the Output Arrays
    unsigned int error_count = 0;
    for(unsigned int i = 0; i < cpu_ans.size(); i++)
        if (cpu_ans[i] != cl_ans[i])
            error_count++;

    // Reshape the Output Array to 2D for Drawing
    std::vector<std::vector<int>> ans_grid;
    for(unsigned int i = 0; i < reals.size() / stride; i++)
        ans_grid.push_back(std::vector<int>(
                           cl_ans.begin() + (i      * stride),
                           cl_ans.begin() + (i + 1) * stride));

    // Write the Mandelbrot Set to File
    ppm_draw("mandelbrot.ppm", ans_grid);

    // Print Statistics
    std::cout << "CPU Time: " << (float) (cpu_end - cpu_begin) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "GPU Time: " << (float) (cl_end - cl_begin)   / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "Error: "    << (float) error_count * 100 / cpu_ans.size() << "%" << std::endl;

    return 0;
}

// Ray Trace main file

// C++ headers
#include <iostream>   // cout
#include <string>     // string

// Ray Trace headers
#include "ray_trace.hpp"
#include "exceptions.hpp"   // ray_trace_exception
#include "ray_tracer.hpp"   // ray_tracer
#include "read_athena.hpp"  // athena_reader
#include "read_input.hpp"   // input_reader

//--------------------------------------------------------------------------------------------------

// Main function
// Inputs:
//   argc: number of command-line arguments
//   argv: array of command-line argument strings
// Outputs:
//   returned value:
//     0: successful execution
//     1: error
int main(int argc, char *argv[])
{
  // Parse command line inputs
  if (argc != 2)
  {
    std::cout << "Error: Must give a single input file.\n";
    return 1;
  }
  const std::string input_file(argv[1]);

  // Read input file
  input_reader inputs(input_file);
  try
  {
    inputs.read();
  } catch (const ray_trace_exception &exception) {
    std::cout << exception.what();
    return 1;
  } catch (...) {
    std::cout << "Error: Could not read input file.\n";
    return 1;
  }

  // Read data file
  athena_reader raw_data(inputs.data_file);
  try
  {
    raw_data.read();
  } catch (const ray_trace_exception &exception) {
    std::cout << exception.what();
    return 1;
  } catch (...) {
    std::cout << "Error: Could not read data file.\n";
    return 1;
  }

  // Process data
  ray_tracer ray_tracing(inputs, raw_data);
  try
  {
    ray_tracing.sample_rays();
    ray_tracing.make_image();
  } catch (const ray_trace_exception &exception) {
    std::cout << exception.what();
    return 1;
  } catch (...) {
    std::cout << "Error: Could not process data.\n";
    return 1;
  }

  // End program
  return 0;
}

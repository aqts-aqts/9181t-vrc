def convert_path_to_cpp(input_file, output_file):
    """
    Converts a path.txt file into a C++ header file containing a hardcoded vector of waypoints.

    Parameters:
        input_file (str): Path to the input text file (e.g., path.txt).
        output_file (str): Path to the output header file (e.g., path_data.h).
    """
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        # Start writing the header file
        outfile.write("#ifndef PATH_DATA_H\n")
        outfile.write("#define PATH_DATA_H\n\n")

        outfile.write("#include \"main.h\"\n")
        outfile.write("#include <vector>\n\n")
        outfile.write("namespace global {")
        outfile.write("    // Automatically generated file containing path waypoints\n")
        outfile.write("    std::vector<std::pair<double, double>> path_data = {\n")

        # Read the waypoints from the input file
        for line in infile:
            x, y = map(float, line.strip().split(","))
            outfile.write(f"        {{{x}, {y}}},\n")

        # End the vector and the header guard
        outfile.write("    };\n")
        outfile.write("}\n\n")
        outfile.write("#endif // PATH_DATA_H\n")

if __name__ == "__main__":
    # Example usage
    input_file = "dev/path.txt"  # Replace with your actual file path
    output_file = "dev/path_data.h"  # Output header file

    convert_path_to_cpp(input_file, output_file)
    print(f"Generated {output_file} from {input_file}")

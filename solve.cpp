#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// DFS to find a path from root to leaf with a product equal to target
bool dfs(const vector<vector<int>>& tree, int level, int index, int current_product, int target, string& path) {
    int current_node = tree[level][index];
    current_product *= current_node;  // Multiply the current product by the current node's value

    // If at leaf, check if product matches the target
    if (level == tree.size() - 1) {
        return current_product == target;
    } else {
        // Try left child and add 'L' to the path
        path.push_back('L');
        if (dfs(tree, level + 1, index, current_product, target, path)) return true;
        path.pop_back(); // Backtrack if left path doesn't work

        // Try right child and add 'R' to the path
        path.push_back('R');
        if (dfs(tree, level + 1, index + 1, current_product, target, path)) return true;
        path.pop_back(); // Backtrack if right path doesn't work
    }

    // False if neither left nor right paths work
    return false;
}

// Function to print tree and highlight the path
void printTree(const vector<vector<int>>& tree, const string& path) {
    int current_index = 0; // Track the path's current position

    for (int level = 0; level < tree.size(); ++level) {
        // Add spaces for indentation to create the pyramid structure
        cout << string((tree.size() - level - 1) * 3, ' ');

        for (int index = 0; index < tree[level].size(); ++index) {
            // Highlight nodes in the path
            if (index == current_index) {
                cout << "*" << tree[level][index] << "*";
            } else {
                cout << " " << tree[level][index] << " ";
            }
            cout << "   "; // Space between nodes
        }
        cout << endl;

        // Update current_index for the next level based on path direction
        if (level < path.size()) {
            if (path[level] == 'R') {
                current_index++;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);  // Open the input file
    if (!infile.is_open()) {
        cerr << "Error: could not open input file." << endl;
        return 1;
    }

    string line;
    int target;
    vector<vector<int>> tree;

    // Read the target value from the first line
    if (getline(infile, line)) {
        stringstream ss(line);
        string target_label;
        ss >> target_label >> target;
    }

    // Read the tree structure line by line
    while (getline(infile, line)) {
        vector<int> row;
        stringstream ss(line);
        string number;

        // Split each line by commas to extract each node
        while (getline(ss, number, ',')) {
            row.push_back(stoi(number));
        }
        tree.push_back(row);
    }

    // Prepare for DFS
    string path;  // Holds the directions (L or R)
    bool found = dfs(tree, 0, 0, 1, target, path);  // Start DFS from the root (level 0, index 0)

    // Generate output file name by replacing "_input" with "_output"
    string input_file = argv[1];
    size_t input_pos = input_file.find("_input.txt");
    string output_file = input_file.substr(0, input_pos) + "_output.txt";
    ofstream outfile(output_file);

    // Output the result
    if (found) {
        // Write the path directions to the output file
        outfile << path << endl;

        // Print the tree with highlighted path
        printTree(tree, path);
    } else {
        cout << "ERROR: No such path exists." << endl;
    }

    return 0;
}

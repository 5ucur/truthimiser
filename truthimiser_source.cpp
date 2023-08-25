/* A typo-maker. Works with stdin (only first line of a file, for now). 
 * It can also take input after launch. Version 1.0.0.
 *
 * Released under the MIT license.
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <time.h>

// A map of neighbourhoods of keys on a US layout keyboard
// Not the best but it gets the job done
// The '\6' are stand-ins for Tab, later replaced with "    " (four spaces)
// The '\7' are stand-ins for Caps Lock
std::unordered_map<char, std::vector<char>> neighbourhoods = {
    {'`', {'1', '\6'}},
    {'1', {'`', '\6', 'q', '2'}},
    {'2', {'1', 'q', 'w', '3'}},
    {'3', {'2', 'w', 'e', '4'}},
    {'4', {'3', 'e', 'r', '5'}},
    {'5', {'4', 'r', 't', '6'}},
    {'6', {'5', 't', 'y', '7'}},
    {'7', {'6', 'y', 'u', '8'}},
    {'8', {'7', 'u', 'i', '9'}},
    {'9', {'8', 'i', 'o', '0'}},
    {'0', {'9', 'o', 'p', '-'}},
    {'-', {'0', 'p', '[', '='}},
    {'=', {'-', '[', ']', '\b'}},

    {'q', {'1', '2', 'w', 's', 'a', '\7', '\6'}},
    {'w', {'2', '3', 'e', 's'}},
    {'e', {'3', '4', 'r', 'd', 's', 'w'}},
    {'r', {'4', '5', 't', 'f', 'd', 'e'}},
    {'t', {'5', '6', 'y', 'g', 'f', 'r'}},
    {'y', {'t', '6', '7', 'u', 'h', 'g'}},
    {'u', {'7', '8', 'i', 'j', 'h', 'y'}},
    {'i', {'8', '9', 'o', 'k', 'j', 'u'}},
    {'o', {'9', '0', 'p', 'l', 'k', 'i'}},
    {'p', {'0', '-', '[', ';', 'l', 'o'}},
    {'[', {'-', '=', ']', '\'', ';', 'p'}},
    {']', {'+', '\b', '\\', '\n', '\'', '['}},
    {'\\', {'\b', '\n', ']'}},

    {'a', {'q', 'w', 's', 'z', '\7'}},
    {'s', {'w', 'e', 'd', 'x', 'z', 'a'}},
    {'d', {'e', 'r', 'f', 'c', 'x', 's'}},
    {'f', {'r', 't', 'g', 'v', 'c', 'd'}},
    {'g', {'t', 'y', 'h', 'b', 'v', 'f'}},
    {'h', {'y', 'u', 'j', 'n', 'b', 'g'}},
    {'j', {'u', 'i', 'k', 'm', 'n', 'h'}},
    {'k', {'i', 'o', 'l', ',', 'm', 'j'}},
    {'l', {'o', 'p', ';', '.', ',', 'k'}},
    {';', {'p', '[', '\'', '/', '.', 'l'}},
    {'\'', {'[', ']', '\n', '/', ';'}},

    {'z', {'a', 's', 'x'}},
    {'x', {'z', 's', 'd', 'c'}},
    {'c', {'x', 'd', 'f', 'v', ' '}},
    {'v', {'c', 'f', 'g', 'b', ' '}},
    {'n', {'b', 'h', 'j', 'm', ' '}},
    {'m', {'n', 'j', 'k', ',', ' '}},
    {',', {'m', 'k', 'l', '.', ' '}},
    {'.', {',', 'l', ';', '/', ' '}},
    {'/', {'.', ';', '\''}},

    {'~', {'!', '\6'}},
    {'!', {'~', '@', 'Q', '\6'}},
    {'@', {'!', '#', 'Q', 'W'}},
    {'#', {'@', '$', 'W', 'E'}},
    {'$', {'#', '%', 'E', 'R'}},
    {'%', {'$', '^', 'R', 'T'}},
    {'^', {'%', 'T', 'Y', '&'}},
    {'&', {'^', 'Y', 'U', '*'}},
    {'*', {'&', 'U', 'I', '('}},
    {'(', {'*', 'I', 'O', ')'}},
    {')', {'(', 'O', 'P', '_'}},
    {'_', {')', 'P', '[', '+'}},
    {'+', {'_', '[', ']', '\b'}},

    {'Q', {'\6', '!', '@', 'W', 'A', '\7'}},
    {'W', {'@', '#', 'E', 'Q', 'S', 'A'}},
    {'E', {'#', '$', 'W', 'R', 'S', 'D'}},
    {'R', {'$', '%', 'T', 'F', 'D', 'E'}},
    {'T', {'%', '^', 'Y', 'G', 'F', 'R'}},
    {'Y', {'^', '&', 'U', 'H', 'G', 'T'}},
    {'U', {'Y', '&', '*', 'I', 'J', 'H'}},
    {'I', {'*', '(', 'O', 'K', 'J', 'U'}},
    {'O', {'(', ')', 'P', 'L', 'K', 'I'}},
    {'P', {')', '_', '{', ':', 'L', 'O'}},
    {'{', {'P', '_', '+', '}', '"', ':'}},
    {'}', {'+', '\b', '\n', '"', '|', '{'}},
    {'|', {'}', '\b', '\n'}},

    {'A', {'Q', 'W', 'S', 'Z', '\7'}},
    {'S', {'A', 'W', 'E', 'D', 'X', 'Z'}},
    {'D', {'E', 'R', 'F', 'C', 'X', 'S'}},
    {'F', {'R', 'T', 'G', 'V', 'C', 'D'}},
    {'G', {'T', 'Y', 'H', 'B', 'V', 'F'}},
    {'H', {'Y', 'U', 'J', 'N', 'B', 'G'}},
    {'J', {'U', 'I', 'K', 'M', 'N', 'H'}},
    {'K', {'I', 'O', 'L', '<', 'M', 'J'}},
    {'L', {'K', 'O', 'P', ':', '>', '<'}},
    {':', {'L', 'P', '{', '"', '?', '>'}},
    {'"', {'{', '}', '\n', '?', ':'}},

    {'Z', {'A', 'S', 'X'}},
    {'X', {'Z', 'S', 'D', 'C'}},
    {'C', {'X', 'D', 'F', 'V', ' '}},
    {'V', {'C', 'F', 'G', 'B', ' '}},
    {'B', {'V', 'G', 'H', 'N', ' '}},
    {'N', {'B', 'H', 'J', 'M', ' '}},
    {'M', {'N', 'J', 'K', '<', ' '}},
    {'<', {'M', 'K', 'L', '>', ' '}},
    {'>', {'<', 'L', ':', '?', ' '}},
    {'?', {'>', ':', '"'}},
    {' ', {'c', 'v', 'b', 'n', 'm', ',', '.'}},
    {'\n', {']', '}', '\\', '|', '\'', '"'}}
};

// Typo-maker
// This function first checks for the character in the keys above
// Then it picks a random one from its neighbourhood
std::string truthimise(char key) {
    // Search for character
    if (neighbourhoods.find(key) != neighbourhoods.end()) {
        // Get its neighbourhood
        std::vector<char> values = neighbourhoods[key];
        // Get a random index of one of them
        int randomIndex = std::rand() % values.size();
        // Return the character
        return std::string(1, values[randomIndex]);
    }
    // Not found? Return nothing
    return "\0";
}

int main(int argc, char** argv) {
    // The MIT License; input !license in the program to view
    std::string license = "Copyright 2023 5ucur \n\nPermission is hereby granted, free of charge, to any person \nobtaining a copy of this software and associated documentation \nfiles (the “Software”), to deal in the Software without restriction, \nincluding without limitation the rights to use, copy, modify, merge, \npublish, distribute, sublicense, and/or sell copies of the Software, \nand to permit persons to whom the Software is furnished to do so, \nsubject to the following conditions: \n\nThe above copyright notice and this permission notice shall be included \nin all copies or substantial portions of the Software. \n\nTHE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS \nOR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING \nFROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS \nIN THE SOFTWARE.";
    // Location of the source code; input !source in the program to view
    std::string source = "https://github.com/5ucur/truthimiser";
    // Init the random seed with time 
    std::srand(time(0));
    // Output some text, disclaimer, description, so on.
    std::cout << "This is a truthimiser, which makes your input into a truthism (iykyk)!" << std::endl;
    std::cout << "Please note, it's not perfect. Made by Five. Version 1.0.0." << std::endl;
    std::cout << " Program released under the MIT license. Input !license to view,\n or !source for source code URL."  << std::endl;

    // Make input text string 
    std::string in_text;
    // Check for stdin, if missing
    if (!argv[1]) {
        // Get input
        std::cout << "\ntext pls: ";
        std::getline(std::cin, in_text);
    // Otherwise
    } else {
        // Use stdin
        // For now only the first line of a file
        in_text = argv[1];
    }

    // If the user wants to see the license
    if (in_text == "!license") {
        // Show it
        std::cout << license << std::endl;
    // If the user wants to see where the source is
    } else if (in_text == "!source") {
        // Show it
        std::cout << source << std::endl;
    // Else, proceed with the program
    } else {
        // Typo string for result
        std::string truthism;
        // Caps Lock flag
        bool caps = false;

        // Go through the input text 
        for (char character : in_text) {
            // At a random chance (1 in 60)
            if (std::rand() % 60 == 0) {
                // (and a smaller chance, total 1 in 8400)
                if (std::rand() % 140 == 0) {
                    // Skip the key fully
                    character = '\0';
                // Back on that 1 in 60 chance
                } else {
                    // Typo the key
                    char temp_character = truthimise(character)[0];
                    // If the key was found on the keyboard and typoed
                    if (temp_character != '\0') {
                        // Assign it to the character
                        character = temp_character;
                        // At an even smaller chance (total 1 in 12000)
                        if (std::rand() % 200 == 0) {
                            // Typo the key _again_
                            character = truthimise(character)[0];
                            // No need to re-check 'cause the previous key was
                            // definitely on the keyboard
                        }
                    }
                }
            }
            // If Caps Lock pressed
            if (character == '\7') {
                // Case: Caps is off (lowercase)
                if (!caps) {
                    // (let's give a chance to notice and fix right away ;))
                    if (std::rand() % 60 == 0) {
                        // Toggle it on!
                        caps = true;
                    }
                // Case: Caps is on (UPPERCASE)
                } else {
                    // Toggle it off
                    caps = false;
                }
            }
            // If Caps Lock ON
            if (caps) {
                // Type in UPPERCASE
                character = std::toupper(character);
            }
            // If the character is backspace
            if (character == '\b') {
                // Do an actual deletion (back, overwrite with space, back)
                truthism += "\b \b";
            // If the character is a Tab (stand-in)
            } else if (character == '\6') {
                // Insert an actual string of four spaces
                truthism += "    ";
            // In all other cases
            } else {
                // Just pass the character to the string
                truthism += character;
            }
        }
        // Output the string
        std::cout << "\nTruthism: " << truthism << std::endl;
    }
    // Preventing console closing in on itself...
    std::cout << "\nPress Enter to exit..."; 
    std::getline(std::cin, in_text);
    return 0;
}

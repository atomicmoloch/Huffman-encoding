
#include "huffman.hh"
#include "bitio.hh"
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
        if(argc < 2)
        {
                cerr << "No filename given";
                return -1;
        }

        ifstream infile(argv[1]);
        string newname = argv[1];
        ofstream outfile(newname + ".comp", ios::out);

        if (!infile.is_open()) //file open errors
            {
                cerr << "Could not open infile";
                return -1;
            }
        else if (!outfile.is_open())
            {
                cerr << "Could not open outfile";
                return -1;
            }
        else
        {
            Huffman encoder; //encoder huffman tree
            BitOutput output(outfile);

            char letter; //declaration for letter char
            while(infile.get(letter)) //gets next letter
                {
                Huffman::bits_t encoded = encoder.encode(letter); //finds path to letter
                while(!encoded.empty()) //writes letter-path to encoded file
                    {
                    auto b = encoded.front();
                    output.output_bit(b);
                    encoded.erase(encoded.begin());
                    }
                }

            Huffman::bits_t encoded = encoder.encode(Huffman::HEOF); //adds EOF line
            while(!encoded.empty())
                {
                auto b = encoded.front();
                output.output_bit(b);
                encoded.erase(encoded.begin());
                }

        }
            return 0;

}

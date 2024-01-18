
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

        ifstream infile(argv[1], ios::in); //opens new file
        string newname = argv[1]; //I tried to do this one-line but compiler did not like
        ofstream outfile(newname + ".plaintext");

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
            Huffman decoder; //decoder huffman tree
            BitInput input(infile);

            bool letter;
            int decoded = 0; //temp declaration thats near-immediately overwritten
            while(!(decoded == Huffman::HEOF)) //gets next letter
                {
                letter = input.input_bit();
                decoded = decoder.decode(letter);
                                //cout << decoded; //this was cool to see the relative lengths of each character path flash across the screen
                if (!(decoded == -1) and !(decoded == Huffman::HEOF)) //writes to file if not intermediate node or end of file
                {
                    outfile.put(decoded);
                }
                }

            return 0;

        }
}

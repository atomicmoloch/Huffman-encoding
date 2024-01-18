

#include "huffman.hh"

using namespace std;


    Huffman::Huffman()
    {
        for (int x = 0; x < ALPHABET_SIZE - 1; x++)
        {
            values.add_tree(make_shared<HTree>(x, 0)); //Adds to forest "values" a tree with freq 0 for each alphabet letter
        }
        int x = HEOF;
        values.add_tree(make_shared<HTree>(x, 1)); //Adds EOF tree with frequency 1

    }

    HTree::tree_ptr_t Huffman::compile_tree()
    {
        HForest Tempforest = values;
        while(Tempforest.size() > 1)
        {
            auto low1 = Tempforest.pop_top();
            auto low2 = Tempforest.pop_top(); //Takes two lowest trees
            Tempforest.add_tree(make_shared<HTree>(-1, (*low1).get_value() + (*low2).get_value(), low1, low2)); //combines them to new tree with key value -1
        }
        return Tempforest.pop_top(); //returns the only tree remaining in the forest
    }
    Huffman::bits_t Huffman::encode(int symbol)
    {
        bits_t retval;
        code_tree = compile_tree(); //compiles code tree first
        auto code = (*code_tree).path_to(symbol); //gets path to desired symbol on code tree

        while ((*code).size() > 0) //Turns HTree direction list into a series of booleans
        { //could be made efficient by just having Htree return booleans
            if((*code).back() == HTree::Direction::LEFT)
            {
                retval.insert(retval.begin(), true); //Left = true = 1
            }
            else
            {
                retval.insert(retval.begin(), false); //Right = false = 0
            }
            (*code).pop_back();
        }

        code_tree = nullptr; //destroys code tree on the way out
        values.valueplus(symbol); //increments value counter with character just encoded
        return retval; //returns boolean path encoding to desired symbol
    }

    int Huffman::decode(bool bit)
    {
        if(not code_tree) //compiles code tree if it isn't compiled already (is nullptr)
        {
            code_tree = compile_tree();
        }

        if(bit) //Gets either the left or right tree according to bit
        {
            code_tree = code_tree->get_child(HTree::Direction::LEFT); //Left = true = 1
        }
        else
        {
            code_tree = code_tree->get_child(HTree::Direction::RIGHT); //Right = false = 0
        }

        int symbol = code_tree->get_key(); //gets symbol of begotten tree

        if (symbol >= 0) //if symbol is positive, this is a leaf and end of tree
        {
            values.valueplus(symbol); //increments value count for found value
            code_tree = nullptr; //destroys tree
            return symbol;
        }
        else
        {
            return symbol; //should always return -1 here
        }

    }


#include "bitio.hh"

using namespace std;

BitInput::BitInput(std::istream& is)
{
    stream = &is; //initializes stream
}

bool BitInput::input_bit()
{
    if(this->countl == 8) //if this is the ninth input_bit call, loads a new char from the file
    {
        char temp;
        (*stream).get(temp);
        currentl = (unsigned char)temp; //I do not know why chars are signed by default
        countl = 0;
    }
    char bit = currentl % 2; //gets the least signifigant bit of the loaded char
    currentl = currentl / 2;
    countl++;

 //   cout << bit << " | ";
    return (bit == 1);
}


BitOutput::BitOutput(std::ostream& os)
{
    stream = &os; //initializes stream
}

int pow(int times) //didn't want to wastefully import math for one function
{
    if (times == 0)
    {
        return 1;
    }
    return 2 * pow(times - 1);

}

void BitOutput::write() //Writes to file one char at a time
{
    unsigned char out = 0;
    for (int i = 0; i < 8; i++)
    {
        out+=pow(i) * buffer[i];
       // (*stream).put(buffer[i]); //outputs entire buffer one by one to stream
    }
      //    cout << +out << " | ";
    (*stream) << out;

}


void BitOutput::output_bit(bool bit)
{

    buffer[count] = bit; //puts new bit in buffer and increments
    count++;

    if (count == 8) //if buffer full, writes and resets buffer
    {
        write();
        for (int i = 0; i < 8; i++)
        {
            buffer[i] = 0;
        }
        count = 0; //resets count too
    }
}


BitOutput::~BitOutput()
{
    if (!(count == 0))
    {
    write(); //makes sure to write all buffer out before deletion
    }
}

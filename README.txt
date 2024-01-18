Kavi Wilson
2022/04/07
Frachtenberg
CS 221

I did this project alone
As for code design, it is rather prosaic. I used the provided example versions of the relevant HW7 files for the sake of making it a control, though my own code worked fine in the relevent sections.
Encoding: The encoder takes a file and opens the relevant input and output streams and creates a Huffman tree. It one by one reads letters from the input file, passes it to the Huffman encode(character) function to get an encoded path, and then one by one passes the encoded path bits to bitio's output_bit(bool) function, which collects them in an 8-bit buffer, and, when said buffer is full, writes them out to the iostream in the form of one character per 8 bits via the write() function therein. The encoder function adds the EOF character likewise.
Decoding: The decoder takes a file and opens the relevant input and output streams and creates a huffman tree. While the decoded character variable is not equivalent to the EOF number, it calls the input_bit() function which returns the next path-direction bit (The way it is stored, the path-branch codes are not stored in order but in this wise: 8-7-6-5-4-3-2-1-16-15-14-13-12-11-10-8-9-24-23...). The path-direction bit is then passed to the huffman decode(bool) function, which advances along the code tree and returns the current location's value. If the value thus returned is a valid character, it is written to the output file. When the EOF is reached, the loop stops.

Compression tests:

Filename and contents                                  | Initial size| FinalSize | Matches
-------------------------------------------------------------------------------------------
First sentence of "Fantazius Mallare" (Fantazius.txt)  | 70 bytes    | 131 bytes | Yes
A short paragraph I wrote about Harry Kemp (poets.txt) | 1,072 bytes | 734 bytes | Yes
Emerson's 1838 Divinity College address (emerson.txt)  | 41,143 bytes| 22,799 byt| Yes
Shakespeare's play Julius Caeser (shakespeare.txt)     | 117,902 byt | 74,529 byt| Yes
Twain's A Tramp Abroad from Proj. Gutenberg (twain.txt)| 857,812 byt | 487,172 b | Yes

Thank you for textfiles.com for providing the text files!

# compression
Implementation of text file compression algorithm.

Algorithm Implemented
1.Huffmancode

Step Followed.
1. Taking the file using File handling concept and finding the frequency of the each character of the file.
2. Finding the total bits by multiplying the frequency of each charcter by 8(Fixed length Encoading).
3.then applying the huffman algorithm to the character.
4.After that finding the toatl number of the bits after the compression of the file.
5. Finding the compressed bits by. (bit before compression - bit after compression)/bit before compression.

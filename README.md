# Huffman Project

## Overview

- ### The Huffman Project is an implementation of learned data structures applied to create a lossy data compression algorithm. It constructs a Huffman expression tree and compresses characters for a variety of files, including text files and image formats such as BMP.

- ## Features
  - ### Huffman Encoding: Constructs a Huffman tree based on character frequencies to generate optimal binary codes.

  - ### Compression: Reduces file size by replacing characters with binary codes of varying lengths.

  - ### Decompression: Restores original data from the compressed binary representation.

  - ### Support for Multiple File Types: Handles plain text files and image files (e.g., BMP format).

- ## How It Works

    - ### Frequency Analysis: Analyzes the frequency of characters in the input file.

    - ### Tree Construction: Builds a Huffman tree using a priority queue (min-heap), where nodes with the lowest frequencies have the highest priority.

    - ### Code Generation: Generates binary codes for each character based on the tree structure.

    - ### Compression: Replaces characters in the input file with their corresponding binary codes.

    - ### Decompression: Reconstructs the original file using the binary codes and the Huffman tree.

- ## Installation


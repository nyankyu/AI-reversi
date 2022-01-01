# AI-reversi

[![Microsoft C++ Code Analysis](https://github.com/nyankyu/AI-reversi/actions/workflows/msvc-analysis.yml/badge.svg)](https://github.com/nyankyu/AI-reversi/actions/workflows/msvc-analysis.yml)
[![CodeQL](https://github.com/nyankyu/AI-reversi/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/nyankyu/AI-reversi/actions/workflows/codeql-analysis.yml)
[![build and test in win, linux, mac](https://github.com/nyankyu/AI-reversi/actions/workflows/cmake.yml/badge.svg)](https://github.com/nyankyu/AI-reversi/actions/workflows/cmake.yml)

This is Reversi against the AI.

## Build and Run
```bash
$ git clone https://github.com/nyankyu/AI-reversi.git
$ cd AI-reversi
$ cmake .
$ make
$ ./ai-reversi
```

## Play
```
===== AI-reversi =====
   A B C D E F G H
 1 . . . . . . . .
 2 . . . . . . . .
 3 . . . . . . . .
 4 . . . O X . . .
 5 . . . X O . . .
 6 . . . . . . . .
 7 . . . . . . . .
 8 . . . . . . . .

 O: 2, X: 2, .: 60

 X > 
```
`O`: AI, `X`: player

`X >`means that it is`X`'s turn to place a stone. Enter the location where you want to place the stone. The location is represented by a letter and a number.

For example, to place a stone in the `C` column, `4` row, enter `C4`. The result will look like the one below.
```
===== AI-reversi =====
   A B C D E F G H
 1 . . . . . . . . 
 2 . . . . . . . . 
 3 . . O . . . . . 
 4 . . X O X . . . 
 5 . . . X O . . . 
 6 . . . . . . . . 
 7 . . . . . . . . 
 8 . . . . . . . . 

 O: 3, X: 3, .: 58

 X > 
```

If you want to quit the game midway, enter `q`.


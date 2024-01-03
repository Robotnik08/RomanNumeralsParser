# Simple Roman numeral parser made in C

As of this date I am in Rome on holiday, I decided to pass the time a bit and create this simple Roman Numeral parser. <br>

It's actually pretty fun to make, and a nice little challenge. <br>

It currently supports all valid Roman Numerals and even has support for Numerals above 3999 (the four in a row rule is removed for M)

## Usage

When no arguments are given you are prompted to input a value right there in your terminal, it also knows when you inputted an invalid numeral. <br><br>

You can also input the Numeral in the first argument, it will parse it for you. <br>

Example Usage:<br>

```
    .\roman XII
```

You can also put some extra arguments

```
    .\roman IV -s
    .\roman DII -c
```

-s (or --silent) Will only print the output in the stdout, instead of the whole formatted stuff. <br>
-c (or --code) Will not print anything, just return the output as the exit code. <br> <br>

Invalid numbers are displayed as -1 in these modes.
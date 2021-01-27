# CString
## Name
cstring - Program that encodes text files as C string literals.
## Synopsis
`cstring [--single-line] [--hex] [FILE]...`
## Description
**cstring** takes a list of files as command line arguments and translate each of them to an equivalent C string literal. Each of these is then written to the file called *FILE*.str.
If files are passed as arguments stdin will be used and the output will be written to a.str.
## Examples
```bash
$ cat a.txt
Format the file called "a.txt"
$ cstring a.txt
$ cat a.txt.str
"Format the file called \"a.txt\"\n"
""
```
```bash
$ cstring
You can also use stdin!
This will be written to a.str
$ cat a.str
"You can also use stdin!\n"
"This will be written to a.str\n"
""
```
## Options
`--single-line` - The string literal will be compressed to a single line (Does NOT affect the value of the string!).

`--hex` - All characters will be written as their hex value using the \x*XX* escape sequence.

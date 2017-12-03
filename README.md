# bmpMask
This is a small program to mask or unmask a secret message in a .bmp file. I wrote `unmask.c` as an assignment for a course and then wrote `mask.c` to play with my own messages.

## Compile

bash:
```
gcc -o unmask unmask.c
```
```
gcc -o mask mask.c
```
Or use `make`. If you need to install the C compiler click for  [Mac](https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/) or  [Windows](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html) or [Linux](https://www.cyberciti.biz/faq/howto-compile-and-run-c-cplusplus-code-in-linux/).

## Usage

These programs take two arguments: the input file and the output file. The input file must be a 24-bit uncompressed BMP 4.0 file.

```
./unmask rcmessage.bmp result.bmp
```

## Example
### Secret message:
![secret](https://s3.amazonaws.com/fcc-codepen-assets/secret.bmp)

### Secret revealed:
![revealed](https://s3.amazonaws.com/fcc-codepen-assets/secretRevealed.bmp)

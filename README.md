This is test assignment for internship. I used Linux in order to complete this task. To compile just use:
```
$ make
```
There are 2 test input files in folder input_files. You can use them with the usage of make:
```
$ make test1
$ make test2
```
Or you can do that manually:
```
$ gcc -std=c++20 -O2 -Isrc main.cpp src/*.cpp -o main -lstdc++
$ ./main test1.txt
$ ./main test2.txt
```


# PyramidDescent
PyramidDescent Puzzle: AoPS puzzle 



To run the code: 
```
g++ -o solve solve.cpp
```

Then, with your input.txt file, run
```
./solve <input.txt>
```

The output will be `<name>_output.txt`


# Example
The input is `pyramid_sample_input.txt`
```
// pyramid_sample_input.txt
Target: 720
2
4,3
3,2,6
2,9,5,2
10,5,2,15,5
```
Then when you run
```
g++ -o solve solve.cpp
./solve pyramid_sample_input.txt
```
The output will be in `pyramid_sample_output.txt`: which is going to be `LRLL`. 

Additionally, in the terminal, the code will highlight the path that is taken. So, for this input, it will print
```
            *2*   
        *4*      3   
     *3*     2      6   
   2    *9*      5     2   
10    5     *2*     15    5   
```
in the terminal. 

#include <stdio.h>
#include <stdlib.h>

void process(char inName[]) 
{
    
    int     row, col;                                           //variable for rows and columns to use in loops
    int     gradeTotal[32], gradeArray[32][5], roundedAv[32];   //arrays for storing data after every stage of calculation
    float   average[32];                                        //array for average in float to help rounding up/down

    FILE *in, *out;     

    //open the grades file to read the data from
    printf("Input file. Opening.\n");
    in = fopen(inName, "r");

    //input all the data from the file into an array
    for(row=0; row<32; row++) {
        for(col=0; col<5; col++) {
            fscanf(in, "%i", &gradeArray[row][col]);
        }
    }

    //close the imported file
    printf("Input file. Closing.\n");
    fclose(in);                             
    
    //check whether the imported student id numbers and grades are within the valid range
    printf("Checking data.\n");
    for(row=0; row<32; row++) {

        //check if the id numbers are valid and within the range and print a message if not
        if(!(gradeArray[row][0] >= 2022000  &&  gradeArray[row][0] <= 2022099)) {
            printf("Found an invalid student id: %d. Exiting.\n", gradeArray[row][0]);
            exit (1);
        }

        //check if the grade values are within the valid range
        for(col=1; col<5; col++) {
            if((gradeArray[row][col] <= 0  ||  gradeArray[row][col] >= 100)) {
                printf("Found an invalid grade: id %d grade %d. Exiting.\n", gradeArray[row][0], gradeArray[row][col] );
                exit (1);
            }
            
            //check if one of the grades is below 20. then round it up to 20 if so
            if (gradeArray[row][col] < 20) {
                printf("Correcting student %d grade %d\n", gradeArray[row][0], gradeArray[row][col]);
                gradeArray[row][col] = 20;
            }
            //check if one of the grades is ubove 90. then round it down to 90 if so
            if (gradeArray[row][col] > 90) {
                printf("Correcting student %d grade %d\n", gradeArray[row][0], gradeArray[row][col]);
                gradeArray[row][col] = 90;
            }
        }
    }

    // compute averages
    printf("Computing averages.\n");
    for(row=0, col=1; row<32; row++) {

        //submission of four of the grades for each student
        gradeTotal[row] = (gradeArray[row][col] + gradeArray[row][col+1] + gradeArray[row][col+2] + gradeArray[row][col+3]);
        
        //calculating the average for each student
        average[row] = (float) gradeTotal[row] / 4;

        //ounding the average to turn it into integer
        if(((int) average[row] +1) <= (average[row] +0.5))
        {
            //rounding the average up
            roundedAv[row] = (int) average[row] + 1;
        }
        else
        {
            //rounding the average down
            roundedAv[row] = (int) average[row];
        }
    }

    //open a file to write the results
    printf("Output file. Opening.\n");
    out = fopen("averages.txt", "w");         

    //write the results with the student id into the output file
    for(row=0; row<32; row++) {
        fprintf(out, " %i %i \n", gradeArray[row][0], roundedAv[row]);
    }

    //close the output file
    printf("Output file. Closing.\n");
    fclose(out);    
}

//excuting the function process with various ranges
int main (void)
{
    process("grades.txt");

    return 0;
}
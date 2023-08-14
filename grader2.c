#include <stdio.h>
#include <stdlib.h>


void process( int nStudent, int nGrades, char inName[] ) 
{
    int     row, col;                       
    int     gradeTotal[nStudent], gradeArray[nStudent][nGrades +1], roundedAv[nStudent];    //arrays for storing data after every stage of calculation
    float   average[nStudent];                                                              //array for average in float to help rounding up/down

    //check if the inputed data is within the required range
    if (!(nStudent>=1  &&  nStudent<=100)) {
        printf("Requires 1 to 100 students. Exiting.\n");
        exit (1);
    }
    if (!(nGrades>=1  &&  nGrades<=8)) {
        printf("Requires 1 to 8 grades. Exiting.\n");
        exit (1);
    }

    FILE *in, *out;

    //open the grades file to read the data from
    printf("Input file. Opening.\n");
    in = fopen(inName, "r");         

    //for-loop to input all the data from the file into an array
    for(row=0; row<nStudent; row++) {
        for(col=0; col<nGrades +1; col++) {
            fscanf(in, "%i", &gradeArray[row][col]);
        }
    }

    //close the output file
    printf("Input file. Closing.\n");
    fclose(in);

    //processing data
    printf("Checking data.\n");
    for(row=0; row<nStudent; row++) {
        //check if the id numbers are valid and within the range and print a message if not
        if(!(gradeArray[row][0] >= 2022000  &&  gradeArray[row][0] <= 2022099)) {
            printf("Found an invalid student id: %d. Exiting.\n", gradeArray[row][0]);
            exit (1);
        }

        //check whether the grades are within the valid range and ignore if value = -1
        for(col=1; col<nGrades +1; col++) {
            if(!(gradeArray[row][col] == -1) && (gradeArray[row][col] < 0  ||  gradeArray[row][col] > 100)) {
                printf("Found an invalid grade: id %d grade %d. Exiting.\n", gradeArray[row][0], gradeArray[row][col] );
                exit (1);
            }
        }

        //looping over the grades to correct some of the data that are too low or too high
        for(col=1; col<nGrades +1; col++) {
            //check if one of the grades is below 20. then round it up to 20 if so
            if ((gradeArray[row][col] < 20) && (gradeArray[row][col] != -1)) {
                printf("Correcting student %d grade %d\n", gradeArray[row][0],gradeArray[row][col] );
                gradeArray[row][col] = 20;
            }
            //check if one of the grades is ubove 90. then round it down to 90 if so
            if (gradeArray[row][col] > 90) {
                printf("Correcting student %d grade %d\n", gradeArray[row][0],gradeArray[row][col] );
                gradeArray[row][col] = 90;
            }
        }
    }

    printf("Computing averages.\n");
    //looping over the grades of each student to calculate the average
    for(row=0; row<nStudent; row++) {
        
        //looping over each grade and change the grades with value -1 to 0
        for (col=1; col<nGrades +1; col++) {
            if (gradeArray[row][col] == -1) {
                nGrades = nGrades -1;
                gradeArray[row][col] = 0;
            }
        }
        
        //submission of four of the grades for each student
        gradeTotal[row] = (gradeArray[row][1] + gradeArray[row][2] + gradeArray[row][3] + gradeArray[row][4]);
        
        //calculating the average
        average[row] = (float) gradeTotal[row] / nGrades;

        //rounding the average to turn it into integer
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

    //for-loop to write the results with the student id into the output file
    for(row=0; row<nStudent; row++) {
        fprintf(out, " %i %i \n", gradeArray[row][0], roundedAv[row]);
    }

    //closing output file
    printf("Output file. Closing.\n");
    fclose(out);    
}

//excuting the function process with various ranges
int main (void)
{
    process(32, 4, "grades.txt");

    return 0;
}
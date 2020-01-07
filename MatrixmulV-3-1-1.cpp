//test program to parse csv files
//to compile: mpiCC -o <executable file name> <file name>.cpp
//to run mpirun -np <process number> <full path to exe file>

#include <iostream> //input from command line
#include <fstream>  //file library
#include <string>   //library for strings
#include <bits/stdc++.h> //library for string to char
#include <sstream> //library used here for string to int conversion
#include <stdio.h>
#include <mpi.h>
using namespace std;

struct matrix{
	double node[100][100];
	int row = 0;
	int column = 0;
	int index = 0;
	char type;
};


matrix matrix1, matrix2, matrix3;
void dataMatrix1(int len, char parser[],bool firstLine);
void dataMatrix2(int l, char parse[],bool first);
void createTuple(int rowNumb, matrix row, matrix column);
void printMatrix(matrix mx);

int main(int argc, char *argv[]){//pull in number of processes and string file name

	string line, fileName = "in2.txt";//file name is argument 2
	//string processNumb= argv[0];//number of processes is argument 1 
	int lineNumber=0;//lineNumber used to keep track of which line has been pulled.
	int ierr, root_process, id, numb_procs;

	ierr = MPI_Init(NULL,NULL);

	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);
        ierr = MPI_Comm_size(MPI_COMM_WORLD, &numb_procs);

	matrix1.type = 'r'; matrix2.type = 'c', matrix3.type='a';
	
	bool isSwitching = false, firstLine = true;
	ifstream file(fileName);//constructor of fstream pass in file name as string

	if(file.is_open()){
		//pull each line of the file into string line
		while(getline(file,line)){
			int n = line.length();
			char parser[n+1];
			lineNumber++;
			strcpy(parser,line.c_str());//turn string into char[]
			if(n==0){
				isSwitching=true;
			}
			if(!isSwitching){
				//place double data into matrix1
				dataMatrix1(n,parser,firstLine);
				firstLine = false;
				matrix1.row++;	
			}else if(isSwitching && n==0){
				firstLine = true;
			}else{
				//place double data into matrix2
				dataMatrix2(n,parser,firstLine);
				firstLine = false;
				matrix2.row++;
			}
			
		}//end while loop
		//cout<<matrix1.size<<" "<<matrix2.size<<"\n";
		for(int y=0;y<matrix1.row;y++){
			createTuple(y,matrix1,matrix2);
		}
		file.close();	

	}else{
		cout<<"unable to open file\n";
	}
	return 0;
}//end main method


//converts one line at a time into int data in arrays
void dataMatrix1(int len, char parser[],bool firstLine){
	string tempNumb="";
	for(int i=0;i<len+1;i++){
		if(parser[i]!=','){
			tempNumb+= parser[i];
		}
		if(parser[i]==','|| i==len){
			//convert string to double in matrix
			matrix1.node[matrix1.row][matrix1.index]=stod(tempNumb);//pass converted int to row's node
			//cout<< matrix1.node[matrix1.row][matrix1.index]<<" matrix1["<<matrix1.row<<"]["<<matrix1.index<<"]"<<endl;
			matrix1.index++;
			if(firstLine){
				matrix1.column++;//increase for every number in row  of second matrix
			}
			if(i==len){
				matrix1.index=0;
			}
			//reset tempNumb for the next number
			tempNumb = "";
		}
	}//end for loop
}//end method parse

//converts one line at a time into int data in arrays
void dataMatrix2(int l, char parse[],bool first){
	string tempNumb="";
	for(int i=0;i<l+1;i++){
		if(parse[i]!=','){
			tempNumb+= parse[i];
		}
		if(parse[i]==','|| i==l){
			//convert string to double in matrix
			matrix2.node[matrix2.row][matrix2.index]=stod(tempNumb);//pass converted int to row's node
		//	cout<<matrix2.node[matrix2.row][matrix2.index]<<endl;
			matrix2.index++;
			if(first){
				matrix2.column++;//increase for every number in row  of second matrix
			}
			if(i==l){
				matrix2.index=0;
			}
			//reset tempNumb for the next number
			tempNumb = "";
		}
	}//end for loop
}//end method parse


//converts one row into the correct string data
void createTuple(int rowNumb, matrix one, matrix two){	
	//int sum=0;
	//cycle through each
	for(int i=0;i<two.column;i++){
		for(int j=0;j<two.row;j++){
			matrix3.node[rowNumb][i] += one.node[rowNumb][j]*two.node[j][i];
		}
		//matrix3.node[rowNumb][i] = sum;
		//sum = 0;
		cout << matrix3.node[rowNumb][i];
		if(i<two.column-1){
			cout<<",";
		}
	}
	cout << endl;
}//end method createTuple

void printMatrix(matrix mx){
	for(int i=0;i<mx.row;i++){
		for(int j=0;j<mx.column;j++){
			cout<<mx.node[i][j]<<" ";
		}
		cout<<endl;
	}
}


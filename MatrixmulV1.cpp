//test program to parse csv files

#include <iostream> //input from command line
#include <fstream>  //file library
#include <string>   //library for strings
#include <bits/stdc++.h> //library for string to char
#include <sstream> //library used here for string to int conversion
//#include <mpi.h>
using namespace std;

struct matrix{
	int node[100];
	int index = 0;
	int size = 0;
	char type;
};


matrix matrix1, matrix2, matrix3;
void parse(int len, matrix obj, char parser[],int lineNumber);
void createTuple(int rowNumb, matrix row, matrix column);

int main(int argc, char *argv[]){//pull in number of processes and string file name

	string line, fileName = argv[2];//file name is argument 2
	string processNumb= argv[0];//number of processes is argument 1
	int counter = 1, lineNumber=0;//lineNumber used to keep track of which line has been pulled.

	matrix1.type = 'r'; matrix2.type = 'c', matrix3.type='a';
	
	bool isSwitching = false;
	ifstream file(fileName);//constructor of fstream pass in file name as string

	if(file.is_open()){
		//pull each line of the file into string line
		while(getline(file,line)){
			int n = line.length();
			char parser[n+1];
			lineNumber++;
			strcpy(parser,line.c_str());//turn string into char[]
			if(n==0){isSwitching=true;}

			if(!isSwitching){
				parse(n,matrix1,parser,lineNumber);	
			}else if(isSwitching && n==0){
				//blank line catch
			}else{
				matrix2.size++;//increase for every line in second table
				parse(n,matrix2,parser,lineNumber);
			}
			
		}//end while loop
		for(int y=0;y<matrix2.size;y++){
			createTuple(y+1,matrix1,matrix2);
			cout<<endl;
		}
		//cout << "row: "<< matrix1.size<<" column: "<<matrix2.size<<endl;
		//answer = row n element * all of column n elements
		//cycle through on element of row * size of columns number of elements save in answer at k
		for(int k=0;k<matrix2.size;k++){
			int sum=0;
			for(int m=0;m< matrix1.size;m++){
			sum+=matrix1.node[k]*matrix2.node[m];
			}
			int h = k/matrix1.size;
		
			//cout << answer[h][k]<<endl;
		}
		file.close();
		
		for(int q=0;q<matrix2.size;q++){
			for(int r=0;r<matrix1.size;r++){
				//cout << answer[q][r];
			}
			//cout <<endl; 
		}

	}else{
		cout<<"unable to open file\n";
	}
	return 0;
}//end main method


//converts one line at a time into int data in arrays
void parse(int len, matrix obj, char parser[],int lineNumber){
	string tempNumb="";
	for(int i=0;i<len+1;i++){
		if(parser[i]!=','){
			tempNumb+= parser[i];
		}
		
		if(parser[i]==','|| i==len){
			//convert string to int in row or column
			stringstream converter(tempNumb);//convert string to int
			converter >> obj.node[obj.index];//pass converted int to row's node
			obj.index++;
			if(lineNumber == 1){
				obj.size++;//increase for every number in row  of first table
				//cout << "line number: "<< lineNumber <<" index: "<<i<<" row size: "<< obj.size<<" type: "<< obj.type  <<"\n";
			}
			tempNumb = "";
		}
	}//end for loop
	if(obj.type=='r'){
		matrix1 = obj;
	}else{
		matrix2= obj;
	}
}//end method parse

//converts one row into the correct string data
void createTuple(int rowNumb, matrix row, matrix column){
       int sum;	
	for(int i=(rowNumb-1)*row.size;i<row.size*rowNumb;i++){
		sum = 0;
		for(int j=0;j<column.size;j++){
			sum+= row.node[i]*column.node[j+(j*(row.size-1))];
			//cout << row.node[i] <<" "<<column.node[j+(j*(row.size-1))]<<endl;
		}
		matrix3.node[i] = sum;
		if(i==(rowNumb-1)*row.size){
			cout<< matrix3.node[i];
		}else{
			cout << "," << matrix3.node[i];
		}
	}
}//end method createTuple


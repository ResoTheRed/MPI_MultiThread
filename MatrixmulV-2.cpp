//test program to parse csv files

#include <iostream> //input from command line
#include <fstream>  //file library
#include <string>   //library for strings
#include <bits/stdc++.h> //library for string to char
#include <sstream> //library used here for string to int conversion
//#include <mpi.h>
using namespace std;

struct matrix{
	double node[100][100];
	int index = 0;
	int size = 0;
	char type;
};


matrix matrix1, matrix2, matrix3;
void parse(int len, matrix obj, char parser[],bool firstLine);
void createTuple(int rowNumb, matrix row, matrix column);

int main(int argc, char *argv[]){//pull in number of processes and string file name

	string line, fileName = argv[2];//file name is argument 2
	string processNumb= argv[0];//number of processes is argument 1
	int lineNumber=0;//lineNumber used to keep track of which line has been pulled.

	matrix1.type = 'r'; matrix2.type = 'c', matrix3.type='a';
	
	bool isSwitching = false, firstLine = false;
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
				parse(n,matrix1,parser,firstLine);
				matrix1.size++;	
			}else if(isSwitching && n==0){
				firstLine = true;
			}else{
				//place double data into matrix2
				parse(n,matrix2,parser,firstLine);
				firstLine = false;
			}
			
		}//end while loop
		cout<<matrix1.size<<" "<<matrix2.size<<"\n";
		for(int y=0;y<matrix2.size;y++){
			createTuple(y+1,matrix1,matrix2);
			cout<<endl;
		}
		file.close();	

	}else{
		cout<<"unable to open file\n";
	}
	return 0;
}//end main method


//converts one line at a time into int data in arrays
void parse(int len, matrix obj, char parser[],bool firstLine){
	string tempNumb="";
	for(int i=0;i<len+1;i++){
		if(parser[i]!=','){
			tempNumb+= parser[i];
		}
		if(parser[i]==','|| i==len){
			//convert string to double in matrix
			obj.node[obj.index]=stod(tempNumb);//pass converted int to row's node
			obj.index++;
			if(firstLine){
				obj.size++;//increase for every number in row  of second matrix
			}
			//reset tempNumb for the next number
			tempNumb = "";
		}
	}//end for loop
	//set correct matrix to updated obj
	if(obj.type=='r'){
		matrix1 = obj;
	}else{
		matrix2= obj;
	}
}//end method parse

//converts one row into the correct string data
void createTuple(int rowNumb, matrix row, matrix column){
       double sum;	
	for(int i=(rowNumb-1)*column.size;i<column.size*rowNumb;i++){
		sum = 0;
		for(int j=0;j<row.size;j++){
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


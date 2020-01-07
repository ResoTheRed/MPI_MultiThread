//test program to parse csv files

#include <iostream> //input from command line
#include <fstream>  //file library
#include <string>   //library for strings
#include <bits/stdc++.h> //library for string to char
#include <sstream> //library used here for string to int conversion
//#include <mpi.h>
using namespace std;

struct table{
	int node[100];
	int index = 0;
	int size = 1;
};


int main(int argc, char *argv[]){//pull in number of processes and string file name

	string line, fileName = argv[2];//file name is argument 2
	string processNumb= argv[0];//number of processes is argument 1
	int counter = 1, lineNumber=0;//lineNumber used to keep track of which line has been pulled.
	int answer[100][100];
	table row, column;	

	ifstream file(fileName);//constructor of fstream pass in file name as string

	if(file.is_open()){
		//pull each line of the file into string line
		while(getline(file,line)){
			int n = line.length();
			char parser[n+1];
			lineNumber++;
			string tempNumb;
			strcpy(parser,line.c_str());//turn string into char[]
			bool isSwitching = false;
			if(n==0){isSwitching=true;}
			cout<<line<<endl;
			if(!isSwitching){
				for(int i=0;i<n;i++){
					if(parser[i]==','){
						//convert string to int in row
						stringstream converter(tempNumb);//convert string to int
						converter >> row.node[row.index];//pass converted int to row's node
						row.index++;
						if(lineNumber == 1){
							row.size++;//increase for every number in row  of first table
						}
						tempNumb = "";
					}else{
						tempNumb+= parser[i];	
					}
				}
			}else{
				column.size++;//increase for every line in second table
				for(int j=0;j<n;j++){
					if(parser[j]==','){
						//convert string to int in column at next index
						stringstream converter(tempNumb);
						converter >> column.node[column.index];
						column.index++;
						tempNumb="";
					}else if(parser[j]=='\n'){
						column.size++;
					}else{
						tempNumb+=parser[j];//temp+= int
					}
				}
			}
			
		}//end while loop
		//answer = row n element * all of column n elements
		//cycle through on element of row * size of columns number of elements save in answer at k
		for(int k=0;k<column.size;k++){
			int sum=0;
			for(int m=0;m< row.size;m++){
			sum+=row.node[k]*column.node[m];
			cout<< row.node[k]<<" "<<column.node[m]<< " " << " " <<sum<<endl;
			}
			int h = k/row.size;
			answer[h][k] = sum;
			cout << "row: "<<row.size<<" column: "<<column.size<<"\n";
			cout << answer[h][k]<<endl;
		}
		file.close();
		
		for(int q=0;q<column.size;q++){
			for(int r=0;r<row.size;r++){
				cout << answer[q][r];
			}
			cout <<endl; 
		}

	}else{
		cout<<"unable to open file\n";
	}
	return 0;
}

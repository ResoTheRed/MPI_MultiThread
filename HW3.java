import java.util.Scanner;

public class HW3 {
	
	public static void main(String[] args) {
		//Initialize variables
		int personOne = 0;
		int personTwo = 0;
		int personThree = 0;
		int personFour = 0;
		//initialize a counter
		int counter = 0;
		//for each possible int value for personOne (starting at 1, ending at 100-3) 
		for( personOne = 1; personOne <= (100-3); personOne++) {
		
			//for each possible int value for personTwo (starting at personOne+1, ending at 100-2) 
			for(personTwo = personOne + 1; personTwo <= (100-2); personTwo++){
			
				//for each possible int value for personThree(starting at personTwo+1, ending at 100-1)   
				for(personThree = personTwo + 1; personThree <= (100-1); personThree++){
				
					//for each possible int value for personFour(staring at personThree+1, ending at 100) 
					for(personFour = personThree + 1; personFour <= (100); personFour++){
					//increment the count 
						counter++;
						//output the result;
						//System.out.println( personOne + " " +  personTwo + " " + personThree + " " + personFour);
					}
				}
			}   
				
		}	
		System.out.println(counter);
	}
}


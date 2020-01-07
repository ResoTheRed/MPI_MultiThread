import java.util.Scanner;

public class Conversations{
	public static void main(String[] args){

		Scanner input =new Scanner(System.in);
		int guest =100;
		int groups=4;
		int possibleGroups=0;

		for(int person1=1;person1<=guest-3;person1++){
			for(int person2=person1+1;person2<=guest-2;person2++){
				for(int person3=person2+1;person3<=guest-1;person3++){
					for(int person4=person3+1;person4<=guest;person4++){
						possibleGroups++;

					}
				}
			}
		}
			System.out.println(possibleGroups);
	}

}



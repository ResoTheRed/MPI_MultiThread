import java.util.Random;

public class CSVGen{
	public static Random rand = new Random();
	private static int row = rand.nextInt(50)+50;
	private static int column = rand.nextInt(50)+50;
	private static int shared = rand.nextInt(40)+60;

	private static double[][] matrix1 = new double[row][shared];
	private static double[][] matrix2 = new double[shared][column];
		
	public static void main(String[] args){
	
		loadMatrix(matrix1);
		loadMatrix(matrix2);

	}

	public static void loadMatrix(double[][] mx){
		for(int i=0;i<mx.length;i++){
			for(int j=0;j<mx[i].length;j++){
				mx[i][j] = rand.nextDouble() * (rand.nextInt(10000)-5000);
			}
		}
		print(mx);
	}

	private static void print(double[][] mx){
		for(int i=0;i<mx.length;i++){
			for(int j=0;j<mx[i].length;j++){
				System.out.printf("%.3f",mx[i][j]);
				if(j<mx[i].length-1){
					System.out.print(",");
				}
			}
			System.out.println();
		}
		System.out.println();
	}


}

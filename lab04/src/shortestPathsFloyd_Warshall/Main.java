package shortestPathsFloyd_Warshall;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	public static final int M = 9;
	public static final int graph1[][] = 
						{ { 0, 1, M, M, M }, 
				          { 1, 0, 1, M, M }, 
				          { M, 1, 0, 1, 1 }, 
				          { M, M, 1, 0, M },
				          { M, M, 1, M, 0 } };
	public static final int Nr_threads = 4;
	public static final int N = 5;
	public static void main(String[] args) {
		
		int graph[][] = { { 0, 1, M, M, M }, 
				          { 1, 0, 1, M, M }, 
				          { M, 1, 0, 1, 1 }, 
				          { M, M, 1, 0, M },
				          { M, M, 1, M, 0 } };

		Thread[] t = new Thread[Nr_threads];
		for (int i = 0; i < 4 ;i++){
			t[i] = new Thread(new Task(i));
			t[i].start();

		}
		for(int i = 0 ; i < Nr_threads ; i++) {
			try {
				t[i].join();
			} catch(InterruptedException e) {
				e.printStackTrace();
			}
		}





		// Parallelize me (You might want to keep the original code in order to compare)
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
				}
			}
		}
		//print paraleliz
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph1[i][j] + " ");
			}
			System.out.println();
		}
			System.out.println();
		

		//print secv
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}
	}
}

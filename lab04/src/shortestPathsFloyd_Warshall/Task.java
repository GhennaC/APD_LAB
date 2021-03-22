package shortestPathsFloyd_Warshall;

class Task implements Runnable {
	private int id;
	public Task (int id ){
		this.id = id;
	}

	public void run() {
		int start = id*Main.N/Main.Nr_threads;
		int stop = Math.min((id+1)*Main.N/Main.Nr_threads,Main.N);

		for (int k = start; k < stop; k++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					Main.graph1[i][j] = Math.min(Main.graph1[i][k] + Main.graph1[k][j], Main.graph1[i][j]);
				}
			}
		}
	}
}
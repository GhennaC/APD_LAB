package doubleVectorElements;

class Task implements Runnable{
	private int id ;

	public Task( int thread_id){
		id = thread_id;
	}
	public void run(){
		int start = id*Main.N/Main.Nr_threads;
		int stop = Math.min((id+1)*Main.N/Main.Nr_threads,Main.N);

		for(int i = start ; i < stop; i++)
			Main.v[i] = i * 2;
		
	}
}
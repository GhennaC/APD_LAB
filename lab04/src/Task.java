public class Task implements Runnable {
	private int thread_id;

	public Task (int id) {
		thread_id = id;
	}

	public void run(){
		System.out.println("Buna ziua " + thread_id);
	}
}
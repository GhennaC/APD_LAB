public class Main {
	public static void main(String []args){
		int Nr_threads = 4;
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

	}
}
package doubleVectorElements;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	public static final int N = 100000013;
	public static final int v[] = new int[N];
	public static final int Nr_threads = 4;

	public static void main(String []args) {
		
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

		for (int i = 0; i < N; i++) {
			if(v[i]!= i*2) {
				System.out.println("Wrong answer");
			}
		}
		System.out.println("Correct");
	}

}

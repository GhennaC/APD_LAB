package oneProducerOneConsumer;
/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	int a = -1;

	synchronized void  put(int value) {
		try {
			if(a != -1){
				this.wait();
			} 
			if(a == -1) {
				a = value;
				this.notify();
			}
		} catch(InterruptedException exc){
			System.out.println(exc);
		}
		
	}

	synchronized int get() {
		try {
			if(a == -1){
				this.wait();
			}
			if(a != -1){
				int b = a;
				a = -1;
				this.notify();
				return b;
			}
		} catch (InterruptedException exc) {
			System.out.println(exc);
		}	
		return 0;
	}
	
}

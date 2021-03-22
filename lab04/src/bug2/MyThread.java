package bug2;
/**
 * @author cristian.chilipirea
 * 
 *         Why does this code not block? We took the same lock twice!
 */
//pentru ca avem lock pe acelasi thread si odata ce intra in primul intra si in al doilea ....si respectiv merge..
//practic functioneaza la fel,adica nu are nici o utilitate 2 synchr...
public class MyThread implements Runnable {
	static int i;

	@Override
	public void run() {
		synchronized (this) {
			synchronized (this) {
				i++;
			}
		}
	}
}

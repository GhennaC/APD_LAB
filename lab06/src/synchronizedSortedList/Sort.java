package synchronizedSortedList;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Sort extends Thread {
    private final List<Integer> list;

    public Sort(List<Integer> list) {
        super();
        this.list = list;
    }

    @Override
    public synchronized void run() {
        try{
            Main.sem.acquire();
            Collections.sort(list);
        }catch(InterruptedException ex){
            System.out.println(ex);
        }
        Main.sem.release();


    }
}

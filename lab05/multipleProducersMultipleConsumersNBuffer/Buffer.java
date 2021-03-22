package multipleProducersMultipleConsumersNBuffer;

import java.util.Queue;
import java.util.concurrent.*;

/**
 * @author Gabriel Gutu <gabriel.gutu at upb.ro>
 *
 */
public class Buffer {
    Semaphore sput;
    Semaphore sget;
    Queue queue;
    
    public Buffer(int size) {
        queue = new LimitedQueue(size);
        sput = new Semaphore(size);
        sget = new Semaphore(0);
    }
i
    void put(int value) {
        try{
                sput.acquire();
        }catch(InterruptedException exc){
            System.out.println(exc);
        }
        synchronized(this){
                queue.add(value);    
                sget.release();    
        }
    }

    int get() {
        try{
                sget.acquire();
        } catch(InterruptedException exc){
            System.out.println(exc);
        }
        synchronized(this){
                sput.release();
                return (int)queue.poll();     
        }

    }

}


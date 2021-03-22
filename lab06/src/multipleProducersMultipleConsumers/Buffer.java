package multipleProducersMultipleConsumers;

import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.SynchronousQueue;

public class Buffer {
	int value;

	ArrayBlockingQueue <Integer> coada = new ArrayBlockingQueue(Main.N);

	void put(int value){
		try {
			coada.put(value);
		}catch(InterruptedException ex){
			System.out.println(ex);
		}
	}

	int get(){
		try {
			 return coada.take();
		}catch(InterruptedException ex){
			System.out.println(ex);
		}
		return 0;

	}
}

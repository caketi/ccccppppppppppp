public class MyCircularQueue {
    int[] queue;
    int capacity, front, rear, count;

    public MyCircularQueue(int k) {
        queue = new int[k];
        capacity = k;
        front = 0;
        rear = 0;
        count = 0;
    }

    public boolean enQueue(int value) {
        if (isFull())
            return false;
        queue[rear++] = value;
        rear %= capacity;
        count++;
        return true;
    }

    public boolean deQueue() {
        if (isEmpty())
            return false;
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    public int front() {
        if (isEmpty())
            return -1;
        return queue[front];
    }

    public int Rear() {
        if (isEmpty())
            return -1;
        return queue[(rear - 1 + capacity) % capacity];
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public boolean isFull() {
        return capacity == count;
    }
   
}

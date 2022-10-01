import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileReader;
import java.io.Reader;

class Task implements Runnable   
{
    private String buff;
    private long actual;

    static final int MIN_SIZE = 15;
    static final int MAX_SIZE = 30;

    public Task(String b, long a)
    {
        buff = b;
        actual = a;
    }

    public void run()
    {   
        /** odd palindrome **/
        int middle = MAX_SIZE/2;
        for (int i = 1; i < MAX_SIZE/2; i++)
        {
            /** not found. */
            if (buff.charAt(middle + i) != buff.charAt(middle - i)) {
                break;
            }
            /** print it! */
            if ((i*2 + 1) > MIN_SIZE) {
                String part = buff.substring(middle-i, middle+i+1);
                System.out.printf("pos: %d, size %d: found: %s\n", actual - i, (i*2)+1, part);
            }
        }
        /** pair palindrome */
        for (int i = 0; i < middle - 1; i++)
        {
            /** not found. */
            if (buff.charAt(middle - i - 1) != buff.charAt(middle + i)){
                break;
            }
            /** print it! */
            if ((i*2) > MIN_SIZE) {
                String part = buff.substring(middle-i, middle+i);
                System.out.printf("pos: %d, size %d: found: %s\n", actual - i, i*2, part);
            }
        }
    }
}

class TierThree
{
    /** Maximum number of threads in thread pool. */
    static final int MAX_THREADS = 8;

    /** Maximum size of pending batch. */
    static final int MAX_QUEUE = 8;

    /** Maximum palindrome. */
    static final int MAX_P = 30;

    /** Maximum buffer size */
    static final int MAX_B = MAX_P;

    /** Queue of tasks to be performed. */
    static ThreadPoolExecutor pool;

    private static void init()
    {
        pool = (ThreadPoolExecutor) Executors.newFixedThreadPool(MAX_THREADS);
    }

    private static void exec(char[] txt, int pos)
    {
        /** to be thread safe char[] -> String */
        pool.execute(new Task(new String(txt), pos));
    }

    private static void end()
    {
        pool.shutdown();
    }

    public static void main(String[] args)
    {
        init();
        int c, pos = 0; 
        BufferedReader buff;
        char[] txt = new char[MAX_B];

        try {
            /** open file */
            Reader reader = new FileReader("../data/sausage0.txt");
            buff = new BufferedReader(reader, MAX_B);
        }
        catch (FileNotFoundException ex) {
            /* exit error **/
            System.err.println("file not found.");
            System.exit(15);
            return;
        }

        /** main loop */
        while(true)
        {
            /** any comments that explain the queue */
            if(pool.getQueue().size() >= MAX_QUEUE) {
                continue;
            }

            try {
                /** load first buffer */
                if (pos < MAX_B) {
                    c = buff.read(txt, 0, MAX_B);
                    pos = MAX_B;
                /** stacking buffer */
                } else {
                    c = buff.read();
                    System.arraycopy(txt, 1, txt, 0, MAX_B - 1);
                    txt[MAX_B - 1] = (char) c;
                    pos += 1;
                }
            }
            catch (IOException ex){
                /** any problem? */
                System.err.println(ex.toString());
                System.exit(15);
                return;
            }

            /** end of file */
            if (c == -1){
                break;
            }

            /** add to queue */
            exec(txt, pos);
        }
        
        end();
    }
}
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
    private char[] buff;
    private int offset;

    public Task(char[] b, int o)
    {
        buff = b;
        offset = o;
    }

    public void run()
    {
        String txt = new String(buff);
        System.out.printf("%d->%s\n", offset, txt);
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

    /** Minimum palindrome. */
    static final int MIN_P = 3;

    /** Maximum buffer size */
    static final int MAX_B = (MAX_P*2) - 1;

    /** Queue of tasks to be performed. */
    static ThreadPoolExecutor pool;

    private static void init()
    {
        pool = (ThreadPoolExecutor) Executors.newFixedThreadPool(MAX_THREADS);
    }

    private static void exec(char[] txt, int pos)
    {
        pool.execute(new Task(txt, pos));
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
            Reader reader = new FileReader("../data/sausage.txt");
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
                /** loads buffer */
                c = buff.read();
                System.arraycopy(txt, 1, txt, 0, MAX_B - 1);
                txt[MAX_B - 1] = (char) c;
                pos += 1;
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
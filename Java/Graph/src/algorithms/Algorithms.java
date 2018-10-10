package algorithms;

public class Algorithms {
	public static long factorial(long value) {
		if (value <= 1) return 1;
		else return value * Algorithms.factorial(value - 1); 
	}
	static long n = 1, n_1 = 1;
	public static long fibonacci(long value) {
		if (value < 0) 
			return 0;
		else {
			for (long i = 2; i <= value; ++i) {
				Algorithms.n += Algorithms.n_1;
				Algorithms.n_1 = Algorithms.n - Algorithms.n_1;
			}
			long out = Algorithms.n;
			Algorithms.n = Algorithms.n_1 = 1;
			return out;
		}
	}
}
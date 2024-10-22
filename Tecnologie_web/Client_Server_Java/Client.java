import java.io.*;
import java.net.*;

public class Client {
	
    public static void main(String[] args) throws IOException {
		// In filename salvo il parametro dalla riga di comando 
		String filename = args[0];
		
		// Apro la socket su localhost alla porta 9090
        Socket socket = new Socket("127.0.0.1", 9090);

		// Sullo stream della socket invio il nome del file
		PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
		output.println(filename);
		
		// Resto in attesa di leggere quello che arriva sulla socket
        BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        String message = input.readLine();
        System.out.println(message);

		// Chiudo la socket
        socket.close();
		
		// Termino l'esecuzione
        System.exit(0);
    }
}

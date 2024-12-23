import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.*;

class Client{
    public static void main(String[] args) {
        try{
            Socket s = new Socket(args[0],Integer.parseInt(args[1]));
            BufferedReader netIn=new BufferedReader(new InputStreamReader(s.getInputStream(),"UTF-8"));
            BufferedWriter netOut=new BufferedWriter(new OutputStreamWriter(s.getOutputStream(),"UTF-8"));
            BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in));
            while(true){
                System.out.println("Inserisci username:");
                String username = keyboard.readLine();
                System.out.println("Inserisci password:");
                String password = keyboard.readLine();
                System.out.println("Inserisci categoria macchine:");
                String categoria = keyboard.readLine();
                
                netOut.write(username); netOut.newLine();
                netOut.write(password); netOut.newLine();
                netOut.write(categoria); netOut.newLine();
                netOut.flush();

                String line;
                while(true){
                    line =netIn.readLine();
                    if((line == null)){
                        System.exit(0);
                    }
                    if(line.equals("--- END REQUEST ---")){
                        break;
                    }
                    System.out.println(line);
                }
            }
        } catch (Exception e){
            System.err.println(e.getMessage());
            System.exit(1);
        }
        
    }
}
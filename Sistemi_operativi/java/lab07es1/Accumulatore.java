package lab07es1;

public class Accumulatore {
    double counter=0;

    public Accumulatore(double counter) {
        this.counter = counter;
    }

    public void addValue(double value){
         counter=counter+value;
    }
    
    public double getValue(){
        return counter;
    }
}

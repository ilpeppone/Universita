package lab09es6;

import java.util.HashMap;
import java.util.Map;

public class ThreadLoad {
    
    HashMap <Integer,Double> threadLoad;
    

    public ThreadLoad() {
        threadLoad=new HashMap<>(10);
    }

    public synchronized void setThreadLoad(int threadId,double cpuLoad){
        threadLoad.put(threadId, cpuLoad);
    }

    public synchronized Integer getMaximumThreadId(){
        Map.Entry<Integer,Double> max = null;
        for (Map.Entry<Integer, Double> entry : threadLoad.entrySet()) {
            if (max == null || entry.getValue().compareTo(max.getValue()) > 0) {
                max = entry;
            }
        }
        if (max==null)
            return null;
        return max.getKey();
    }
    public synchronized Double getCpuLoad(Integer threadId) {
        if (threadId == null) {
            return null;
        }
        return threadLoad.get(threadId);
    }
}

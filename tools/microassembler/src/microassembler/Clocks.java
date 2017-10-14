package microassembler;

import java.util.HashMap;
import java.util.List;

/**
 *
 * @author erol
 */
public class Clocks {
    
    private static final HashMap<String, List<String>> dict = new HashMap<>();
    
    public static void initialize(List<Block> blocks) {
        
        Block superBlock = Block.get(blocks, Keywords.CLOCKS);
        List<Block> clocksBlocks = Block.split(superBlock.getBody());
        
        for (Block b : clocksBlocks) {
            dict.put(b.getSymbol(), b.getBody());
        }
    }
    
    // returns true if <signal> is a hardwired clock signal, otherwise false
    public static boolean isCorrectlyTimed(String T_State, String signal) {
        
        boolean isClockSignal = false;
        
        for (List<String> clocks : dict.values()) {
            if (clocks.contains(signal)) {
                isClockSignal = true;
                break;
            }
        }
        
        if (isClockSignal) {
            if (!dict.get(T_State).contains(signal)) {
                System.err.print("CRITICAL: clock signal " + signal);
                System.err.println(" is not timed as expected!");
            }
            return true;
        }
        else
            return false;
    }
}

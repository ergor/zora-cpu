package microassembler;

import java.util.HashMap;
import java.util.List;

/**
 *
 * @author erol
 */
public class ControlLines {
    
    // the byte code when no lines are active
    private static int[] inactive = new int[Microassembler.CHIP_COUNT];
    
    private static final HashMap<String, ControlLine> dict = new HashMap<>();
    
    public static void initialize(List<Block> blocks) {
        
        Block controlLines = Block.get(blocks, Keywords.LINES);
        
        if (controlLines == null) {
            System.err.println("error: no lines declaration found");
            return;
        }
        
        List<String> body = controlLines.getBody();
        
        for (int i = 0; i < body.size(); i++) {
            String lineName = body.get(i);
            ControlLine cl = new ControlLine();
            
            cl.value = 1 << (i % 8);
            cl.chip = i / 8;
            
            if (lineName.startsWith("#")) {
                inactive[cl.chip] |= cl.value;
                cl.activeLow = true;
                lineName = lineName.replace("#", "");
            }
            
            dict.put(lineName, cl);
        }
    }
    
    public static ControlLine get(String lineName) {
        return dict.get(lineName);
    }
    
    public static int getInactiveValue(int chip) {
        return inactive[chip];
    }
}

class ControlLine {
    public int chip;
    public int value;
    public boolean activeLow = false;
}
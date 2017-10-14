package microassembler;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 *
 * @author erol
 */
public class Defines {
    
    private static final HashMap<String, List<String>> dict = new HashMap<>();
    
    public static void initialize(List<Block> blocks) {
    
        Block superBlock = Block.get(blocks, Keywords.DEFINE);
        List<Block> defineBlocks = Block.split(superBlock.getBody());
        
        for (Block b : defineBlocks) {
            dict.put(b.getSymbol(), b.getBody());
        }
    }
    
    public static List<String> resolveDef(String symbol) {
        return dict.get(symbol);
    }
    
    public static void apply(Block T_state) {
        
        List<String> body = T_state.getBody();
        List<String> definesPresent = new ArrayList<>();
        
        for (String line : body)
            if (dict.containsKey(line))
                definesPresent.add(line);
        
        body.removeAll(definesPresent);
        
        for (String define : definesPresent)
            body.addAll(resolveDef(define));
    }
}

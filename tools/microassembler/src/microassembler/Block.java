package microassembler;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author erol
 */
public class Block {
    
    private final String WARN_ILLEGAL_SPACE = 
            "warning: illegal space \\u00a0 detected";
    
    private int address = -1;
    private String symbol;
    private List<String> body = new ArrayList<>();
    
    //** GETTERS AND SETTERS **//
    public int getAddress() {
        return address;
    }
    public void setAddress(int address) {
        this.address = address;
    }
        
    
    public String getSymbol() {
        return symbol;
    }
    public void setSymbol(String symbol) {
        if (symbol.contains("\u00a0"))
            System.out.println(WARN_ILLEGAL_SPACE + " at: " + symbol);
        
        this.symbol = symbol.trim();
    }


    public List<String> getBody() {
        return body;
    }
    public void setBody(List<String> body) {
        this.body = body;
    }
    
    //** MISC METHODS **//
    public void addBodyLine(String line) {
        if (line.contains("\u00a0"))
            System.out.println(WARN_ILLEGAL_SPACE + " at: " + line);
                
        this.body.add(line.trim());
    }
    
    public boolean isBodyWildcard() {
        return this.getBody().size() == 1 && this.getBody().get(0).equals("*");
    }
    
    //** STATIC METHODS **//
    public static Block get(List<Block> blocks, String symbol) {
        
        Block block = null;
        
        for (Block b : blocks) {
            if (b.getSymbol().equals(symbol))
                block = b;
        }
        
        return block;
    }
    
    // creates a Body object from String list
    public static List<Block> split(List<String> lines) {
        
        // data vars
        List<Block> blocks = new ArrayList<>();
        Block block = new Block();
        StringBuilder sb = new StringBuilder();
        String trimmed;
        
        // parse state vars
        final int SYMBOL = 0;
        final int BODY = 1;       
        int currentState = 0;
        int depth = 0;
        
        for (String line : lines) {
            
            // skip any whitespace-only line
            trimmed = line.trim();
            if (trimmed.equals("") || trimmed.startsWith("//"))
                continue;
            
            for (char c : trimmed.toCharArray()) {

                switch (currentState) {
                    
                    case SYMBOL:                        
                        if (c == '{') {
                            currentState++;
                            String sym = sb.toString().trim();
                            if (sym.startsWith("0x")) {
                                String hex = sym.split(" ")[0];
                                sym = sym.substring(hex.length() + 1,
                                        sym.length());
                                block.setAddress(Integer.decode(hex));
                            }
                            block.setSymbol(sym);
                            sb.setLength(0);
                        }
                        else 
                            sb.append(c);
                        break;
                        
                    case BODY:
                        if      (c == '{') depth++;
                        else if (c == '}') depth--;
                        
                        if (depth < 0) { 
                            blocks.add(block);
                            block = new Block();
                            depth = 0;
                            currentState = 0;
                            break;
                        }
                        sb.append(c);
                        break;
                }
            }
            
            if (currentState == BODY && sb.length() > 0) {
                block.addBodyLine(sb.toString().trim());
                sb.setLength(0);
            }
        }
        
        if (currentState != 0 || depth != 0)
            System.err.println("possible parse error");
        return blocks;
    }
}

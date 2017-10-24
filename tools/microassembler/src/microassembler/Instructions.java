package microassembler;

import java.util.List;
import java.util.TreeSet;

/**
 *
 * @author erol
 */
public class Instructions {
    
    public static final int T_MAX = 8;
    
    public static void generate(List<Block> blocks, int[][] memory) {
        
        Block instructionBlock = Block.get(blocks, Keywords.INSTRUCTIONS);
        List<Block> instructions = Block.split(instructionBlock.getBody());
        
        Block previous = null;
        int opcode = 0;
        
        for (Block instruction : instructions) {
            
            int adr = instruction.getAddress();
            if (adr > 0)
                opcode = adr;
            else
                instruction.setAddress(opcode);
            
            System.out.println(String.format("0x%02X %s", (byte)opcode, 
                instruction.getSymbol()));
            
            // if body only consist of asterisk, then copy the
            // body of the previous block
            if (previous != null && instruction.isBodyWildcard()) {
                instruction.setBody(previous.getBody());
            }
            
            List<Block> T_states = Block.split(instruction.getBody());
            
            for (Block T_state : T_states) {
                
                // check for copy by name(address)
                if (T_state.getSymbol().startsWith("*")) {
                    String opToCpy = 
                            T_state.getSymbol().replace("*", "").trim();
                    int src = Block.get(instructions, opToCpy).getAddress();
                    memcopy(memory, src, opcode);
                    continue;
                }
                
                while(Defines.apply(T_state));
                
                // check if there are duplicate line usages
                TreeSet hs = new TreeSet(T_state.getBody());
                if (hs.size() != T_state.getBody().size())
                    System.out.println("\twarning: duplicate line usage");
                
                // initialize byte values pr chip
                int[] value = new int[Microassembler.CHIP_COUNT];
                for (int chip = 0; chip < Microassembler.CHIP_COUNT; chip++) {
                    value[chip] = ControlLines.getInactiveValue(chip);
                }
                
                for (String line : T_state.getBody()) {
                    
                    // skip comment lines
                    if (line.startsWith("//"))
                        continue;
                    
                    ControlLine cl = ControlLines.get(line);
                    
                    // check for undefined lines
                    if (cl == null) {
                        System.out.println("\twarning: control line null: "+line);
                        continue;
                    }
                    
                    value[cl.chip] = cl.activeLow ?
                                value[cl.chip] & ~(cl.value):
                                value[cl.chip] |   cl.value;
                }
                
                // copy to memory
                for (int i = 0; i < Microassembler.CHIP_COUNT; i++) 
                    memory[i][toT(T_state.getSymbol()) + (opcode * T_MAX)] 
                            = value[i];
                
            }
            
            previous = instruction;
            opcode++;
        }
    }
    
    private static void memcopy(int[][] memory, int src, int dst) {
        // the first bits are T state counter; leftshift up 
        src <<= (int) (Math.log10(T_MAX) / Math.log10(2)); // log2(T_max)
        dst <<= (int) (Math.log10(T_MAX) / Math.log10(2));
        
        for (int chip = 0; chip < Microassembler.CHIP_COUNT; chip++) {
            for (int T = 0; T < T_MAX; T++) {
                
                memory[chip][dst + T] = memory[chip][src + T];
            }
        }
    }
    
    private static int toT(String symbol) {
        symbol = symbol.replace("T", "");
        return Integer.parseInt(symbol);
    }
}

class Instruction {
    
}

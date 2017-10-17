package microassembler;

import java.util.HashSet;
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
        int T;
        
        for (Block instruction : instructions) {
            
            int adr = instruction.getAddress();
            if (adr > 0)
                opcode = adr;
            
            System.out.println(String.format("0x%02X %s", (byte)opcode, 
                instruction.getSymbol()));
            
            // if body only consist of asterisk, then copy the
            // body of the previous block
            if (previous != null && instruction.getBody().size() == 1
                    && instruction.getBody().get(0).equals("*")) {
                instruction.setBody(previous.getBody());
            }
            
            previous = instruction;
            
            T = 0;
            List<Block> T_states = Block.split(instruction.getBody());
            
            for (Block T_state : T_states) {

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
                    memory[i][T + (opcode * T_MAX)] = value[i];
                
                T++;
            }
            
            opcode++;
        }
    }
}

class Instruction {
    
}

package microassembler;

import java.util.List;

/**
 *
 * @author erol
 */
public class Instructions {
    
    public static final int T_MAX = 8;
    
    public static void generate(List<Block> blocks, int[][] memory) {
        
        Block instructionBlock = Block.get(blocks, Keywords.INSTRUCTIONS);
        List<Block> instructions = Block.split(instructionBlock.getBody());
        
        int opcode = 0;
        int T;
        
        for (Block instruction : instructions) {
            
            T = 0;
            List<Block> T_states = Block.split(instruction.getBody());
            
            for (Block T_state : T_states) {
                
                Defines.apply(T_state);
                
                int[] value = new int[Microassembler.CHIP_COUNT];
                for (int chip = 0; chip < Microassembler.CHIP_COUNT; chip++) {
                    value[chip] = ControlLines.getInactiveValue(chip);
                }
                
                for (String line : T_state.getBody()) {
                    
                    // skip value generation if this is a HW clock line
                    if (Clocks.isCorrectlyTimed(T_state.getSymbol(), line))
                        continue;
                    
                    ControlLine cl = ControlLines.get(line);
                    
                    if (cl == null) {
                        System.out.println("warning: control line null!");
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

package microassembler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author erol
 */
public class Microassembler {
    
    public static final int CHIP_COUNT = 2;
    public static final int MEMORY_SIZE = 256;
    
    private static final int[][] memory = new int[CHIP_COUNT][MEMORY_SIZE];
    
    public static void main(String[] args) {
        
        if (args.length < 1) {
            System.err.println("provide code file");
            return;
        }
        
        List<String> lines = readCodeFile(args[0]);
        List<Block> blocks = Block.split(lines);
        ControlLines.initialize(blocks);
        prepareMemory();
        Defines.initialize(blocks);
        Clocks.initialize(blocks);
        Instructions.generate(blocks, memory);
        System.out.println("OK");
    }
    
    
    private static List<String> readCodeFile(String file) {
        
        try {

            File f = new File(file);

            BufferedReader b = new BufferedReader(new FileReader(f));
            
            String readLine;
            List<String> lines = new ArrayList<>();
            
            while((readLine = b.readLine()) != null) {
                lines.add(readLine);
            }
            
            return lines;
                
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return null;
    }
    
    private static void prepareMemory() {
        
        for (int chip = 0; chip < CHIP_COUNT; chip++) {
            
            for (int address = 0; address < MEMORY_SIZE; address++) {
                memory[chip][address] = ControlLines.getInactiveValue(chip);
            }
        }
    }
}

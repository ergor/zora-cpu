package microassembler;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author erol
 */
public class Save {
    
    private static final String LOGISIM_HEADER = "v2.0 raw\r\n";
    
    public static void logisimFile(int[][] memory) {
        
        for (int chip = 0; chip < Microassembler.CHIP_COUNT; chip++) {
            StringBuilder sb = new StringBuilder();
            sb.append(LOGISIM_HEADER);
            
            for (int addr = 0; addr < Microassembler.MEMORY_SIZE; addr++) {
                sb.append(String.format("%02X", (byte)memory[chip][addr]));
                sb.append("\r\n");
            }
            
            File f = new File("CU" + chip + ".txt");
            
            if (!f.exists()) {
                try {
                    f.createNewFile();
                } catch (IOException ex) {
                    Logger.getLogger(Save.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
          
            try (FileWriter fw = new FileWriter(f, false)) {
                fw.write(sb.toString());                
            }
            catch (IOException ex) {
                Logger.getLogger(Save.class.getName()).log(Level.SEVERE, null, ex);
            }            
        }
    }
}

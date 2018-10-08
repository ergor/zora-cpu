
import uno
import os

oDoc = XSCRIPTCONTEXT.getDocument()

def table_hex_2_oct(*args):
    sheet_hex = oDoc.getSheets().getByIndex(1)
    sheet_oct = oDoc.getSheets().getByIndex(2)
    x_orig = 2
    y_orig = 7

    def getx(x):
        return x + x_orig
    def gety(y):
        return y + y_orig

    for y in range(16):
        for x in range(16):
            x_offset = 0 if x < 8 else 2 # skip the obstruction
            cell = sheet_hex.getCellByPosition(getx(x) + x_offset, gety(y))

            y_new, x_new = divmod(x, 8)
            y_new = 2*y + y_new

            if y_new >= 16:
                y_new -= 16
                x_new += 9
            
            cell_new = sheet_oct.getCellByPosition(getx(x_new), gety(y_new))
            cell_new.setString(cell.getString())
            cell_new.CellBackColor = cell.CellBackColor
            
            
                    


    #cell.setString("value")

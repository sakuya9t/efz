// Write every function of the current program to a JSON file: entry, name, where the
// name came from (FunctionID labels the static CRT), body ranges, and the functions it
// calls.  tools/revinventory.py reads it.
//   analyzeHeadless <project dir> <name> -process <file> -postScript ExportFunctions.java out.json
//@category efz
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.symbol.Symbol;

public class ExportFunctions extends GhidraScript {
    private static String q(String s) {
        StringBuilder b = new StringBuilder("\"");
        for (char c : s.toCharArray()) {
            if (c == '"' || c == '\\') b.append('\\').append(c);
            else if (c < 0x20) b.append(String.format("\\u%04x", (int) c));
            else b.append(c);
        }
        return b.append('"').toString();
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        try (PrintWriter out = new PrintWriter(new FileWriter(args[0]))) {
            out.println("[");
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            boolean first = true;
            while (it.hasNext()) {
                Function f = it.next();
                Symbol s = f.getSymbol();
                List<String> ranges = new ArrayList<>();
                for (AddressRange r : f.getBody()) {
                    ranges.add("[" + r.getMinAddress().getOffset() + "," + r.getMaxAddress().getOffset() + "]");
                }
                TreeSet<Long> callees = new TreeSet<>();
                for (Function c : f.getCalledFunctions(monitor)) {
                    callees.add(c.getEntryPoint().getOffset());
                }
                if (!first) out.println(",");
                first = false;
                out.print("{\"entry\":" + f.getEntryPoint().getOffset()
                        + ",\"name\":" + q(f.getName(true))
                        + ",\"source\":" + q(s.getSource().toString())
                        + ",\"thunk\":" + f.isThunk()
                        + ",\"external\":" + f.isExternal()
                        + ",\"ranges\":[" + String.join(",", ranges) + "]"
                        + ",\"callees\":" + callees.toString().replace(" ", "")
                        + "}");
            }
            out.println("\n]");
        }
    }
}

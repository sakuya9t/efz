// Decompile functions to a text file, after naming the ones already identified.
//
// Arguments: NAMES OUT LO HI [LO HI ...]
//   NAMES  a JSON object {address: name} (from tools/revmatch.py through
//          tools/revnames.py); functions are created where missing and renamed
//   OUT    the C output; every function in LO-HI ranges, in address order, each
//          headed by `// FUNCTION 0xADDR size NAME`
// Run with analyzeHeadless ... -process BINARY -noanalysis -postScript ExportDecomp.java ...
//@category EFZ

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import ghidra.app.cmd.function.CreateFunctionCmd;

import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExportDecomp extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        String json = new String(Files.readAllBytes(Paths.get(args[0])), "UTF-8");
        Matcher m = Pattern.compile("\"(0x[0-9a-fA-F]+)\"\\s*:\\s*\"((?:[^\"\\\\]|\\\\.)*)\"").matcher(json);
        int renamed = 0;
        while (m.find()) {
            Address a = toAddr(Long.parseLong(m.group(1).substring(2), 16));
            String name = m.group(2).replace("\\\"", "\"").replace("\\\\", "\\");
            Function f = getFunctionAt(a);
            if (f == null) {
                Function inside = getFunctionContaining(a);
                if (inside != null && inside.getEntryPoint().compareTo(a) < 0) {
                    // Ghidra ran two functions together: cut the first one short
                    try {
                        inside.setBody(inside.getBody().intersect(new ghidra.program.model.address.AddressSet(
                            inside.getEntryPoint(), a.subtract(1))));
                    } catch (Exception e) {
                        // overlapping bodies: leave it
                    }
                }
                new CreateFunctionCmd(a).applyTo(currentProgram);
                f = getFunctionAt(a);
            }
            if (f != null) {
                try {
                    f.setName(name, SourceType.USER_DEFINED);
                    renamed++;
                } catch (Exception e) {
                    // duplicate or invalid name: leave it
                }
            }
        }
        println("renamed " + renamed);

        DecompInterface d = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        d.setOptions(opts);
        d.openProgram(currentProgram);
        List<long[]> ranges = new ArrayList<>();
        for (int i = 2; i + 1 < args.length; i += 2) {
            ranges.add(new long[] {Long.decode(args[i]), Long.decode(args[i + 1])});
        }
        try (PrintWriter out = new PrintWriter(args[1], "UTF-8")) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                long e = f.getEntryPoint().getOffset();
                boolean want = false;
                for (long[] r : ranges) {
                    want |= r[0] <= e && e < r[1];
                }
                if (!want || f.isThunk()) {
                    continue;
                }
                out.printf("// FUNCTION 0x%x %d %s%n", e, f.getBody().getNumAddresses(), f.getName());
                DecompileResults res = d.decompileFunction(f, 60, monitor);
                if (res.decompileCompleted()) {
                    out.println(res.getDecompiledFunction().getC());
                } else {
                    out.println("// decompilation failed: " + res.getErrorMessage());
                }
            }
        }
    }
}

const encoder = new TextEncoder();

Module.onRuntimeInitialized = async () => {
    const calc = {
        WASMopenBuffer: (str) => {
            const strbytes = encoder.encode(str);
            const buffer   = Module._malloc(strbytes.length);

            Module.HEAPU8.set(strbytes, buffer);

            Module.ccall("WASMopenBuffer", "void", ["number"], [buffer]);

            Module._free(buffer);
        },
        init_cc:         Module.cwrap("init_cc", "", ""),
        tokenize_source: Module.cwrap("tokenize_source", "", ""),
        parse_source:    Module.cwrap("parse_source", "", ""),
        clean_cc:        Module.cwrap("clean_cc", "", ""),
    };

    main(calc);
};

function main(calc) {
    console.log("beginning c execution!");

    const input = "int x = 0;";

    calc.init_cc();
    calc.WASMopenBuffer(input);
    calc.tokenize_source();
    calc.parse_source();
}

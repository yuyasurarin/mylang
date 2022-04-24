// 2022.4 haruki1234
class NLMC {
    constructor(Code) {
        if (typeof(Code)!="string") {
            throw "Code must be a string";
        }
        this.code = Code;
    }
    getCode() {
        return this.code;
    }
    run() {
        let c = this.code;

        let register = {
            "ceq": 0,
            "ret": 0,

            "rax": 0,
            "rdx": 0,
            "rdi": 0,
            "al": 0,
        };
        
        let numbers = ["0","1","2","3","4","5","6","7","8","9"];

        let label = {};
        let array = Array(256).fill(null);
        let sta = Array(256).fill(null);
        let stp = 0;

        let t = this.tokenaize(c);
        console.log(t);
        let p = 0;
        while (p<t.length) {
            if (t[p][0]=="label") { // 0
                label[t[p][1][0]] = p;
            }
            p++;
        }
        // instructions
        p = 0;
        while (p<t.length) {
            if (t[p][0]=="mov") { // 1
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] = Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] = register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="add") { // 2
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] += Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] += register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="sub") { // 3
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] -= Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] -= register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="mul") { // 4
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] *= Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] *= register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="div") { // 5
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] = register[t[p][1][0]]/Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] = register[t[p][1][0]]/register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="push") { // 6
                if (numbers.includes(t[p][1][0][0])) {
                    sta[stp] = Number(t[p][1][0]);
                }
                else {
                    sta[stp] = register[t[p][1][0]];
                }
                stp++;
            }
            else if (t[p][0]=="pop") { // 7
                stp--;
                register[t[p][1][0]] = Number(sta[stp]);
                sta[stp] = null
            }
            else if (t[p][0]=="cmp") { // 100
                let a = register[t[p][1][0]];
                let b;
                if (numbers.includes(t[p][1][1][0])) { b = Number(t[p][1][1]); }
                else { b = register[t[p][1][1]]; }
                if (a==b) { register["ceq"] = 1; }
                else { register["ceq"] = 0; }
            }
            else if (t[p][0]=="jmp") { // 101
                p = label[t[p][1][0]];
            }
            else if (t[p][0]=="jz") { // 102
                if (register["ceq"]==1) {
                    p = label[t[p][1][0]];
                }
            }
            else if (t[p][0]=="jnz") { // 103
                if (register["ceq"]!=1) {
                    p = label[t[p][1][0]];
                }
            }
            // console.log(t[p],register,sta);
            p++;
        }
        return register["ret"]
    }


    tokenaize(c) {
        let token = [];
        let spc = c.split("\n");
        let p = 0;
        while (p<spc.length) {
            let lp = 0;
            while (spc[p][lp]==" ") { lp++; };
            let ins = spc[p].substring(lp).split(" ")[0];
            let arg = spc[p].substring(lp).split(" ").slice(1).join("");
            let ltoken;
            if (arg!=null) {
                let args = arg.split(",");
                ltoken = [ins,args];
            } else { ltoken = [ins,[]]; };
            if (ltoken[0].endsWith(":")) {
                ltoken[1] = [ltoken[0].substring(0,ltoken[0].length-1)];
                ltoken[0] = "label";
            };
            token.push(ltoken);
            p++;
        }
        return token;
    }
}
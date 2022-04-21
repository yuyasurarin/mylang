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
        let array = Array(256).fill(null); // スタックの定義 スタックのサイズ
        let stack = Array(256).fill(null); // スタックの定義 スタックのサイズ
        let stp = 0;

        let t = this.tokenaize(c);
        console.log(t);
        let p = 0;
        while (p<t.length) {
            if (t[p][0]=="label") {
                label[t[p][1][0]] = p;
            }
            p++;
        }
        // instructions
        p = 0;
        while (p<t.length) {
            if (t[p][0]=="mov") {
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] = Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] = register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="add") {
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] += Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] += register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="sub") {
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] -= Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] -= register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="mul") {
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] *= Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] *= register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="div") {
                if (numbers.includes(t[p][1][1][0])) {
                    register[t[p][1][0]] = register[t[p][1][0]]/Number(t[p][1][1]);
                }
                else {
                    register[t[p][1][0]] = register[t[p][1][0]]/register[t[p][1][1]];
                }
            }
            else if (t[p][0]=="push") {
                if (numbers.includes(t[p][1][0][0])) {
                    stack[stp] = Number(t[p][1][0]);
                }
                else {
                    stack[stp] = register[t[p][1][0]];
                }
                stp++;
            }
            else if (t[p][0]=="pop") {
                stp--;
                register[t[p][1][0]] = Number(stack[stp]);
                stack[stp] = null
            }
            else if (t[p][0]=="jmp") {
                p = label[t[p][1][0]];
            }
            else if (t[p][0]=="cmp") {
                let a = register[t[p][1][0]];
                let b;
                if (numbers.includes(t[p][1][1][0])) { b = Number(t[p][1][1]); }
                else { b = register[t[p][1][1]]; }
                if (a==b) { register["ceq"] = 1; }
                else { register["ceq"] = 0; }
            }
            else if (t[p][0]=="jz") {
                if (register["ceq"]==1) {
                    p = label[t[p][1][0]];
                }
            }
            else if (t[p][0]=="jnz") {
                if (register["ceq"]!=1) {
                    p = label[t[p][1][0]];
                }
            }
            // console.log(t[p],register,stack);
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
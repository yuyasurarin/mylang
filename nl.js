class NL {
    constructor(Code) {
        if (typeof(Code)!="string") {
            throw "Code must be a string"
        }
        this.code = Code;
    }
    getCode() {
        return this.code;
    }
    run() {
        let c = this.code;
        let token = this.tokenaize(c);
        this.parsing(token);
    }
    parsing(t) {
    }
    tokenaize(c) {
        let p = 0;
        let operatortype = [
            ["EQUAL","=="],
            ["NOTEQUAL","~="],
            ["EXCLAIM","!"],
            ["ASSIGN","="],
            ["PLUS","+"],
            ["MINUS","-"],
            ["NUL","*"],
            ["NOT","~"],
            ["DIV","/"],
            ["LESS","<"],
            ["GREATER",">"],
            ["LPAREN","("],
            ["RPAREN",")"],
            ["LBRACE","{"],
            ["RBRACE","}"],
            ["SEMICOLON",";"],
            ["COLON",":"],
            ["FUNCTION","fn"],
            ["RETURN","rt"],
            ["IF","if"],
            ["ELSE","ELSE"],
            ["BOOL","true"],
            ["BOOL","false"],
        ]
        let token = []
        while (p<c.length) {
            if (c[p]==" "||c[p]=="\n") {
                p++;
                continue;
            }
            token.push(["VARIABLE",""]);
            while (!(c[p]==" "||c[p]=="\n"||c[p]==null)) {
                let opflag = false;
                for (let o=0;o<operatortype.length;o++) {
                    if (c.startsWith(operatortype[o][1],p)) {
                        p+=operatortype[o][1].length;
                        if (token[token.length-1][1]!="") {
                            token[token.length]=operatortype[o];
                        }
                        else {
                            token[token.length-1]=operatortype[o];
                        }
                        if (token[token.length-1][0]=="COLON"&&token[token.length-2][0]=="VARIABLE") {
                            token[token.length-2][0]="TYPE";
                        }
                        token.push(["VARIABLE",""]);
                        opflag = true;
                        break;
                    }
                }
                if (!opflag) {
                    token[token.length-1][1]+=c[p];
                    if (token[token.length-1][0]=="VARIABLE") {
                        let nums = [0,1,2,3,4,5,6,7,8,9];
                        for (let n=0;n<nums.length;n++) {
                            if (token[token.length-1][1][0]==nums[n]) {
                                token[token.length-1][0]="NUMBER"
                            }
                        }
                    }
                    p++;
                }
            }
            if (token[token.length-1][1]=="") {
                token.splice(token.length-1,1);
            }
            p++;
        }
        return token;
    }
}

class NL_Structure {
    constructor(type,re,value) {
        this.type = type;
        this.return = re;
        this.value = value;
    }
    get() {
        return [this.type,this.return,this.value]
    }
}
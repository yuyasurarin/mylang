class NL {
    constructor(Code) {
        if (typeof(Code)!="string") {
            throw "Code must be a string"
        }
        this.code = Code;
        this.tokentypes = [
            ["EQUAL","=="],
            ["NOTEQUAL","~="],
            ["EXCLAIM","!"],
            ["ASSIGN","="],
            ["PLUS","+"],
            ["MINUS","-"],
            ["MUL","*"],
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
            ["VARIABLE",""],
            ["DIGITS",""],
            ["EOF",""],
        ]
    }
    getCode() {
        return this.code;
    }
    run() {
        let c = this.code;
        let token = this.tokenaize(c);
        console.log(token)
        this.parsing(token);
    }
    parsing(t) {
    }
    tokenaize(c) {
        let p = 0;
        let searchtype = [
            ["EQUAL","=="],
            ["NOTEQUAL","~="],
            ["EXCLAIM","!"],
            ["ASSIGN","="],
            ["PLUS","+"],
            ["MINUS","-"],
            ["MUL","*"],
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
                p+=1;
                continue;
            }
            if (c[p]=="/"&&c[p+1]=="*") {
                p+=1;
                while (!((c[p]=="*"&&c[p+1]=="/")||c[p]==null)) {
                    p++;
                }
                p+=2;
                continue;
            }
            if (c[p]=="/"&&c[p+1]=="/") {
                while (!(c[p+1]=="\n"||c[p+1]==null)) {
                    p++;
                }
                continue;
            }
            token.push(["VARIABLE",""]);
            while (!(c[p]==" "||c[p]=="\n"||c[p]==null)) {
                let opflag = false;
                let mlcomm = false;
                for (let o=0;o<searchtype.length;o++) {
                    if (c.startsWith(searchtype[o][1],p)) {
                        p+=searchtype[o][1].length;
                        if (token[token.length-1][1]!="") {
                            token[token.length]=searchtype[o];
                        }
                        else {
                            token[token.length-1]=searchtype[o];
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
                                token[token.length-1][0]="DIGITS"
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
        token.push(["EOF",""])
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
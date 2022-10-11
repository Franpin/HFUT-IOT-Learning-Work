
const hash_mod = 4294967296;
function FNVhash(str) {
    let OFFSET_BASIS = 2166136261;// 32位offset basis  
    let PRIME = 16777619; // 32位prime  
  
    let hash = OFFSET_BASIS;  
    for (let i = 0; i<str.length; i++) {   
        hash *= PRIME;  
        hash %= hash_mod;
        hash ^= str.charCodeAt(i); 
    }  
    return hash.toString(16); 
}

function fill(num, string) {
    var fillnum = num - string.length;
    if(fillnum < 0) {
        fillnum = 0;
    }
    var str = new Array(fillnum + 1).join("0");
    return str.concat(string);
}

function uuid() {
    var s = [];
    var hexDigits = "0123456789abcdef";
    for (var i = 0; i < 36; i++) {
        s[i] = hexDigits.substr(Math.floor(Math.random() * 0x10), 1);
    }
    s[14] = "4";
    s[19] = hexDigits.substr((s[19] & 0x3) | 0x8, 1);
                                                        
    s[8] = s[13] = s[18] = s[23] = "-";

    var uuid = s.join("");
    return uuid;
}


function messageId(pid, eid, num){
    var date = new Date().getTime();
    let time = parseInt(Date.now()/1000);
    time += '';
    let timeCode = fill(8, time);
    pidBinary = fill(12 ,FNVhash(pid));
    num += '';
    let sumCode = fill(8, num);
    eid += '';
    let eidCode = fill(4, eid);
    var id = `${date}${pidBinary}${eid}${num}`;
    return id;
}
